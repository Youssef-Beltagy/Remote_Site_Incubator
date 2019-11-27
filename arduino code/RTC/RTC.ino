#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup () 
{
  Serial.begin(9600);
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  // Comment out below lines once you set the date & time.
  // Following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () 
{
    DateTime now = rtc.now();
    
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(')');
    
    delay(1000);
}
