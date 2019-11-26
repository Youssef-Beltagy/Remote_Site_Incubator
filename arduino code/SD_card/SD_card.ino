#include <SPI.h>
#include <SD.h>

File myFile;

// cs or ss pin on the sd card module.
const int chipSelect = 10;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("Init SD");

  if (!SD.begin()) {
    Serial.println("init fail");
    return;
  }
  
  Serial.println("init done");

 SD.remove("DATA.TXT");

}

int counter = 0;
void loop()
{
  // open the file. Only one file can be open at a time,
  // so you have to close this one before opening another.
  // I know that now you can open more than one at the same
  // time, but when I used to do it, I would get corrupted
  // data after some time.
   myFile = SD.open("DATA.TXT", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.print("count: ");
    myFile.println(++counter);
    // close the file:
    myFile.close();
    Serial.println(counter);
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  delay(1000);
}
