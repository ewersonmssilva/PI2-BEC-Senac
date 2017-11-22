#ifndef data_hora_h
#define data_hora_h

#include <Wire.h>        //Biblioteca para manipulação do protocolo I2C
//////////////#include <DS3231.h>      //Biblioteca para manipulação do DS3231
#include <WiFi.h>
/////////////DS3231 rtc;              //Criação do objeto do tipo DS3231
////////////RTCDateTime dt;   //Criação do objeto do tipo RTCDateTime
#include <time.h>


#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
// --- Variáveis Globais ---
int segundos = 0, minutos = 0, horas = 0;   //variáveis do relógio
int dia = 0, mes = 0, ano = 0;

time_t now;

void printDateTime(const RtcDateTime& dt);
char datestring[20];
#define countof(a) (sizeof(a) / sizeof(a[0]))

/*
  void atualiza()
  {
  dt = rtc.getDateTime();     //Atribuindo valores instantâneos de
  //data e hora à instância dt
  mes = dt.month;
  dia = dt.day;
  ano = dt.year;
  horas = dt.hour;
  minutos = dt.minute;
  segundos = dt.second;
  }


  char datestring[20];
  #define countof(a) (sizeof(a) / sizeof(a[0]))
  void dataehora() {
  if (segundos > 59) {
    atualiza();
  }

  datestring[20];
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             mes,
             dia,
             ano,
             horas,
             minutos,
             segundos);
  Serial.print(datestring);
  segundos ++;
  } //end mostra hora

*/


// Acessa o Servidor NTP e imprime data e hora
const char* NTP_SERVER = "a.st1.ntp.br";
const char* TZ_INFO    = "EST2EDT4,M3.2.0/02:00:00,M11.1.0/02:00:00";
struct tm timeinfo;

void ntp_dataehora() {
  configTzTime(TZ_INFO, NTP_SERVER);
  if (getLocalTime(&timeinfo)) {
    Serial.print(&timeinfo, "%m/%d/%Y %H:%M:%S ");
    // teste = timeinfo.tm_hour;
    // Serial.print("teste: ");
    // Serial.println(teste);

    Serial.println(&timeinfo);

    mes = timeinfo.tm_mon;
    dia = timeinfo.tm_mday;
    ano = timeinfo.tm_year + 1900;
    horas = timeinfo.tm_hour;
    minutos = timeinfo.tm_min;
    segundos = timeinfo.tm_sec;


    RtcDateTime ntp_timestamp = time(&now);
    RtcDateTime now = Rtc.GetDateTime();

    if (now > ntp_timestamp + 5 || now < ntp_timestamp - 5)
    {
      RtcDateTime now = Rtc.GetDateTime();
      printDateTime(now);
      Serial.println(" O RTC está desatualizado  (Atualizando)");
      Rtc.SetDateTime(ntp_timestamp);
    }


    //char strftime_buf[25];
    //strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo); // Converte struct em Char
    //int i, a, b, c, d;
    /*
      char procura_char = ':';
      for (i = 0; i < 63; i++) {
      if (strftime_buf[i] == procura_char) { // Procura um charactere no vetor
        Serial.print ("   Char: ");
        Serial.print (i);
        Serial.print ("  ");

        a = strftime_buf[i - 2] - 48; // Converte char em int
        b = strftime_buf[i - 1] - 48; // Converte char em int
        horas = (a * 10) + b;     // Multiplica e soma para juntar os numeros
        Serial.print(horas);
        Serial.print(":");

        a = strftime_buf[i + 1] - 48; // Converte char em int
        b = strftime_buf[i + 2] - 48; // Converte char em int
        minutos = (a * 10) + b;   // Multiplica e soma para juntar os numeros
        Serial.print(minutos);
        Serial.print(":");

        a = strftime_buf[i + 4] - 48; // Converte char em int
        b = strftime_buf[i + 5] - 48; // Converte char em int
        segundos = (a * 10) + b;  // Multiplica e soma para juntar os numeros
        Serial.print(segundos);
        break;
      }
    */
    /*
        a = strftime_buf[11] - 48; // Converte char em int
        b = strftime_buf[12] - 48; // Converte char em int
        horas = (a * 10) + b;     // Multiplica e soma para juntar os numeros
        Serial.print(horas);
        Serial.print(":");

        a = strftime_buf[14] - 48; // Converte char em int
        b = strftime_buf[15] - 48; // Converte char em int
        minutos = (a * 10) + b;   // Multiplica e soma para juntar os numeros
        Serial.print(minutos);
        Serial.print(":");

        a = strftime_buf[17] - 48; // Converte char em int
        b = strftime_buf[18] - 48; // Converte char em int
        segundos = (a * 10) + b;  // Multiplica e soma para juntar os numeros
        Serial.print(segundos);

        Serial.print("  ");

        a = strftime_buf[0] - 48; // Converte char em int
        b = strftime_buf[1] - 48; // Converte char em int
        mes = (a * 10) + b;  // Multiplica e soma para juntar os numeros

        a = strftime_buf[8] - 48; // Converte char em int
        b = strftime_buf[9] - 48; // Converte char em int
        dia = (a * 10) + b;  // Multiplica e soma para juntar os numeros

        a = strftime_buf[20] - 48; // Converte char em int
        b = strftime_buf[21] - 48; // Converte char em int
        c = strftime_buf[22] - 48; // Converte char em int
        d = strftime_buf[23] - 48; // Converte char em int
        ano = (a * 1000) + (b * 100) + (c * 10) + d;  // Multiplica e soma para juntar os numeros
        Serial.println(ano);*/

  }


  {
    datestring[20];
    snprintf_P(datestring,
               countof(datestring),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
               mes,
               dia,
               ano,
               horas,
               minutos,
               segundos);
    Serial.print(datestring);
    Serial.print("  Data e Hora no NTP ");
  }
}
/*//////////////////////////////////

  // Funções do RTC
  //char datestring[20];
  //#define countof(a) (sizeof(a) / sizeof(a[0]))

  void rtc_dataehora() {
  //atualiza();

  datestring[20];
  //Atribuindo valores instantâneos de
  //data e hora à instância dt
  dt = rtc.getDateTime();
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.month,
             dt.day,
             dt.year,
             dt.hour,
             dt.minute,
             dt.second);
  Serial.print(datestring);
  mes = dt.month;
  dia = dt.day;
  ano = dt.year;
  horas = dt.hour;
  minutos = dt.minute;
  segundos = dt.second;
  Serial.println("Data e Hora no RTC");
  }
*//////////////////////////////////


void printDateTime(const RtcDateTime& dt)
{
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
  mes = dt.Month();
  dia = dt.Day();
  ano = dt.Year();
  horas = dt.Hour();
  minutos = dt.Minute();
  segundos = dt.Second();
  Serial.println(" Data e Hora no RTC");
}

void rtc_dataehora ()
{
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  Serial.println();

}




void dataehora() {
  if (WiFi.status() == WL_CONNECTED) {
    ntp_dataehora();
  } else {
    rtc_dataehora();
  }
}

#endif
