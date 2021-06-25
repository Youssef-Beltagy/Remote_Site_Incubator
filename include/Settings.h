#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h> // For using Arduino Framework

#include <stdint.h>// for clarity in data types

#include "FS.h"// For using a filesystem for the SD Card
#include "SD.h"// For the SD Card
#include "SPI.h"// Serial Peripheral Interface for the SD Card
#include "SDCard.h"

#include <Wire.h> // I2C protocol for the RTC module
#include "RTClib.h" // For the RTC module

#include <OneWire.h>// For the thermometer
#include <DallasTemperature.h>// For the thermometers

#include <Adafruit_GFX.h> // For OLED display
#include <Adafruit_SSD1306.h>

#include <WiFi.h> // for connecting to the server
#include <ThingSpeak.h>

#define FISHCOUNTER_DEBUG
//#define SET_TIME

//TODO: clean
#ifdef FISHCOUNTER_DEBUG
RTC_DATA_ATTR int bootCount = 0;
#endif // FISHCOUNTER_DEBUG

RTC_DS3231 rtc; // initialize clock

struct TimeStorage{
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
};

namespace Settings{

    // Fish counter variables
  uint8_t PROGMEM fishCounterPin = 33;
  volatile uint16_t RTC_DATA_ATTR fishCount = 0;

  //uint8_t PROGMEM SDApin = 21;
  //uint8_t PROGMEM SCLpin = 22;


  // year, month, day, hour, minute, second
  DateTime wakeupTime;
  DateTime now;
  TimeStorage volatile RTC_DATA_ATTR volatileWakeupTime = {2000, 1, 1, 1, 1, 1};
  bool volatile RTC_DATA_ATTR print = true;

  // days, hours, minutes, seconds
  PROGMEM TimeSpan sleepDuration(0, 0, 0, 20);
  uint64_t sleepTimeInMicros = 1000000;

}

#include "FishCounterAndSleep.h"

#endif // SETTINGS_H