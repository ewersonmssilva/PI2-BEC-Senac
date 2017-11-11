#ifndef sd_card_h
#define sd_card_h

#include <FS.h>
#include <SD.h>
#include <SPI.h>

uint64_t cardSize = SD.cardSize() / (1024 * 1024);
//Serial.printf("SD Card Size: %lluMB\n", cardSize);
#endif
