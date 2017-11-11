#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "sensor_ultrason.h"
#include "sensor_fluxo.h"
#include "wifi_connect.h"
#include "envia_recebe_dados.h"
#include "data_hora.h"
#include "display.h"

// Funções Multitarefas
void tarefa1( void * pvParameters ) {
  while (true) {
    conta_litros();
    mede_distacia();
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Display();
    Serial.print("   Core: ");
    Serial.print(xPortGetCoreID());
    Serial.print("   ");
    delay(1000);
  }
}

void tarefa2( void * pvParameters ) {
  while (true) {
    conecta_wifi();
    conecta_DB();
    Serial.print("   Core: ");
    Serial.print(xPortGetCoreID());
    Serial.print("   ");
    delay(10000);
  }
}

void setup() {
  Serial.begin(115200);

  // Sensor Utrasônico
  pinMode(trigPin, OUTPUT); // Define o trigPin como uma saída
  pinMode(echoPin, INPUT); // Define o echoPin como uma Entrada

  // Sensor de Fluxo
  // Inicializacao da variavel "flowmeter" como INPUT (pino 15)
  pinMode(flowmeter, INPUT);
  // Anexe uma interrupção ao vetor flowmeter
  attachInterrupt(digitalPinToInterrupt(flowmeter), flow, RISING); // Configuração de interrupção
  // veja http://arduino.cc/en/Reference/attachInterrupt

  // Inicia Display TFT
  tft.init();
  tft.setRotation(1);

  // Imprimo no display informações da inicializacão
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

  // Inicia RTC
  Rtc.Begin();
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);


  // Inicia SDCard
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("Lendo SDCard: ", 10, 105, 1);
  if (!SD.begin()) {
    Serial.println("Falha na montagem do cartão");

    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("Falha!", 90, 105, 1);
    delay ( 2000 );
    tft.fillScreen(TFT_BLACK);
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("Nenhum cartão SD anexado");
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
    Serial.println("DESCONHECIDO");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("Tamanho do SDCard: %lluMB\n", cardSize);
  Serial.printf("Espaço total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Espaço usado: %lluMB\n", SD.usedBytes() / (1024 * 1024));
  delay ( 2000 );
  tft.fillScreen(TFT_BLACK);
  // Inicia multitarefas

  xTaskCreatePinnedToCore(tarefa1, "loop1", 4096, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  xTaskCreatePinnedToCore(tarefa2, "loop2", 4096, NULL, 1, NULL, ARDUINO_RUNNING_CORE);

}

void loop() {
  // Não faça nada aqui
  vTaskDelay(portMAX_DELAY); // aguarde o máximo possível ...

}
