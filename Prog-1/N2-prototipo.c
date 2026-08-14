#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LINHAS 120
#define MAX_ALERTAS 15
#define MIN_PRESSAO_PRODUCAO 80.0
#define MAX_PRESSAO_PRODUCAO 250.0
#define MIN_PRESSAO_INJECAO 150
#define MAX_PRESSAO_INJECAO 400.0

int main() 
{
    srand(time(NULL));  

    struct Duto {
        char codigo[10];
        int funcao;
        float pressao;
        int num_alertas;
    } dutos[NUM_LINHAS];


    for (int i = 0; i < NUM_LINHAS; i++) {
        if (i % 2 == 0) { 
            sprintf(dutos[i].codigo, "P-%d", 77001 + i);
            dutos[i].funcao = 1;
            dutos[i].pressao = MIN_PRESSAO_PRODUCAO + ((float)rand() / RAND_MAX) * (MAX_PRESSAO_PRODUCAO - MIN_PRESSAO_PRODUCAO);
        } else { 
            sprintf(dutos[i].codigo, "I-%d", 77001 + i);
            dutos[i].funcao = 2;
            dutos[i].pressao = MIN_PRESSAO_INJECAO + ((float)rand() / RAND_MAX) * (MAX_PRESSAO_INJECAO - MIN_PRESSAO_INJECAO);
        }
        dutos[i].num_alertas = rand() % (MAX_ALERTAS + 1); 
    }

    
    float soma_alertas = 0;
    float soma_pressao_producao = 0;
    float soma_pressao_injecao = 0;
    int count_producao = 0;
    int count_injecao = 0;
    int count_producao_acima_200 = 0;
    int count_injecao_abaixo_220 = 0;
    int count_injecao_zero_alertas = 0;

    for (int i = 0; i < NUM_LINHAS; i++) {
        soma_alertas += dutos[i].num_alertas;

        if (dutos[i].funcao == 1) {
            soma_pressao_producao += dutos[i].pressao;
            count_producao++;
            if (dutos[i].pressao > 200.0) {
                count_producao_acima_200++;
            }
        } else {
            soma_pressao_injecao += dutos[i].pressao;
            count_injecao++;
            if (dutos[i].pressao < 220.0) {
                count_injecao_abaixo_220++;
            }
            if (dutos[i].num_alertas == 0) {
                count_injecao_zero_alertas++;
            }
        }

        printf("Codigo: %s, Funcao: %d, Pressao: %.2f, Alertas: %d\n", dutos[i].codigo, dutos[i].funcao, dutos[i].pressao, dutos[i].num_alertas);
        
    }

    //calculos
    float media_alertas = soma_alertas / NUM_LINHAS;
    float media_pressao_producao = soma_pressao_producao / count_producao;
    float media_pressao_injecao = soma_pressao_injecao / count_injecao;
    float percentual_producao_acima_200 = ((float)count_producao_acima_200 / count_producao) * 100.0;
    float percentual_injecao_abaixo_220 = ((float)count_injecao_abaixo_220 / count_injecao) * 100.0;
    float percentual_injecao_zero_alertas = ((float)count_injecao_zero_alertas / count_injecao) * 100.0;

    printf("\nMedia geral de alertas: %.2f\n", media_alertas);
    printf("Media de pressao operacional por funcao:\n");   
    printf("Producao: %.2f\n", media_pressao_producao); 
    printf("Injecao: %.2f\n", media_pressao_injecao);
    printf("Percentual de linhas de producao com pressao superior a 200.0 bar: %.2f%%\n", percentual_producao_acima_200);
    printf("Percentual de linhas de injecao com pressao inferior a 220.0 bar: %.2f%%\n", percentual_injecao_abaixo_220);
    printf("Percentual de linhas de injecao sem alertas: %.2f%%\n", percentual_injecao_zero_alertas);
    

    return 0;
}