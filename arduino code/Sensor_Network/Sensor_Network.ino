#include <stdint.h>// for clarity in data types

#include <Wire.h> // for RTC module
#include "RTClib.h"

// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

#include <SPI.h>// For SD card module
#include <SD.h>

#include <Adafruit_GFX.h> // For OLED display
#include <Adafruit_SSD1306.h>


// Global Variables for use throughout the program

File myFile; // initialize file

RTC_DS3231 rtc; // initialize clock

Adafruit_SSD1306 display(128, 64, &Wire); // initialize OLED display


//------------------------------------------------------------
// I use dashes to say that I need to clean this part later.
// Usually this means deleting a debugging comment or statement.
// If There is any other reason, I will write it


//---------------------Clean this up later by making libraries and classes----------------
                                //
                                     //
const PROGMEM uint8_t secToAvg = 1; // seconds to measure flow and get average          //
                                                                                         //
const PROGMEM uint8_t flowPin = 2; // flowmeter pin 
volatile uint16_t flowPulses = 0; // number of flow-meter pulses                         //

const PROGMEM uint8_t counterPin = 3; // fish counter pin
volatile uint16_t fishCount = 0; // number of fish counted till now                      //
volatile unsigned long ltime = millis();
const long LowerTimeThr = 6; // set arbitrarily for now (and ever). A HACK
const long UpperTimeThr = 1000;

                                                                                         //
void countFish() {
  if(digitalRead(counterPin) == HIGH){// What about if LOW and time is not
    ltime = millis();
  }else if(digitalRead(counterPin) == LOW && (millis() - ltime > LowerTimeThr) && (millis() - ltime < UpperTimeThr)){// Consider ltime - millis in large values like 100000
    fishCount++;
  }
}                                                                                       //
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



const uint8_t ONE_WIRE_BUS = 2;
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


void setup () 
{
  //--------------------------Delete Serial before deployment---------------
  Serial.begin(9600);
  
  //---------------------Clean this up later by making libraries and classes----------------
  // attach the interrupt for the fish counter

  pinMode(counterPin, INPUT);
  pinMode(flowPin, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(counterPin), countFish, CHANGE);
    
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
    // how do I handle failures? try agian? There is no guarantee of success. --------------As of right now, I'm printing to OLED the failures.
  }else{
    display.println("CS");
  }

  // check that the sd card was initialized successfully
  if (!SD.begin()) {
    display.println("SDF"); // print failed to initialize SD module
  }else{
    display.println("SDS"); // for some reason this reminds me with Sozialistische Deutsche Studentenbund
  }
  
  display.display();
  delay(5000);


  //----------------------------------------------------------------------------
  sensors.begin();
  
}

void loop () 
{   

  // get sensor data
  double flow = getFlow();
  uint16_t count = fishCount;  
  
  DateTime now = rtc.now(); // get current time

  // clear display
  display.clearDisplay();
  display.setCursor(0,0);

  // print reading to OLED screen
  display.println("Last Reading:");
  display.display();
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.println(now.day(), DEC);
  
  
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

  //--------------------------------------------------delete before deployment
  Serial.println("Last Reading:");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.println(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.println(); 
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  Serial.print("Flow: ");
  Serial.println(flow);
  Serial.print("FishCount: ");
  Serial.println(count);


  //----------------------------------------------------------------------------------------



// call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures

  
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }



  //---------------------------------------------------------------------------------------
  

  // open the file. Only one file can be open at a time,
  // so you have to close this one before opening another.
  // I know that now you can open more than one at the same
  // time, but when I used to do it, I would get corrupted
  // data after some time.
  
  myFile = SD.open("TDATA.txt", FILE_WRITE);

  if(!myFile){//---------------------file checking doesn't work if I remove sd card in middle of operation.-----test why
    display.println("File Write Failed");
    display.display();
  }else{
    display.println("Can Write to File");
    display.display();
    
    myFile.print(now.year(), DEC);
    myFile.print(',');
    myFile.print(now.month(), DEC);
    myFile.print(',');
    myFile.print(now.day(), DEC);
    myFile.print(',');
    myFile.print(now.hour(), DEC);
    myFile.print(',');
    myFile.print(now.minute(), DEC);
    myFile.print(',');
    myFile.print(now.second(), DEC);
    myFile.print(',');
    myFile.print(count);
    myFile.print(',');
    myFile.println(flow);
    
    myFile.close();
  }
  
  delay(100);
}
