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

// Acessa o Servidor NTP e imprime data e hora
const char* NTP_SERVER = "a.st1.ntp.br";
const char* TZ_INFO    = "EST2EDT4,M3.2.0/02:00:00,M11.1.0/02:00:00";
struct tm timeinfo;

void ntp_dataehora() {
  configTzTime(TZ_INFO, NTP_SERVER);
  if (getLocalTime(&timeinfo)) {
    Serial.print(&timeinfo, "%m/%d/%Y %H:%M:%S ");
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
