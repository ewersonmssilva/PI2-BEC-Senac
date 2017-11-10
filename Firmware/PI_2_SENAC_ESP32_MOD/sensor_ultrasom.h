#ifndef sensor_ultrason_h
#define sensor_ultrason_h

#include "config.h"

// Inicio da função dos sensores
float media (int n, float *v_ultrason);
float sens_ultra = 10;
long duration;
float distance;
float v_ultrason[10];
float media_ultra;
int i;

void mede_distacia() {

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
#endif
