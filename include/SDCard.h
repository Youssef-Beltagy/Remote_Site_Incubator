#include <Arduino.h>
#include "FS.h"// For using a filesystem for the SD Card
#include "SD.h"// For the SD Card
#include "SPI.h"// Serial Peripheral Interface for the SD Card

// A debugging class to display the contents of an SD Card
// Uses the code from http://www.esp32learning.com/code/esp32-and-microsd-card-example.php

class SDCard{

private:
    fs::FS* ptrFS;

public:

    SDCard(fs::FS & fs);

    void listDir(const char * dirname, uint8_t levels);

    void createDir(const char * path);

    void removeDir(const char * path);

    void readFile(const char * path);

    void writeFile(const char * path, const char * message);

    void appendFile(const char * path, const char * message);

    void renameFile(const char * path1, const char * path2);

    void deleteFile(const char * path);

    void testFileIO(const char * path);

};


