#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 120
#define MAX_ALERTAS 15

struct Duto {
    char codigo[10];
    int funcao;
    float pressao;
    int alertas;
};

int main()
{
    srand(time(NULL));

    struct Duto dutos[TOTAL], ord[TOTAL], aux;
    float soma_alertas = 0;
    float soma_prod = 0;
    float soma_inj = 0;
    float med_alertas, med_prod, med_inj;
    float pct_prod_200, pct_inj_220, pct_inj_zero;
    int qtd_prod = 0, qtd_inj = 0;
    int prod_200 = 0, inj_220 = 0, inj_zero = 0;

    for (int i = 0; i < TOTAL; i++) {
        if (i % 2 == 0) {
            sprintf(dutos[i].codigo, "P-%d", 77001 + i);
            dutos[i].funcao = 1;
            dutos[i].pressao = 80.0 + ((float)rand() / RAND_MAX) * (250.0 - 80.0);
        } else {
            sprintf(dutos[i].codigo, "I-%d", 77001 + i);
            dutos[i].funcao = 2;
            dutos[i].pressao = 150.0 + ((float)rand() / RAND_MAX) * (400.0 - 150.0);
        }

        dutos[i].alertas = rand() % (MAX_ALERTAS + 1);
        ord[i] = dutos[i];
    }

    printf("\n+---------------------------------------------------------------+\n");
    printf("| TELEMETRIA DOS DUTOS - ORDEM DE GERACAO                       |\n");
    printf("+------------+------+------------+---------------+-------------+\n");
    printf("| %-10s | %-4s | %-10s | %-13s | %-11s |\n", "Codigo", "Func", "Funcao", "Pressao(bar)", "Alertas");
    printf("+------------+------+------------+---------------+-------------+\n");

    for (int i = 0; i < TOTAL; i++) {
        printf("| %-10s | %4d | %-10s | %13.2f | %11d |\n",
               dutos[i].codigo,
               dutos[i].funcao,
               dutos[i].funcao == 1 ? "Producao" : "Injecao",
               dutos[i].pressao,
               dutos[i].alertas);
    }

    printf("+------------+------+------------+---------------+-------------+\n");

    for (int i = 0; i < TOTAL; i++) {
        soma_alertas += dutos[i].alertas;

        if (dutos[i].funcao == 1) {
            soma_prod += dutos[i].pressao;
            qtd_prod++;

            if (dutos[i].pressao > 200.0) {
                prod_200++;
            }
        } else {
            soma_inj += dutos[i].pressao;
            qtd_inj++;

            if (dutos[i].pressao < 220.0) {
                inj_220++;
            }

            if (dutos[i].alertas == 0) {
                inj_zero++;
            }
        }
    }

    med_alertas = soma_alertas / TOTAL;
    med_prod = soma_prod / qtd_prod;
    med_inj = soma_inj / qtd_inj;
    pct_prod_200 = ((float)prod_200 / qtd_prod) * 100.0;
    pct_inj_220 = ((float)inj_220 / qtd_inj) * 100.0;
    pct_inj_zero = ((float)inj_zero / qtd_inj) * 100.0;

    printf("\n+-----------------------------------------------------------------------+\n");
    printf("|                         CALCULOS E ANALISES                          |\n");
    printf("+----+------------------------------------------------+-----------------+\n");
    printf("| %-2s | %-46s | %15s |\n", "It", "Descricao", "Resultado");
    printf("+----+------------------------------------------------+-----------------+\n");
    printf("| %-2s | %-46s | %15.2f |\n", "a", "Media geral de alertas", med_alertas);
    printf("| %-2s | %-46s | %12.2f bar |\n", "b1", "Media de pressao - Producao", med_prod);
    printf("| %-2s | %-46s | %12.2f bar |\n", "b2", "Media de pressao - Injecao", med_inj);
    printf("| %-2s | %-46s | %13.2f %% |\n", "c1", "Producao com pressao acima de 200.0 bar", pct_prod_200);
    printf("| %-2s | %-46s | %13.2f %% |\n", "c2", "Injecao com pressao abaixo de 220.0 bar", pct_inj_220);
    printf("| %-2s | %-46s | %13.2f %% |\n", "d", "Injecao com zero alertas", pct_inj_zero);
    printf("+----+------------------------------------------------+-----------------+\n");

    for (int i = 0; i < TOTAL - 1; i++) {
        for (int j = i + 1; j < TOTAL; j++) {
            if (ord[i].alertas < ord[j].alertas) {
                aux = ord[i];
                ord[i] = ord[j];
                ord[j] = aux;
            }
        }
    }

    printf("\n+---------------------------------------------------------------+\n");
    printf("| RELATORIO ORDENADO POR ALERTAS - DECRESCENTE                  |\n");
    printf("+------------+------+------------+---------------+-------------+\n");
    printf("| %-10s | %-4s | %-10s | %-13s | %-11s |\n", "Codigo", "Func", "Funcao", "Pressao(bar)", "Alertas");
    printf("+------------+------+------------+---------------+-------------+\n");

    for (int i = 0; i < TOTAL; i++) {
        printf("| %-10s | %4d | %-10s | %13.2f | %11d |\n",
               ord[i].codigo,
               ord[i].funcao,
               ord[i].funcao == 1 ? "Producao" : "Injecao",
               ord[i].pressao,
               ord[i].alertas);
    }

    printf("+------------+------+------------+---------------+-------------+\n");

    return 0;
}
