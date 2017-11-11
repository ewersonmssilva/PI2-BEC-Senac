#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti WiFiMulti;
#include "config.h"

void connectToNetwork() {
    // Inicia a conexão com uma rede Wi-Fi
    WiFiMulti.addAP(ssid, pass);

    Serial.println();
    Serial.println();
    Serial.print("Conectando WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("Endereço IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("Endereço MAC: ");
    Serial.println(WiFi.macAddress());

    delay(500);
}
