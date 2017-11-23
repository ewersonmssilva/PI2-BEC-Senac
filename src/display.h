#ifndef display_h
#define display_h
#include "sd_card.h"

//Display TFT
#include <TFT_eSPI.h> // Biblioteca gráfica e de fontes para o chip do driver ST7735
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invocar biblioteca, pinos definidos em User_Setup.h
#define TFT_GREY 0x5AEB // Nova cor
unsigned long targetTime = 0; // Usado para testar tempos de desenho
void Display();
extern char datestring[];

// Inicio da Função do Display
void Display()
{
        targetTime = millis();
        yield();
        // Primeiro, preenche com um conjunto de cores de fundo
        tft.setTextSize(1);
        //tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_GREEN, TFT_BLACK);

        tft.drawString("PI2 SENAC", 30, 5, 2);

        tft.setTextColor(TFT_CYAN, TFT_BLACK);
        tft.drawString("S. Fluxo:", 20, 30, 2);
        tft.drawFloat(sens_fluxo, 1, 80, 30, 2);

        tft.setTextColor(TFT_BLUE, TFT_BLACK);
        tft.drawString("S. Ultra:", 20, 50, 2);
        //tft.drawFloat(pi,precision,xpos,ypos,font); // Imprime float
        //pi = 3.14159 e a precisão é 2 ele imprimirá 3.14
        tft.drawFloat(sens_ultra, 1, 80, 50, 2);

        tft.setTextColor(TFT_PURPLE, TFT_BLACK);
        //tft.drawString("SDCard:", 13, 70, 2);

        uint8_t cardType = SD.cardType();
        if (cardType == CARD_MMC)
        {
                tft.drawString("MMC:", 13, 70, 2);
        } else if (cardType == CARD_SD)
        {
                tft.drawString("SDSC:", 14, 70, 2);
        } else if (cardType == CARD_SDHC)
        {
                tft.drawString("SDHC:", 13, 70, 2);
        } else {
                tft.drawString("DESCONHECIDO:", 13, 70, 2);
        }

        uint64_t cardSize = SD.cardSize() / (1024 * 1024);
        //Serial.printf("SD Card Size: %lluMB\n", cardSize);
        tft.drawNumber(cardSize, 63, 70, 2);
        tft.drawString("MB", 105, 76, 1);
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.drawString(datestring, 10, 93, 1);

        if (WiFi.status() == WL_CONNECTED)
        {
                tft.setTextColor(TFT_GREEN, TFT_BLACK);
                tft.drawString("Rede: OK!", 15, 110, 1);
        } else {
                tft.setTextColor(TFT_RED, TFT_BLACK);
                tft.drawString("Rede: Off!", 15, 110, 1);
        }
        if (conn.connected())
        {
                tft.setTextColor(TFT_GREEN, TFT_BLACK);
                tft.drawString("DB: OK!", 75, 110, 1);
        } else {
                tft.setTextColor(TFT_RED, TFT_BLACK);
                tft.drawString("DB: Off!", 75, 110, 1);
        }
}
#endif
