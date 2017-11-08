#ifndef display_h
#define display_h
#include "sd_card.h"

//Display TFT
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
#define TFT_GREY 0x5AEB // New colour
unsigned long targetTime = 0; // Used for testing draw times
void Display();
extern char datestring[];

// Inicio da Função do Display
void Display() {

  targetTime = millis();
  yield();
  // First we test them with a background colour set
  tft.setTextSize(1);
  //tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.drawString("PI2 SENAC", 30, 5, 2);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("S. Fluxo:", 20, 30, 2);
  tft.drawFloat(sens_fluxo, 2, 80, 30, 2);

  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("S. Ultra:", 20, 50, 2);
  //tft.drawFloat(pi,precision,xpos,ypos,font); // Draw float
  //pi = 3.14159 and precision is 2 it will print as 3.14
  tft.drawFloat(sens_ultra, 2, 80, 50, 2);

  tft.setTextColor(TFT_PURPLE, TFT_BLACK);
  //tft.drawString("SDCard:", 13, 70, 2);


  uint8_t cardType = SD.cardType();
  if (cardType == CARD_MMC) {
    tft.drawString("MMC:", 13, 70, 2);
  } else if (cardType == CARD_SD) {
    tft.drawString("SDSC:", 14, 70, 2);
  } else if (cardType == CARD_SDHC) {
    tft.drawString("SDHC:", 13, 70, 2);
  } else {
    tft.drawString("UNKNOWN:", 13, 70, 2);
  }


  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  //Serial.printf("SD Card Size: %lluMB\n", cardSize);
  tft.drawNumber(cardSize, 63, 70, 2);
  tft.drawString("MB", 105, 76, 1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString(datestring, 10, 93, 1);

  if (WiFi.status() == WL_CONNECTED) {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString("Rede: OK!", 15, 110, 1);
  } else {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("Rede: Off!", 15, 110, 1);
  }
  if (conn.connected()) {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString("DB: OK!", 75, 110, 1);
  } else {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("DB: Off!", 75, 110, 1);
  }
}
#endif
