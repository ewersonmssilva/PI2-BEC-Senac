#ifndef data_hora_h
#define data_hora_h

#include <Wire.h>        //Biblioteca para manipulação do protocolo I2C
#include <DS3231.h>      //Biblioteca para manipulação do DS3231

DS3231 rtc;              //Criação do objeto do tipo DS3231
RTCDateTime dt;   //Criação do objeto do tipo RTCDateTime

// --- Variáveis Globais ---
int segundos = 0, minutos = 0, horas = 0;   //variáveis do relógio
int dia = 0, mes = 0, ano = 0;

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

/*
  // Acessa o Servidor NTP e imprime data e hora
  const char* NTP_SERVER = "a.st1.ntp.br";
  const char* TZ_INFO    = "EST2EDT4,M3.2.0/02:00:00,M11.1.0/02:00:00";
  struct tm timeinfo;
  void atualizaData() {
  configTzTime(TZ_INFO, NTP_SERVER);
  if (getLocalTime(&timeinfo)) {
    Serial.print(&timeinfo, "%m/%d/%Y %H:%M:%S ");
    Serial.println(&timeinfo);
  }
  }
*/
/*
  // Funções do RTC
  char datestring[20];
  #define countof(a) (sizeof(a) / sizeof(a[0]))

  void dataehora() {
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
  }
*/
#endif
