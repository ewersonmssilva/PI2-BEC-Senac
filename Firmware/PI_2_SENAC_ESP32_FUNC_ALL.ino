#include <WiFi.h>
#include <WiFiMulti.h>

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Ultrasonic.h>

//Display TFT
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
//#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
#define TFT_GREY 0x5AEB // New colour
unsigned long targetTime = 0; // Used for testing draw times

/*
  SoftwareWire myWire(SDA, SCL);
  RtcDS3231<SoftwareWire> Rtc(myWire);
  /* for normal hardware wire use below */
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
/* for normal hardware wire use above */

// SDCard
#include <FS.h>
#include <SD.h>
#include <SPI.h>

// Definir aqui o numero do usuario
#define usuario 1

// DB Config
IPAddress server_addr(192, 168, 0, 36); // IP of the MySQL server here
char user[] = "root"; // MySQL user login username
char password[] = "senha"; // MySQL user login password

// WiFi Config
char ssid[] = "NetVirtua-80"; // your SSID
char pass[] = "ferreirasantos"; // your SSID Password
byte mac[6];

// INSERT
char INSERT_DATA[] = "INSERT INTO cisterna.sensores (user_id, s_ultrasson, s_fluxo) VALUES (%d,%d,%d)";
char query[128];
char temperature[10];

// SELECT
//
// Observe o "%lu" - esse é um espaço reservado para o parâmetro que forneceremos.
// Consulte a documentação sprintf () para mais opções de especificação de formatação
const char QUERY_POP[] = "SELECT s_ultrasson, s_fluxo FROM cisterna.sensores WHERE user_id > %lu ORDER BY criado DESC;";
char selec[128];

WiFiClient client;
MySQL_Connection conn((Client *)&client);

//#include <Ultrasonic.h>

/*
  Pass as a parameter the trigger and echo pin, respectively,
  or only the signal pin (for sensors 3 pins), like:
  Ultrasonic ultrasonic(13);
  WeMos portas D6 e D7
*/
//Ultrasonic ultrasonic(02, 04);
// defines pins numbers
const int trigPin = 2;
const int echoPin = 4;

// defines variables
long duration;
float distance;

// Sensor de Fluxo
volatile int  flow_frequency;  // Mede os pulsos do sensor de fluxo
unsigned int  l_hour;          // Calculado litros/hour
int litrosAdd = 0;
float litros = 0;
unsigned char flowmeter = 15;  // Número do pino do sensor de fluxo
int contagem_comp = 0;

// Função de interrupção, de modo que a contagem do pulso "aumenta" não interfira com o resto do código (attachInterrupt)
void flow ()                  // Função de interrupção
{
  flow_frequency++;
  // Se a contagem de transições (de baixo para alto, "subida") é superior a 440, conte com mais um litro.
  // pulso por litro +/- 450 "www.hobbytronics.co.uk/yf-s201-water-flow-meter"
  if (flow_frequency > 440 )
  {
    litrosAdd++;
    flow_frequency = 0;
  }
  litros = litrosAdd + flow_frequency / 450.0;
}

void setup() {
  Serial.begin(115200);

  // Sendor Utrasom
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Sendor de Fluxo
  // Inicialização da variável "buttonPin" como INPUT (D2 pin)
  pinMode(flowmeter, INPUT);
  // Anexe uma interrupção ao vetor flowmeter
  attachInterrupt(digitalPinToInterrupt(flowmeter), flow, RISING); // Setup Interrupt
  // see http://arduino.cc/en/Reference/attachInterrupt

  // Display TFT
  tft.init();
  tft.setRotation(1);

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


  // RTC
  Rtc.Begin();
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);

  // SDCard
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

// Inicio Função Rtc DS3231
char datestring[20];
#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
  //char datestring[20];
  datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
}


// Inicio da função Reboot
int num_fails;
#define MAX_FAILED_CONNECTS 5   // Número máximo de conexões com falha no MySQL

void soft_reset() {
  //WiFi.forceSleepBegin();
  //wdt_reset();
  fflush(stdout);
  ESP.restart();
  //while (1)wdt_reset();
}
// Fim da função Reboot

// Inicio da função dos sensores
float sens_fluxo = 0;
float sens_ultra = 0;

float v_ultrason[10];
float media_ultra;
int i;

