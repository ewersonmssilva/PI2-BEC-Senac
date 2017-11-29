#ifndef config_h
#define config_h

// Número do pino do sensor de fluxo
unsigned char flowmeter = 15;

// Número do pino do sensor ultrasom
const int trigPin = 2;
const int echoPin = 4;

// WiFi Config
const char* ssid = "XT1635-01"; // Seu SSID
const char* pass =  "senha123"; // Sua senha

// Definir aqui o numero do usuario para ser identificado no DB
#define usuario 1
// Número máximo de falha de conexão com MySQL antes de reiniciar o sistema.
#define MAX_FAILED_CONNECTS 4

// Configurações do Banco de Dados
IPAddress server_addr(192, 168, 43, 232); // IP do servidor MySQL
char user[] = "root"; // Nome de login do usuário MySQL
char password[] = "senha"; // Senha de login do usuário MySQL

#endif
