#include <Wire.h> // for RTC module
#include "RTClib.h"

#include <SPI.h>// For SD card module
#include <SD.h>

File myFile;

RTC_DS3231 rtc;

void setup () 
{
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("RTC f");
    // how do I handle failures? try agian? There is no guarantee of success
  }

  if (!SD.begin()) {
    Serial.println("SD f");
  }
  
  // set time of RTC module as the compilation time. Recompile if necessary.
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

int counter = 0;//-----------------------------------
void loop () 
{
    DateTime now = rtc.now();


    // open the file. Only one file can be open at a time,
    // so you have to close this one before opening another.
    // I know that now you can open more than one at the same
    // time, but when I used to do it, I would get corrupted
    // data after some time.
    myFile = SD.open("TDATA.txt", FILE_WRITE);

    if(!myFile){
      Serial.println("f f");
    }
    
    myFile.println("Current Date & Time: ");
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(" (");
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(") counter: ");
    myFile.println(++counter);

    myFile.close();
    
    delay(100);
}