void sensores() {
  /*Serial.print("Distance in CM: ");
    // Pass INC as a parameter to get the distance in inches
    Serial.println(ultrasonic.distanceRead());
    sens_ultra = ultrasonic.distanceRead();
    //Sensor de Fluxo para contagem apenas
    sens_fluxo = sens_fluxo + 1;
    if (sens_fluxo > 10 || sens_fluxo < 0 )
    sens_fluxo = 0;
    //delay(1000);
  */

  // Sensor Utrasom
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  if (distance < distance + 1 || distance > distance - 1) {
    v_ultrason[i] = distance;
    i++;
    //sens_ultra = distance;
  }
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);

  /* leitura das Medidas
    for (i = 0; i < 10; i++)
    {
    printf("Digite os valores das notas: ");
    scanf("%f", &v_ultrason[i]);
    }
  */
  //chamada da função
  if (i > 10) {
    sens_ultra = media(10, v_ultrason);
  }
  Serial.print("    Media: ");
  Serial.println(sens_ultra);



  //Sensor Fluxo
  if (contagem_comp != flow_frequency) {

    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
    l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flow rate in L/hour
    Serial.print("Flow 1 in Liters: ");
    Serial.print (l_hour);

    //flow_frequency = 0;                   // Reset Contador

    Serial.print("   ");
    Serial.print(l_hour, DEC);            // Print litres/hour
    Serial.print(" L/hour     ");

    Serial.print(litros);            // Print litres/hour
    Serial.println(" Litros");
    contagem_comp = flow_frequency;
  }
  sens_fluxo = litros;

}
/* Função para cálculo da média
   Parâmetros:
      Recebe a quantidade de elementos n
      Recebe o endereço inicial do vetor notas em *v_ultrason
   Retorno:
     Retorna a media na variavel m
*/
float media (int n, float *v_ultrason)
{
  //int i;
  float m = 0, soma = 0;

  //fazendo a somatória das medidas
  for (i = 0; i < n; i++)
    soma = soma + v_ultrason[i];

  //dividindo pela quantidade de elementos n
  m = soma / n;
  //sens_ultra = m;
  i = 0;
  //retornando a média
  return m;
}

// Inicio da Função de conexão com o Banco de Dados
void conectaDB() {
  // Inicio conexão, leitura e gravação de dados no DB
  if (conn.connected()) {
    Serial.println("Conectado com sucesso!");
    conn.close();                  // close the connection
    num_fails = 0;                 // reset failures
  } else {
    Serial.println("Conectando...");
    if (conn.connect(server_addr, 3306, user, password)) {
      delay(1000);
      // Vai para função envia_recebe
      envia_recebe();
    } else {
      num_fails++;
      Serial.println("Falha na conexão!");
      if (num_fails == MAX_FAILED_CONNECTS) {
        Serial.println("Ok, é isso. Estou fora. Reiniciando...");
        delay(2000);
        // Aqui, pedimos para WeMos reiniciar redirecionando para a função de reboot.
        soft_reset();
      }
    }
  }
}


void envia_recebe () {

  // Inicio gravação DB
  //
  Serial.println("> Gravando dados.");
  // Inicia a consulta da instância de classe
  MySQL_Cursor *cur_memi = new MySQL_Cursor(&conn);
  // Salvar
  //dtostrf(50.125, 1, 1, temperature);
  sprintf(query, INSERT_DATA, usuario, sens_ultra, sens_fluxo);
  // Execute a consulta
  cur_memi->execute(query);
  // Nota: uma vez que não há resultados, não precisamos ler nenhum dado
  // Deleta ponteiro para liberar memória
  delete cur_memi;
  Serial.println("> Dados gravados.");
  Serial.println("");
  // Fim gravação DB
  //
  // Inicio leitura DB
  Serial.println("< Lendo Banco de Dados");
  Serial.println("");
  // Inicia a consulta da instância de classe
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Forneça o parâmetro para a consulta
  // Aqui usamos o QUERY_POP como a string de formato e consulta como o
  // chamado. Isso usa duas vezes a memória, então outra opção seria
  // alocar um buffer para todas as consultas formatadas ou alocar na
  // memória conforme necessário (apenas certifique-se de alocar memória suficiente e
  // livre-a quando terminar!).
  sprintf(selec, QUERY_POP, 0);
  // Execute a consulta
  cur_mem->execute(selec);
  // Procure as colunas e imprima-as
  column_names *cols = cur_mem->get_columns();
  for (int f = 0; f < cols->num_fields; f++) {
    Serial.print(cols->fields[f]->name);
    if (f < cols->num_fields - 1) {
      Serial.print(',');
    }
  }
  Serial.println();
  // Leia as linhas e imprima-as
  row_values *row = NULL;
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      for (int f = 0; f < cols->num_fields; f++) {
        Serial.print(row->values[f]);
        if (f < cols->num_fields - 1) {
          Serial.print(',');
        }
      }
      Serial.println();
    }
  } while (row != NULL);
  // Deleta ponteiro para liberar memória
  delete cur_mem;
  {
    Serial.println("< Fim da leitura do Banco de Dados");
    Serial.println("");
    // Desconecta do DB
    Serial.print("Desconectando... >> ");
    conn.close();
    Serial.println("");
  }
  num_fails = 0;                 // reseta falhas de conexão
  // Fim leitura e gravação de dados no DB
}

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

void loop() {
  delay(2000);

  sensores();

  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);

  Serial.println();

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  //conectaDB();

  Display();

}
