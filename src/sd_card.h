#ifndef sd_card_h
#define sd_card_h

#include <FS.h>
#include <SD.h>
#include <SPI.h>

uint64_t cardSize = SD.cardSize() / (1024 * 1024);
//Serial.printf("SD Card Size: %lluMB\n", cardSize);
File myFile;                   //Cria um ponteiro para arquivo

void appendFileSfluxo()
{
        dataehora();
        RtcDateTime now = Rtc.GetDateTime();

        //Cria string de dados para armazenar no cartão SD
        //Utilizando arquivo do tipo Comma Separete Value
        String dataString = String(sens_fluxo) + ", " + String(now);

        //Abre o arquivo para escrita
        //Apenas um arquivo pode ser aberto de cada vez
        File myFile = SD.open("/s_fluxo.csv", FILE_APPEND);
        if (myFile)
        {
                myFile.println(dataString);
                myFile.close();
                Serial.println(dataString);
        } //end if logFile
        else
        {
                Serial.println("Erro ao abrir arquivo para escrita final");
        }
}

void appendFileSultrason()
{
        dataehora();
        RtcDateTime now = Rtc.GetDateTime();

        //Cria string de dados para armazenar no cartão SD
        //Utilizando arquivo do tipo Comma Separete Value
        String dataString = String(sens_ultra) + ", " + String(now);

        //Abre o arquivo para escrita
        //Apenas um arquivo pode ser aberto de cada vez
        File myFile = SD.open("/s_ultrason.csv", FILE_APPEND);
        if (myFile)
        {
                myFile.println(dataString);
                myFile.close();
                Serial.println(dataString);
        } //end if logFile
        else
        {
                Serial.println("Erro ao abrir arquivo para escrita final");
        }
}

void escreve_SD() {
        if (minutos == 20 && segundos == 22 || minutos == 40 && segundos == 22 || minutos == 58 && segundos == 22)
        {
                //writeFile(SD, "/sensores.txt", datestring);
                //appendFile(SD, "/sensores.txt", valor);
                appendFileSfluxo();
                appendFileSultrason();
                //appendFile(SD, "/sensores.txt", "Fluxo  ");
                //appendFile(SD, "/sensores.txt", " Ultra ");
                //appendFile(SD, "/sensores.txt", datestring);
        }
}
#endif
