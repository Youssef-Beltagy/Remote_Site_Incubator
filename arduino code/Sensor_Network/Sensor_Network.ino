//#include <stdint.h>// for clarity in data types

#include <Wire.h> // for RTC module
#include "RTClib.h"

#include <SPI.h>// For SD card module
#include <SD.h>

#include <Adafruit_GFX.h> // For OLED display
#include <Adafruit_SSD1306.h>


// Global Variables for use throughout the program

//File myFile; // initialize file

RTC_DS3231 * rtc = new rtc(); // initialize clock

Adafruit_SSD1306 * display =  new Adafruit_SSD1306(128, 64, &Wire); // initialize OLED display


//------------------------------------------------------------
// I use dashes to say that I need to clean this part later.
// Usually this means deleting a debugging comment or statement.
// If There is any other reason, I will write it


//---------------------Clean this up later by making libraries and classes----------------
const PROGMEM byte counterPin = 3; // fish counter pin                                //
const PROGMEM byte flowPin = 2; // flowmeter pin                                      //
const PROGMEM byte secToAvg = 10; // seconds to measure flow and get average          //
                                                                                         //
volatile unsigned int fishCount = 0; // number of fish counted till now                      //
volatile unsigned int flowPulses = 0; // number of flow-meter pulses                         //
                                                                                         //
void countFish(){                                                                        //
  ++fishCount;                                                                           //
}                                                                                        //
                                                                                         //
void incrementPulses(){                                                                  //
  ++flowPulses;                                                                          //
}                                                                                        //
                                                                                         //
//-----------------------------------------------------------------------------------------

//---------------------Clean this up later by making libraries and classes----------------
double getFlow(){
  // attach the interrupt for the fish counter
  
  flowPulses = 0;// reset counter 
  
  attachInterrupt(digitalPinToInterrupt(flowPin), incrementPulses, RISING);
  
  delay(1000 * secToAvg);// wait some time and get the average
  
  detachInterrupt(digitalPinToInterrupt(flowPin));
  
  return (double) flowPulses/ (double) (secToAvg);
}
//-----------------------------------------------------------------------------------------

void setup () 
{

  Serial.begin(9600);
  delay(10);
  Serial.println("hello");
  //---------------------Clean this up later by making libraries and classes----------------
  // attach the interrupt for the fish counter
  attachInterrupt(digitalPinToInterrupt(counterPin), countFish, RISING);
    
  //-----------------------------------------------------------------------------------------
 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  // Clear the buffer.
  display.clearDisplay();
  
  // text display tests
  display.setTextSize(1); // choice of size between 1 to 8
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  // check that the clock was initialized successfully.
  if (! rtc.begin()) {
    display.println("Cf"); // print failed to initialize clock
    // how do I handle failures? try agian? There is no guarantee of success --------------------------------
  }else{
    display.println("CS");
  }

  // check that the sd card was initialized successfully
  if (!SD.begin()) {
    display.println("SDf"); // print failed to initialize SD module
  }else{
    display.println("SDS");
  }
  
  display.display();
  delay(5000);
  
}

void loop () 
{   

  // get sensor data
  double flow = getFlow();
  unsigned int count = fishCount;  
  
  DateTime now = rtc.now(); // get current time

  // clear display
  display.clearDisplay();
  display.setCursor(0,0);

  // print reading to OLED screen
  display.println("Last Reading:");
  display.println(now.year(), DEC);
  display.print('/');
  display.println(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.print(" ");
  display.display();
  
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.println(now.second(), DEC);
  display.display();

  display.print("Flow: ");
  display.println(flow);
  display.print("FishCount: ");
  display.println(count);
  display.display();

  //--------------------------------------------------
  Serial.println("Last Reading:");
  Serial.println(now.year(), DEC);
  Serial.print('/');
  Serial.println(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" "); 
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  Serial.print("Flow: ");
  Serial.println(flow);
  Serial.print("FishCount: ");
  Serial.println(count);
  

  // open the file. Only one file can be open at a time,
  // so you have to close this one before opening another.
  // I know that now you can open more than one at the same
  // time, but when I used to do it, I would get corrupted
  // data after some time.
  
//  myFile = SD.open("TDATA.txt", FILE_WRITE);
//
//  if(!myFile){
//    display.println("Failed to write to file");
//    display.display();
//  }else{
//    myFile.print(now.year(), DEC);
//    myFile.print(',');
//    myFile.print(now.month(), DEC);
//    myFile.print(',');
//    myFile.print(now.day(), DEC);
//    myFile.print(',');
//    myFile.print(now.hour(), DEC);
//    myFile.print(',');
//    myFile.print(now.minute(), DEC);
//    myFile.print(',');
//    myFile.print(now.second(), DEC);
//    myFile.print(',');
//    myFile.print(count);
//    myFile.print(',');
//    myFile.println(flow);
//    
//    myFile.close();
//  }
  
  delay(100);
}
