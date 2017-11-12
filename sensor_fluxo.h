#ifndef sensor_fluxo_h
#define sensor_fluxo_h
#include "config.h"

// Sensor de Fluxo
volatile int  flow_frequency;  // Mede os pulsos do sensor de fluxo
unsigned int  l_hour;          // Calcula litro/hora
int litrosAdd = 0;
float litros = 0;
//unsigned char flowmeter = 15;  // Número do pino do sensor de fluxo
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

float sens_fluxo = 0;

void conta_litros() {
  //Sensor Fluxo
  if (contagem_comp != flow_frequency) {

    // Pulse frequency (Hz) = 7.5Q, Q é taxa de fluxo em L/min. (Resultados em +/- 3%)
    l_hour = (flow_frequency * 60 / 7.5); // (Freqüência de pulso x 60 min) / 7.5Q = taxa de fluxo em L/hour
    Serial.print("Fluxo em litros: ");
    Serial.print (l_hour);

    Serial.print("   ");
    Serial.print(l_hour, DEC);            // Imprime L/hour
    Serial.print(" L/hour     ");

    Serial.print(litros);            // Imprime litros/hour
    Serial.print(" Litros");
    contagem_comp = flow_frequency;
  }
  sens_fluxo = litros;
}
#endif

