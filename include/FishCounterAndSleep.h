#ifndef FISHCOUNTERANDSLEEP_H
#define FISHCOUNTERANDSLEEP_H
#include "Settings.h"

//TODO: add ifndef and endif


// This namespace collects all the code related to the fish counter.
namespace FishCounterAndSleep{

  using namespace Settings;
  // Will only use the fishCount and fishCounterPin variables.
  // TODO: Consider whether to define the fishCount variable in here or in settings

  // The interrupt service routine function responsible for counting fish
  void incrementFishCount() {

    fishCount++;

  }

  // FIXME: Possibly add an increment function that debounces to count while writing data

  // The first to call when the esp32 wakes up.
  void process_wakeup(){

    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

    if(wakeup_reason == ESP_SLEEP_WAKEUP_EXT0){
      incrementFishCount();
    }

    #ifdef FISHCOUNTER_DEBUG

      // begin serial monitor
      Serial.begin(115200);

      //Take some time to open up the Serial Monitor
      //delay(1000);

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

    rtc.begin();


    //FIXME: What in the world is this? Why in the world is this loaded using the volatile
    wakeupTime = DateTime(  volatileWakeupTime.year,
                            volatileWakeupTime.month,
                            volatileWakeupTime.day,
                            volatileWakeupTime.hour,
                            volatileWakeupTime.min,
                            volatileWakeupTime.sec);
    now = rtc.now();

    Serial.println("WAKEUP: " + wakeupTime.timestamp());
    Serial.println("NOW: " + now.timestamp());
    Serial.println("PRINT: " + print);

    if(print || now >= wakeupTime){
      print = true;
      wakeupTime = now + sleepDuration;
    }

    sleepTimeInMicros *= uint64_t((wakeupTime - now).totalseconds());
    //Serial.println("Duration: " + String(sleepTimeInMicros.totalseconds()) );

  }

  // The method to call to put the esp32 to sleep.
  void sleep(){

    // spin-wait until the signal falls to low to ensure the fish was counted
    while(digitalRead(digitalPinToInterrupt(fishCounterPin)) == HIGH){
      delay(1);
    }

    #ifdef FISHCOUNTER_DEBUG
      Serial.println("Going to sleep now");
    #endif // FISHCOUNTER_DEBUG

    print = false;
    volatileWakeupTime.year = wakeupTime.year();
    volatileWakeupTime.month = wakeupTime.month();
    volatileWakeupTime.day = wakeupTime.day();
    volatileWakeupTime.hour = wakeupTime.hour();
    volatileWakeupTime.min = wakeupTime.minute();
    volatileWakeupTime.sec = wakeupTime.second();

    esp_sleep_enable_timer_wakeup(sleepTimeInMicros);
    esp_sleep_enable_ext0_wakeup(gpio_num_t(fishCounterPin), 1); //1 = High, 0 = Low
    esp_deep_sleep_start();
  }

}

#endif // FISHCOUNTERANDSLEEP_H