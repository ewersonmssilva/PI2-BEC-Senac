#ifndef sd_card_h
#define sd_card_h

#include <FS.h>
#include <SD.h>
#include <SPI.h>

uint64_t cardSize = SD.cardSize() / (1024 * 1024);
//Serial.printf("SD Card Size: %lluMB\n", cardSize);


void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}


void escreve_SD() {
  if (minutos == 20 && segundos == 22 || minutos == 40 && segundos == 22 || minutos == 58 && segundos == 22) {
    //writeFile(SD, "/sensores.txt", datestring);
    //appendFile(SD, "/sensores.txt", valor);
    appendFile(SD, "/sensores.txt", "\n");
    appendFile(SD, "/sensores.txt", "Fluxo  ");
    appendFile(SD, "/sensores.txt", " Ultra ");
    appendFile(SD, "/sensores.txt", datestring);
  }
}
#endif
