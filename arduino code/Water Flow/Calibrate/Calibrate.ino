#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

byte sensorPin =  2;
byte rstPin = 3;

volatile unsigned long count = 0;  

void pulseCounter()
{
  count++;
}

void rstCounter()
{
  count = 0;
}

void setup()
{
  
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  // Clear the buffer.
  display.clearDisplay();
  
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  pinMode(sensorPin, INPUT);
  pinMode(rstPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  attachInterrupt(digitalPinToInterrupt(rstPin), rstCounter, FALLING);

}


void loop()
{
  unsigned long temp = count;
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Count:  ");
  display.println(count);
  display.display();
  
}
