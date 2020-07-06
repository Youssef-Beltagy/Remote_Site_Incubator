#include <Arduino.h> // For using Arduino Framework
#include <stdint.h> // For clarity in data types


// This namespace collects all the code related to the fish counter.
namespace FishCounterAndInterruptHandling{

  uint8_t PROGMEM fishCounterPin = 33;

  RTC_DATA_ATTR volatile uint16_t fishCount = 0;

  // debouncing variables
  volatile uint32_t debounceTimer = millis();
  uint32_t PROGMEM lowerTimeThr = 5;
  uint32_t PROGMEM upperTimeThr = 1000;

  volatile bool wokeByFishCounter;

  // Sleep handling variables
  RTC_DATA_ATTR volatile uint32_t wentToSleepTime = millis();
  uint32_t PROGMEM sleepTime = 15*60*1000;// fifteen minutes
  RTC_DATA_ATTR volatile bool timeToPrint = false;


  void process_wakeup(){

    wokeByFishCounter = false;

    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

    if(wakeup_reason == ESP_SLEEP_WAKEUP_EXT0){
      fishCount++;

      // If the signal is still high, record that so the incrementCounter function doesn't double count.
      if(digitalRead(fishCounterPin) == HIGH) wokeByFishCounter = true;
      
    }

    // either it is time to wakeup or the esp32 didn't sleep (first boot)
    if (wakeup_reason != ESP_SLEEP_WAKEUP_TIMER || abs((wentToSleepTime + sleepTime) - millis()) <= 500){
      timeToPrint = true;
    }

    #ifdef FISHCOUNTER_DEBUG
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


  // void increment() {
  //   if(digitalRead(digitalPinToInterrupt(33)) == HIGH){// What about if LOW and time is not
  //     if(wokeByFishCounter) return;
  //     ltime = millis();
  //   }else if(digitalRead(digitalPinToInterrupt(33)) == LOW ){// Consider ltime - millis in large values like 100000
  //     if(wokeByFishCounter){
  //       wokeByFishCounter = false;
  //       return;
  //     }

  //     if((millis() - ltime > LowerTimeThr) && (millis() - ltime < UpperTimeThr))
  //       fishCount++;
  //   }
  // }

  
  // void countFish() {
  //     if(digitalRead(counterPin) == HIGH){// What about if LOW and time is not
  //         debounceTimer = millis();
  //     }else if(digitalRead(counterPin) == LOW && (millis() - debounceTimer > lowerTimeThr) && (millis() - debounceTimer < upperTimeThr)){// Consider ltime - millis in large values like 100000
  //         fishCount++;
  //     }
  // }

  // void init(){
  //     wokeByFishCounter = false;
  //   //Print the wakeup reason for ESP32
  //   print_wakeup_reason();

  //   attachInterrupt(digitalPinToInterrupt(33), increment, CHANGE);

  //   Serial.begin(115200);
  // delay(1000); //Take some time to open up the Serial Monitor
  // }

  // void sleep(){

  //     esp_sleep_enable_timer_wakeup(15*1000000);
  //   esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
  //     while(digitalRead(digitalPinToInterrupt(33)) == HIGH){
  //     delay(1);
  //   }
  //   //Go to sleep now
  //   Serial.println("Going to sleep now");
  //   esp_deep_sleep_start();
  // }

}