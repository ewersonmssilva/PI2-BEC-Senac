#ifndef config_h
#define config_h

// Número do pino do sensor de fluxo
unsigned char flowmeter = 15;

// Número do pino do sensor ultrasom
const int trigPin = 2;
const int echoPin = 4;

// WiFi Config
char ssid[] = "XXXXXXX"; // your SSID
char pass[] = "XXXXXX"; // your SSID Password
byte mac[6];

// Definir aqui o numero do usuario para ser identificado no DB
#define usuario 1
// Número máximo de falha de conexão com MySQL antes de reiniciar o sistema.
#define MAX_FAILED_CONNECTS 5

// Configurações do Banco de Dados
IPAddress server_addr(192, 168, 0, 0); // IP of the MySQL server here
char user[] = "root"; // MySQL user login username
char password[] = "XXXXXX"; // MySQL user login password

#endif
