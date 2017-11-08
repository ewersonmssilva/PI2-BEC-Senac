//#include "config.h"
#include "sensor_ultrasom.h"
#include "sensor_fluxo.h"
//#include "wifi_conex.h"
#include "envia_recebe_dados.h"
#include "data_hora.h"
#include "display.h"

void setup() {
  Serial.begin(115200);

  // Sensor Utrasom
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Sensor de Fluxo
  // Inicialização da variável "buttonPin" como INPUT (D2 pin)
  pinMode(flowmeter, INPUT);
  // Anexe uma interrupção ao vetor flowmeter
  attachInterrupt(digitalPinToInterrupt(flowmeter), flow, RISING); // Setup Interrupt
  // see http://arduino.cc/en/Reference/attachInterrupt

  // Inicia Display TFT
  tft.init();
  tft.setRotation(1);

// Imprimo no display informações da inicialização
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("ENGENHARIA", 10, 5, 1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("de", 45, 15, 1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("COMPUTACAO", 60, 15, 1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("PI2 SENAC", 3, 30, 4);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("Iniciando...", 30, 60, 2);

  while (!Serial); // Aguarda a porta serial conectar

  // Inicio da seção WiFi
  WiFi.begin(ssid, pass);
  // Aguarde a conexão
  Serial.print ( "Conectando na rede." );

  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("Conectando rede: ", 10, 90, 1);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println ( "." );
  Serial.print ( "Conectado a rede: " );

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("OK!", 108, 90, 1);

  Serial.println ( ssid );
  Serial.print ( "Endereço IP: " );
  Serial.println ( WiFi.localIP() );
  Serial.print("Endereço MAC: ");
  WiFi.macAddress(mac);
  for (int i = 0; i < 6; i++) {
    Serial.print(mac[i], HEX);
    if (i < 5) {
      Serial.print(":");
    }
  }
  Serial.println("");
  // Fim da seção WiFi

  // Inicia RTC
  Rtc.Begin();
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);


  // Inicia SDCard
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("Lendo SDCard: ", 10, 105, 1);
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");

    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("Falha!", 90, 105, 1);
    delay ( 2000 );
    tft.fillScreen(TFT_BLACK);
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString("OK!", 90, 105, 1);
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
  delay ( 2000 );
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  delay(2000);

  // Chama Função dos sensores
  conta_litros();
  mede_distacia();

  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);

  Serial.println();

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  //conectaDB();

  Display();
}
