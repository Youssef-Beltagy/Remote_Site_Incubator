#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

int i;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  i = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  i++;
  delay(1000);
  Serial.println(i);
}