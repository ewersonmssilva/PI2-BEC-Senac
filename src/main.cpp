#include <Arduino.h>

//#if CONFIG_FREERTOS_UNICORE
//#define ARDUINO_RUNNING_CORE 0
//#else
//#define ARDUINO_RUNNING_CORE 1
//#endif

#include "data_hora.h"
#include "sensor_ultrason.h"
#include "sensor_fluxo.h"
#include "wifi_connect.h"
#include "envia_recebe_dados.h"
#include "display.h"

// Funções Multitarefas
void tarefa1 (void * pvParameters)
{
        while (true)
        {
                Serial.print ("Executando tarefa1 no nucleo: ");
                Serial.println (xPortGetCoreID());
                Serial.print ("   ");
                conta_litros();
                Serial.print ("   ");
                mede_distancia();
                Serial.print ("   ");
                dataehora();
                Display();
                Serial.println ("");
                vTaskDelay (pdMS_TO_TICKS (1000)); //ticks para ms (Delay)
        }
}

void tarefa2 (void * pvParameters)
{
        while (true)
        {
                Serial.print ("Executando tarefa2 no nucleo: ");
                Serial.println (xPortGetCoreID());
                Serial.print ("   ");
                conecta_DB();
                escreve_SD();

                if (minutos == 59 && segundos > 55 && segundos <= 59)
                {
                        WiFi.disconnect (true);
                        vTaskDelay (pdMS_TO_TICKS (20000)); //ticks para ms (Delay)
                }

                Serial.println ("");
                vTaskDelay (pdMS_TO_TICKS (1000)); //ticks para ms (Delay)
        }
}

void setup()
{
        Serial.begin (115200);

        Serial.print ("Executando setup() no nucleo: ");
        Serial.println (xPortGetCoreID());

        // Sensor Utrasônico
        pinMode (trigPin, OUTPUT); // Define o trigPin como uma saída
        pinMode (echoPin, INPUT); // Define o echoPin como uma entrada

        // Sensor de Fluxo
        // Inicializacao da variavel "flowmeter" como INPUT (pino 15)
        pinMode (flowmeter, INPUT);
        // Anexe uma interrupção ao vetor flowmeter
        attachInterrupt (digitalPinToInterrupt (flowmeter), flow, RISING); // Configuração de interrupção
        // veja http://arduino.cc/en/Reference/attachInterrupt

        // Inicialização do Display TFT
        tft.init();
        tft.setRotation (1);

        // Imprime no display informações da inicializacão
        tft.setTextSize (1);
        tft.fillScreen (TFT_BLACK);
        tft.setTextColor (TFT_WHITE, TFT_BLACK);
        tft.drawString ("ENGENHARIA", 10, 5, 1);
        tft.setTextColor (TFT_WHITE, TFT_BLACK);
        tft.drawString ("de", 45, 15, 1);
        tft.setTextColor (TFT_WHITE, TFT_BLACK);
        tft.drawString ("COMPUTACAO", 60, 15, 1);
        tft.setTextColor (TFT_GREEN, TFT_BLACK);
        tft.drawString ("PI2 SENAC", 3, 30, 4);
        tft.setTextColor (TFT_YELLOW, TFT_BLACK);
        tft.drawString ("Iniciando...", 30, 60, 2);

        //Inicialização do RTC DS3231
        Rtc.Begin();

        // nunca assume que o Rtc foi configurado pela última vez por você, então
        // apenas limpe-os para o seu estado necessário
        Rtc.Enable32kHzPin (false);
        Rtc.SetSquareWavePin (DS3231SquareWavePin_ModeNone);

        // Inicialização do SDCard
        tft.setTextColor (TFT_BLUE, TFT_BLACK);
        tft.drawString ("Lendo SDCard: ", 10, 105, 1);

        if (!SD.begin())
        {
                Serial.println ("Falha na montagem do cartão");

                tft.setTextColor (TFT_RED, TFT_BLACK);
                tft.drawString ("Falha!", 90, 105, 1);
                vTaskDelay (pdMS_TO_TICKS (2000)); //ticks para ms (Delay)
                tft.fillScreen (TFT_BLACK);
                return;
        }

        uint8_t cardType = SD.cardType();

        if (cardType == CARD_NONE)
        {
                Serial.println ("Nenhum cartão SD anexado");
                return;
        }

        Serial.print ("SD Card Type: ");

        if (cardType == CARD_MMC)
        {
                Serial.println ("MMC");
        }
        else if (cardType == CARD_SD)
        {
                Serial.println ("SDSC");
        }
        else if (cardType == CARD_SDHC)
        {
                Serial.println ("SDHC");
                tft.setTextColor (TFT_GREEN, TFT_BLACK);
                tft.drawString ("OK!", 90, 105, 1);
        }
        else
        {
                Serial.println ("DESCONHECIDO");
        }

        uint64_t cardSize = SD.cardSize() / (1024 * 1024);
        Serial.printf ("Tamanho do SDCard: %lluMB\n", cardSize);
        Serial.printf("Espaço total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
        Serial.printf("Espaço usado: %lluMB\n", SD.usedBytes() / (1024 * 1024));
        vTaskDelay (pdMS_TO_TICKS (2000)); //ticks para ms (Delay)
        tft.fillScreen (TFT_BLACK);

        // Inicialização das multitarefas
        xTaskCreate (tarefa1, "loop1", 4096, NULL, 1, NULL);
        xTaskCreate (tarefa2, "loop2", 4096, NULL, 1, NULL);
}

void loop()
{
        Serial.print ("loop executando no nucleo: ");
        Serial.println (xPortGetCoreID());
        // Não faça nada aqui
        vTaskDelay (portMAX_DELAY); // aguarde o máximo possível ...
}
