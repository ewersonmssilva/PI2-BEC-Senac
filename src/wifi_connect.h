#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti WiFiMulti;
#include "config.h"

void conecta_wifi()
{
        WiFi.disconnect(true);
        // Inicia a conexão com uma rede Wi-Fi
        WiFiMulti.addAP(ssid, pass);

        Serial.println();
        Serial.println();
        Serial.print("Conectando WiFi... ");

        while (WiFiMulti.run() != WL_CONNECTED)
        {
                Serial.print(".");
                vTaskDelay(pdMS_TO_TICKS(500)); //ticks para ms (Delay)
        }

        Serial.println("");
        Serial.println("WiFi conectado");
        Serial.print("Endereço IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Endereço MAC: ");
        Serial.println(WiFi.macAddress());
        vTaskDelay(pdMS_TO_TICKS(500)); //ticks para ms (Delay)
}
