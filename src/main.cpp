
// // delete before uploading to github and repopulate again next time--------------------------------------------------------------------
// const char* ssid     = "";
// const char* password = "";
// const uint32_t channel = 0;
// const char* writeKey = "";


// RTC_DS3231 rtc; // initialize clock

// Adafruit_SSD1306 display(128, 64, &Wire); // initialize OLED display

// const uint8_t ONE_WIRE_BUS = 2;
// // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// OneWire oneWire(ONE_WIRE_BUS);

// // Pass our oneWire reference to Dallas Temperature. 
// DallasTemperature sensors(&oneWire);

// WiFiClient  client;

// void setup(){

//   //--------------------------Delete Serial before deployment---------------
//     Serial.begin(115200);

 
//     // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//     display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
    
//     // Clear the buffer.
//     display.clearDisplay();
    
//     // text display tests
//     display.setTextSize(1); // choice of size between 1 to 8
//     display.setTextColor(WHITE);
//     display.setCursor(0,0);
    
//     // check that the clock was initialized successfully.
//     if (! rtc.begin()) {
//       display.println("Failed to initialize clock"); // print failed to initialize clock
//       // how do I handle failures? try agian? There is no guarantee of success. --------------As of right now, I'm printing the failures to OLED.
//     }else{
//       display.println("Initialized clock");
//     }

//     if(!SD.begin()){
//        display.println("Card Mount Failed");
//     }
    
//     uint8_t cardType = SD.cardType();

//     if(cardType == CARD_NONE){
//         display.println("No SD card attached");
//         return;
//     }

//     display.print("SD Card Type: ");
//     if(cardType == CARD_MMC){
//         display.println("MMC");
//     } else if(cardType == CARD_SD){
//         display.println("SDSC");
//     } else if(cardType == CARD_SDHC){
//         display.println("SDHC");
//     } else {
//         display.println("UNKNOWN");
//     }


//     sensors.begin();
//     // call sensors.requestTemperatures() to issue a global temperature 
//     // request to all devices on the bus
//     sensors.requestTemperatures(); // Send the command to get temperatures

//     float tempC = sensors.getTempCByIndex(0);

//     // Check if reading was successful
//     if(tempC != DEVICE_DISCONNECTED_C) 
//     {
//       display.print("Temp(index 0): ");
//       display.println(tempC);
//     } 
//     else
//     {
//       display.println("Error: Could not read temp");
//     }

//     FlowMeter::setFlowMeterValues(32, 1);
//     FishCounterAndInterruptHandling::setFishCounterValues(34, 10, 1000);

//     display.display();


//     WiFi.begin(ssid, password);
//     display.print("Connecting to Wifi:");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         display.print(".");
//         display.display();
//     }

//     WiFi.mode(WIFI_STA);
//     ThingSpeak.begin(client);

//     delay(1000);

// }

// void loop(){

//   //---------------------------------------I probably need to redo this after each sleeping cycle
//   SD.begin();
//   WiFi.begin(ssid, password);
//     display.print("Connecting to Wifi:");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }

//     WiFi.mode(WIFI_STA);
//     ThingSpeak.begin(client);

  

// //   get sensor data
//     float flow = FlowMeter::getFlow();
//     uint16_t count = FishCounterAndInterruptHandling::getFishCount();

//     sensors.requestTemperatures(); // Send the command to get temperatures
//     float tempC = sensors.getTempCByIndex(0);
  
//     DateTime now = rtc.now(); // get current time
    
//     // clear display
//     display.clearDisplay();
//     display.setCursor(0,0);
    
//     // print reading to OLED screen
//     display.println("Last Reading:");
//     display.display();
//     display.print(now.year(), DEC);
//     display.print('/');
//     display.print(now.month(), DEC);
//     display.print('/');
//     display.print(now.day(), DEC);
    
    
//     display.display();

//     display.print(" ");
//     display.print(now.hour(), DEC);
//     display.print(':');
//     display.print(now.minute(), DEC);
//     display.print(':');
//     display.println(now.second(), DEC);
//     display.display();
    
//     display.print("Flow: ");
//     display.println(flow);
//     display.print("FishCount: ");
//     display.println(count);
//     display.print("Temp: ");
//     display.println(tempC);
//     display.display();


// //------------------------------------------------------------------------
//     File file = SD.open("/readings.txt", FILE_APPEND);
//     if(!file){
//         display.println("Failed to open file for writing");
//     }else{
//         bool writtenToFile = true;

