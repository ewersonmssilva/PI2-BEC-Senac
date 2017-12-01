#ifndef envia_recebe_dados_h
#define envia_recebe_dados_h

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <string.h>
#include "config.h"

// Funções
//void conectaDB();
//void envia_recebe();
//void soft_reset();

// INSERT
char INSERT_DATA_DIST[] = "INSERT INTO cisterna.s_ultrasson (user_id, distancia) VALUES (%d,%.1f)";
char dist_query[128];

char INSERT_DATA_FLUX[] = "UPDATE cisterna.s_fluxo SET litros='%.1f' WHERE user_id = '%lu'";
char flux_query[128];

// SELECT
//
// Observe o "%lu" - esse é um espaço reservado para o parâmetro que forneceremos.
// Consulte a documentação sprintf () para mais opções de especificação de formatação
const char QUERY_POP[] = "SELECT s_ultrasson, s_fluxo FROM cisterna.sensores WHERE user_id = %lu ORDER BY criado DESC;";
char selec[128];

const char QUERY_POP_CONS[] = "SELECT litros FROM cisterna.s_fluxo WHERE user_id = %lu";
char select_consumo[32];

WiFiClient client;
MySQL_Connection conn((Client *)&client);

// Inicio da função Reboot
int num_fails;
void soft_reset()
{
        //WiFi.forceSleepBegin();
        //wdt_reset();
        fflush(stdout);
        ESP.restart();
        //while (1)wdt_reset();
}
// Fim da função Reboot

void envia_recebe()
{

        // Inicio gravação DB
        // Inicia a consulta da instância de classe
        MySQL_Cursor *cur_mem_dist = new MySQL_Cursor(&conn);
        // Salvar
        sprintf(dist_query, INSERT_DATA_DIST, usuario, sens_ultra);
        // Execute a consulta
        cur_mem_dist->execute(dist_query);
        // Nota: uma vez que não há resultados, não precisamos ler nenhum dado
        // Deleta ponteiro para liberar memória
        delete cur_mem_dist;
        Serial.println("> Dados distancia gravados.");
        Serial.println("");


        MySQL_Cursor *cur_mem_flux = new MySQL_Cursor(&conn);
        // Salvar
        sprintf(flux_query, INSERT_DATA_FLUX, consumo, usuario);
        // Execute a consulta
        cur_mem_flux->execute(flux_query);
        // Nota: uma vez que não há resultados, não precisamos ler nenhum dado
        // Deleta ponteiro para liberar memória
        delete cur_mem_flux;
        Serial.println("> Dados fluxo gravados.");
        Serial.println("");


        // Fim gravação DB


        // Inicio leitura DB Sensor de fluxo

        //char c = ' ';
        //char number[4];
        //int i = 0;
        int value = 0;
        //String text_string;
        char leitura[10];
        //const char *string



        Serial.println("< Lendo Banco de Dados Fuxo");
        Serial.println("");
        // Inicia a consulta da instância de classe
        MySQL_Cursor *cur_mem_cons = new MySQL_Cursor(&conn);
        // Forneça o parâmetro para a consulta
        // Aqui usamos o QUERY_POP como a string de formato e consulta como o
        // chamado. Isso usa duas vezes a memória, então outra opção seria
        // alocar um buffer para todas as consultas formatadas ou alocar na
        // memória conforme necessário (apenas certifique-se de alocar memória suficiente e
        // livre-a quando terminar!).
        sprintf(select_consumo, QUERY_POP_CONS, usuario);
        // Execute a consulta
        cur_mem_cons->execute(select_consumo);
        // Procure as colunas
        column_names *cols_cons = cur_mem_cons->get_columns();
        Serial.println();
        // Leia as linhas e imprima-as
        row_values *row_cons = NULL;
        do {
                row_cons = cur_mem_cons->get_next_row();
                if (row_cons != NULL) {
                        for (int f = 0; f < cols_cons->num_fields; f++)
                        {
                                Serial.print(row_cons->values[f]);
                                consumo = atoi(row_cons->values[f]);
                                //value = leitura[f] -48;
                        }
                        Serial.println();
                }
        }

        while (row_cons != NULL);
        // Deleta ponteiro para liberar memória
        Serial.print("Leitura: ");
        Serial.println(*leitura);
        //value = atoi(*leitura);
        Serial.println();
        Serial.print("Value: ");
        Serial.print(value);
        Serial.println();
        delete cur_mem_cons;
        Serial.println("< Fim leitura Fuxo");
        // Fim leitura e gravação de dados no DB Sensor de fluxo


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
        sprintf(selec, QUERY_POP, usuario);
        // Execute a consulta
        cur_mem->execute(selec);
        // Procure as colunas e imprima-as
        column_names *cols = cur_mem->get_columns();
        for (int f = 0; f < cols->num_fields; f++)
        {
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
                        for (int f = 0; f < cols->num_fields; f++)
                        {
                                Serial.print(row->values[f]);


                                if (f < cols->num_fields - 1) {
                                        Serial.print(',');
                                }
                        }
                        Serial.println();
                }
        }
        while (row != NULL);
        // Deleta ponteiro para liberar memória
        delete cur_mem;
        {
                Serial.println("< Fim da leitura do Banco de Dados");
                Serial.println("");
                // Desconecta do DB
                Serial.print("Desconectando... >> ");
                conn.close();
                Serial.println("");
                // WiFi.disconnect(true);
        }
        num_fails = 0;           // reseta falhas de conexão
        // Fim leitura e gravação de dados no DB
}

// Inicio da Função de conexão com o Banco de Dados
void conecta_DB()
{
        if (segundos == 10 || segundos == 30 || segundos == 50)
        {
                if (WiFi.status() != WL_CONNECTED) {
                        conecta_wifi();
                }

                // Inicio conexão, leitura e gravação de dados no DB
                if (conn.connected())
                {
                        Serial.println("Conectado com sucesso!");
                        conn.close(); // Fecha a conexão
                        num_fails = 0; // Reiniciar numero de falhas
                } else {
                        Serial.println("Conectando...");
                        if (conn.connect(server_addr, 3306, user, password))
                        {
                                vTaskDelay(pdMS_TO_TICKS(1000)); //ticks para ms (Delay)
                                // Vai para função envia_recebe
                                envia_recebe();
                        } else {
                                num_fails++;
                                Serial.println("Falha na conexão!");
                                if (num_fails == MAX_FAILED_CONNECTS)
                                {
                                        escreve_SD(); // Envia dados dos sensores para o SDCard antes de reiniciar
                                        Serial.println("Ok, é isso. Estou fora. Reiniciando...");
                                        vTaskDelay(pdMS_TO_TICKS(2000)); //ticks para ms (Delay)
                                        // Aqui, pedimos para reiniciar redirecionando para a função de reboot.
                                        soft_reset();
                                }
                        }
                }
        }
}
#endif
