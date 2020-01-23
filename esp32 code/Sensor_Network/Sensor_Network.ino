
#include "FS.h"
#include "SD.h"
#include "SPI.h"


//----------------------------------------------------------------------------------------------------------make namespace later--------------------------------------------------------
// update these functions so they take an object that they will print to instead of Serial. Serial is useless without a computer. I can't use Serial in the field.
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char * path){
    Serial.printf("Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}



//--------------------------------------------------------------------------Make Library Later--------------------------------------------------------------------------

// I need to solve this namespace issue because it is crippling. I want to be able to make classes with instances.
namespace FlowMeter{

//    FlowMeter(){}
//
//    FlowMeter(uint8_t tmpflowPin, uint8_t tmpsecToAvg){
//        FlowMeter::secToAvg = tmpsecToAvg;
//        FlowMeter::flowPin = tmpflowPin;
//
//        pinMode(FlowMeter::flowPin, INPUT);
//    }

//    FlowMeter(uint8_t flowPin){
//          FlowMeter(flowPin, 1); // the default sampling time is one second
//    }


    uint8_t secToAvg; // seconds to measure flow and get average          //
                                                                                         //
    uint8_t flowPin; // flowmeter pin 

    static volatile uint16_t flowPulses; // number of flow-meter pulses

    static void incrementPulses(){       
        ++flowPulses;
    }

    double getFlow(){
  
        flowPulses = 0;// reset counter 
        
        attachInterrupt(digitalPinToInterrupt(FlowMeter::flowPin), incrementPulses, RISING);

        // Ideally, I'd like to do something concurrently-------------------------------------------------------------------\
        // point to consider: I can't have two flow meters working at the same time becaus flowPulses is static.
        // If I do that, I will get the sum of the two flows.
        delay(1000 * secToAvg);// wait some time and get the average
        
        detachInterrupt(digitalPinToInterrupt(FlowMeter::flowPin));

        double flow = (double) flowPulses/ (double) (secToAvg);

        flowPulses = 0;
        
        return flow;
    }

    void setFlowMeterValues(uint8_t tmpflowPin, uint8_t tmpsecToAvg){

        FlowMeter::secToAvg = tmpsecToAvg;
        FlowMeter::flowPin = tmpflowPin;

        pinMode(FlowMeter::flowPin, INPUT);
      
    }

};


//---------------------------------------------------------------------------------Make another library later----------------------------------------------------------
// I want to make this a class
// This is no longer a class
// No, I can only have one fish counter because the pin itself has to be static. 

// The solution is to know which pin caused the interrupt. Apparently there is a solution. Let me look at it later.
// https://forum.arduino.cc/index.php?topic=328670.0

// This might solve the flowmeter issue as well, interesting. For now, I need to switch to computer vision within 15 minutes.
namespace FishCounter{

    uint8_t counterPin;

    long lowerTimeThr;

    long upperTimeThr;

    volatile unsigned long mtime;

    volatile uint16_t fishCount;

    void countFish() {
        if(digitalRead(counterPin) == HIGH){// What about if LOW and time is not
            mtime = millis();
        }else if(digitalRead(counterPin) == LOW && (millis() - mtime > lowerTimeThr) && (millis() - mtime < upperTimeThr)){// Consider ltime - millis in large values like 100000
            fishCount++;
        }
    }


    //--------------------I want a way to get rid of this function if possible. But If I try to define static member variables inside 
    // the class I get compilation errors. I want to look into that later. I want cleaner code.
    void setFishCounterValues(uint8_t tmpcounterPin, long tmplowerTimeThr, long tmpupperTimeThr){
    
        counterPin = tmpcounterPin;
        fishCount = 0;
    
        lowerTimeThr = tmplowerTimeThr;
        upperTimeThr = tmpupperTimeThr;
    
        mtime = millis();
    
        pinMode(counterPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(counterPin), countFish, CHANGE);
          
    }
    
    
//    FishCounter(){}

//    If I try to initialize static member variables, I get compile erros.
//    FishCounter(uint8_t counterPin, long lowerTimeThr, long upperTimeThr){
//
//      setValues(counterPin, lowerTimeThr, upperTimeThr);
//      
//    }

    uint16_t getFishCount(){
      return fishCount;
    }

};


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


























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



RTC_DS3231 rtc; // initialize clock

Adafruit_SSD1306 display(128, 64, &Wire); // initialize OLED display

const uint8_t ONE_WIRE_BUS = 2;
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//FlowMeter flowmeter;

//FishCounter fishcounter;


void setup(){

  //--------------------------Delete Serial before deployment---------------
    Serial.begin(115200);

 
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
      display.println("Failed to initialize clock"); // print failed to initialize clock
      // how do I handle failures? try agian? There is no guarantee of success. --------------As of right now, I'm printing the failures to OLED.
    }else{
      display.println("Initialized clock");
    }

    if(!SD.begin()){
       display.println("Card Mount Failed");
    }
    
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        display.println("No SD card attached");
        return;
    }

    display.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        display.println("MMC");
    } else if(cardType == CARD_SD){
        display.println("SDSC");
    } else if(cardType == CARD_SDHC){
        display.println("SDHC");
    } else {
        display.println("UNKNOWN");
    }


    sensors.begin();
    // call sensors.requestTemperatures() to issue a global temperature 
    // request to all devices on the bus
    sensors.requestTemperatures(); // Send the command to get temperatures

    float tempC = sensors.getTempCByIndex(0);

    // Check if reading was successful
    if(tempC != DEVICE_DISCONNECTED_C) 
    {
      display.print("Temp(index 0): ");
      display.println(tempC);
    } 
    else
    {
      display.println("Error: Could not read temp");
    }

    FlowMeter::setFlowMeterValues(25, 1);
    FishCounter::setFishCounterValues(4, 10, 1000);

    display.display();
}

void loop(){

//   get sensor data
    double flow = FlowMeter::getFlow();
    uint16_t count = FishCounter::getFishCount();

    sensors.requestTemperatures(); // Send the command to get temperatures
    float tempC = sensors.getTempCByIndex(0);
  
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
    display.print("Temp: ");
    display.println(tempC);
    display.display();

//  //--------------------------------------------------delete before deployment
//  Serial.println("Last Reading:");
//  Serial.print(now.year(), DEC);
//  Serial.print('/');
//  Serial.println(now.month(), DEC);
//  Serial.print('/');
//  Serial.print(now.day(), DEC);
//  Serial.println(); 
//  Serial.print(now.hour(), DEC);
//  Serial.print(':');
//  Serial.print(now.minute(), DEC);
//  Serial.print(':');
//  Serial.println(now.second(), DEC);
//  Serial.print("Flow: ");
//  Serial.println(flow);
//  Serial.print("FishCount: ");
//  Serial.println(count);
//
//
//  //----------------------------------------------------------------------------------------
//
//
//

//
//  
//  // After we got the temperatures, we can print them here.
//  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
//  
//
//
//
//  //---------------------------------------------------------------------------------------
//  
//
//  // open the file. Only one file can be open at a time,
//  // so you have to close this one before opening another.
//  // I know that now you can open more than one at the same
//  // time, but when I used to do it, I would get corrupted
//  // data after some time.
//  
//  myFile = SD.open("TDATA.txt", FILE_WRITE);
//
//  if(!myFile){//---------------------file checking doesn't work if I remove sd card in middle of operation.-----test why
//    display.println("File Write Failed");
//    display.display();
//  }else{
//    display.println("Can Write to File");
//    display.display();
//    
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


}
