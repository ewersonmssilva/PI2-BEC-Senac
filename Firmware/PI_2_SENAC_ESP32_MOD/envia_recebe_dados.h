#ifndef envia_recebe_dados_h
#define envia_recebe_dados_h

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "config.h"

// Funções
void conectaDB();
void envia_recebe();
void soft_reset();

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

// Inicio da função Reboot
int num_fails;
void soft_reset() {
  //WiFi.forceSleepBegin();
  //wdt_reset();
  fflush(stdout);
  ESP.restart();
  //while (1)wdt_reset();
}
// Fim da função Reboot

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

void envia_recebe() {

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
#endif