//         writtenToFile = writtenToFile && file.print(now.year(), DEC);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.print(now.month(), DEC);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.print(now.day(), DEC);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.print(now.hour(), DEC);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.print(now.minute(), DEC);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.print(now.second(), DEC);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.print(flow);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.print(count);
//         writtenToFile = writtenToFile && file.print(", ");
//         writtenToFile = writtenToFile && file.println(tempC);
        

//         if(writtenToFile){
//             display.println("File written");
//         } else {
//             display.println("Write failed");
//         }
//         file.close();
//     }

//     display.display();


//       // Connect or reconnect to WiFi
//     if(WiFi.status() != WL_CONNECTED){
//       display.print("Attempting to connect to SSID: ");
//       display.println(ssid);
//       while(WiFi.status() != WL_CONNECTED){
//         WiFi.begin(ssid, password);
//         display.print(".");
//         delay(5000);
//         display.display();  
//       } 
//       display.println("\nConnected.");
//       display.display();
//     }
  
//     ThingSpeak.setField(1, "Time");
//     ThingSpeak.setField(2, flow);
//     ThingSpeak.setField(3, count);
//     ThingSpeak.setField(4, tempC);
    
//     int x = ThingSpeak.writeFields(channel, writeKey);
    
//     // Check the return code
//     if(x == 200){
//       display.println("Channel update successful.");
//     }
//     else{
//       display.println("Problem updating channel. HTTP error code " + String(x));
//     }

//     display.display();
    
//     //delay(20000); // Wait 20 seconds before sending a new value

//     esp_sleep_enable_timer_wakeup(200000000);
//     esp_light_sleep_start();


    
//    //-----------------------------------------------------------------------------------

//     //listDir(SD, "/", 0);
//     //createDir(SD, "/mydir");
//     //listDir(SD, "/", 0);
//     //removeDir(SD, "/mydir");
//     //listDir(SD, "/", 2);
//     //writeFile(SD, "/hello.txt", "Hello ");
//     //appendFile(SD, "/readings.txt", now.year());
//     //appendFile(SD, "/readings.txt", flow + "," + count + "," + tempc + "\n");
//     //readFile(SD, "/hello.txt");
//     //deleteFile(SD, "/foo.txt");
//     //renameFile(SD, "/hello.txt", "/foo.txt");
//     //readFile(SD, "/foo.txt");
//     //testFileIO(SD, "/test.txt");
//     //Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
//     //Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));

// //  //--------------------------------------------------delete before deployment
// //  Serial.println("Last Reading:");
// //  Serial.print(now.year(), DEC);
// //  Serial.print('/');
// //  Serial.println(now.month(), DEC);
// //  Serial.print('/');
// //  Serial.print(now.day(), DEC);
// //  Serial.println(); 
// //  Serial.print(now.hour(), DEC);
// //  Serial.print(':');
// //  Serial.print(now.minute(), DEC);
// //  Serial.print(':');
// //  Serial.println(now.second(), DEC);
// //  Serial.print("Flow: ");
// //  Serial.println(flow);
// //  Serial.print("FishCount: ");
// //  Serial.println(count);
// //
// //
// //  //----------------------------------------------------------------------------------------
// }

// //=====================================================================+++++++++++++++++++++++++++++++++++++++++++++++++++
#define FISHCOUNTER_DEBUG

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

#include <FishCounterAndSleep.h>

namespace fcs = FishCounterAndSleep;

#ifdef FISHCOUNTER_DEBUG
int RTC_DATA_ATTR bootCount;
#endif // FISHCOUNTER_DEBUG

void setup(){ 

  fcs::process_wakeup();
  delay(10); //========================= 
  
  #ifdef FISHCOUNTER_DEBUG
  bootCount++;
  Serial.println("Boot number: " + String(bootCount));
  Serial.println("Fish number: " + String(fcs::fishCount));
  Serial.println("micros(): " + micros());//===================causes exceptions, I think. The symptoms are consecutive rebooting.
  //================================ check: https://github.com/espressif/arduino-esp32/issues/1357
  #endif // FISHCOUNTER_DEBUG

  fcs::sleep();

  /* =====================================research more
  First we configure the wake up source
  We set our ESP32 to wake up for an external trigger.
  There are two types for ESP32, ext0 and ext1 .
  ext0 uses RTC_IO to wakeup thus requires RTC peripherals
  to be on while ext1 uses RTC Controller so doesnt need
  peripherals to be powered on.
  Note that using internal pullups/pulldowns also requires
  RTC peripherals to be turned on.
  */
  
 


  

  
}

void loop(){
  //This is not going to be called
}