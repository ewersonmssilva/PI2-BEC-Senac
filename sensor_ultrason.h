#ifndef sensor_ultrason_h
#define sensor_ultrason_h
#include "config.h"

// Inicio da função dos sensores
float media (int n, float *v_ultrason);
float sens_ultra = 0;
long duration;
float distance;
float v_ultrason[10];
float media_ultra;
int i;

void mede_distacia() {

  // Sensor Utrason
  // Limpa o trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Define o trigPin no estado HIGH durante 10 micro segundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lê o echoPin, retorna o tempo de viagem da onda sonora em microssegundos
  duration = pulseIn(echoPin, HIGH);

  // Calculando a distância
  distance = duration * 0.034 / 2;

  if (distance < distance + 1 || distance > distance - 1) {
    v_ultrason[i] = distance;
    i++;
  }
  // Imprime a distância no Monitor Serial
  Serial.print("Distância: ");
  Serial.print(distance);

  //chamada da função
  if (i > 10) {
    sens_ultra = media(10, v_ultrason);
  }
  Serial.print("    Media: ");
  Serial.print(sens_ultra);

}

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
#endif
