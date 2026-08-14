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

    
    printf("Codigo\tFuncao\tPressao\tNum Alertas\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < NUM_LINHAS; i++) {
        printf("%s\t%d\t%.2f\t%d\n", dutos[i].codigo, dutos[i].funcao, dutos[i].pressao, dutos[i].num_alertas);
    }

    
    float soma_alertas = 0;
    float soma_pressao_producao = 0;
    float soma_pressao_injecao = 0;
    int count_producao = 0;
    int count_injecao = 0;
    int count_producao_acima_200 = 0;
    int count_injecao_abaixo_220 = 0;
    int count_injecao_zero_alertas = 0;

    return 0;
}