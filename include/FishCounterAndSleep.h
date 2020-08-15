#include <Arduino.h> // For using Arduino Framework
#include <stdint.h> // For clarity in data types


// This namespace collects all the code related to the fish counter.
namespace FishCounterAndSleep{

  // Fish counter variables
  uint8_t PROGMEM fishCounterPin = 33;
  RTC_DATA_ATTR volatile uint16_t fishCount = 0;

  // Debouncing variables
  volatile uint32_t debounceTimer = millis();
  uint32_t PROGMEM lowerTimeThr = 5;
  uint32_t PROGMEM upperTimeThr = 1000;

  // If yes, increment fishCount and don't debounce.
  volatile bool wokeByFishCounter = false;

  // Sleep handling variables
  RTC_DATA_ATTR volatile uint32_t wentToSleepTime = millis();
  uint32_t PROGMEM sleepTime = 1*60*1000;// 1 minute(s)
  RTC_DATA_ATTR volatile bool timeToPrint = false;

  // The interrupt service routine function
  void incrementCounter() {

    if(digitalRead(digitalPinToInterrupt(fishCounterPin)) == HIGH){// What about if LOW and time is not
    
      if(wokeByFishCounter) return; // no need to debounce and thus no need to set the debounce timer

      debounceTimer = millis();

    }else if(digitalRead(digitalPinToInterrupt(fishCounterPin)) == LOW ){// Consider ltime - millis in large values like 100000

      if(wokeByFishCounter){ // If esp32 just woke up, that would mean the fish has already been counted.

        wokeByFishCounter = false; // change the state to remember that you can debounce now

        return;
      }

      // If the debouncing time is within acceptable range, count the fish.
      if((millis() - debounceTimer > lowerTimeThr) && (millis() - debounceTimer < upperTimeThr)) fishCount++;

    }
  }

  // The first to call when the esp32 wakes up.
  void process_wakeup(){

    wokeByFishCounter = false;

    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

    if(wakeup_reason == ESP_SLEEP_WAKEUP_EXT0){
      fishCount++;

      // If the signal is still high, record that so the incrementCounter function doesn't double count.
      if(digitalRead(digitalPinToInterrupt(fishCounterPin)) == HIGH) wokeByFishCounter = true;
      else wokeByFishCounter = false;
      
    }

    // either it is time to wakeup or the esp32 didn't sleep (first boot)
    if (wakeup_reason != ESP_SLEEP_WAKEUP_TIMER || (wentToSleepTime + sleepTime) - millis() <= 500){
      timeToPrint = true;
    }

    attachInterrupt(digitalPinToInterrupt(fishCounterPin), incrementCounter, CHANGE);

    #ifdef FISHCOUNTER_DEBUG

    // begin serial monitor
    Serial.begin(115200);

    //Take some time to open up the Serial Monitor
    delay(1000);

    // print wakup reason to the serial monitor.
    switch(wakeup_reason)
    {
      case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
      case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
      case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
      case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
      default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
    }

    #endif // FISHCOUNTER_DEBUG

  }

  // The method to call to put the esp32 to sleep.
  void sleep(){

    // If it is time to print, then a full sleep cycle was completed.
    // Otherwise, it was a partial sleep.
    if(timeToPrint){
      wentToSleepTime = millis();
      timeToPrint = false;
      esp_sleep_enable_timer_wakeup(sleepTime*1000);
    }else{
      esp_sleep_enable_timer_wakeup((sleepTime - (millis()-wentToSleepTime))*1000);
    }

    esp_sleep_enable_ext0_wakeup(gpio_num_t(fishCounterPin), 1); //1 = High, 0 = Low

    // spin-wait until the signal falls to low to ensure the fish was counted
    while(digitalRead(digitalPinToInterrupt(fishCounterPin)) == HIGH){
      delay(1);
    }

    #ifdef FISHCOUNTER_DEBUG
    Serial.println("Going to sleep now");
    #endif // FISHCOUNTER_DEBUG

    //Go to sleep now
    esp_deep_sleep_start();
  }

}