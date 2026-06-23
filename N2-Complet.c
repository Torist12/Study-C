#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_LINHAS 120
#define MAX_ALERTAS 15
#define MIN_PRESSAO_PRODUCAO 80.0
#define MAX_PRESSAO_PRODUCAO 250.0
#define MIN_PRESSAO_INJECAO 150
#define MAX_PRESSAO_INJECAO 400.0

struct Duto {
    char codigo[10];
    int funcao;
    float pressao;
    int alertas;
};

const char *nome_funcao(int funcao) {
    return funcao == 1 ? "Producao" : "Injecao";
}

float gera_pressao(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

int ord_alertas(const void *a, const void *b) {
    const struct Duto *x = (const struct Duto *)a;
    const struct Duto *y = (const struct Duto *)b;

    if (x->alertas != y->alertas) {
        return y->alertas - x->alertas;
    }

    return strcmp(x->codigo, y->codigo);
}

void mostra_tabela(struct Duto dutos[], int n, const char *titulo) {
    printf("\n+---------------------------------------------------------------+\n");
    printf("| %-61s |\n", titulo);
    printf("+------------+------+------------+---------------+-------------+\n");
    printf("| %-10s | %-4s | %-10s | %-13s | %-11s |\n",
           "Codigo", "Func", "Funcao", "Pressao(bar)", "Alertas");
    printf("+------------+------+------------+---------------+-------------+\n");

    for (int i = 0; i < n; i++) {
        printf("| %-10s | %4d | %-10s | %13.2f | %11d |\n",
               dutos[i].codigo,
               dutos[i].funcao,
               nome_funcao(dutos[i].funcao),
               dutos[i].pressao,
               dutos[i].alertas);
    }

    printf("+------------+------+------------+---------------+-------------+\n");
}

void mostra_calc(float med_alertas, float med_prod, float med_inj, float pct_prod_200, float pct_inj_220, float pct_inj_zero) {
    char res[32];

    printf("\n+-----------------------------------------------------------------------+\n");
    printf("|                         CALCULOS E ANALISES                          |\n");
    printf("+----+------------------------------------------------+-----------------+\n");
    printf("| %-2s | %-46s | %15s |\n", "It", "Descricao", "Resultado");
    printf("+----+------------------------------------------------+-----------------+\n");

    snprintf(res, sizeof(res), "%.2f", med_alertas);
    printf("| %-2s | %-46s | %15s |\n", "a", "Media geral de alertas", res);

    snprintf(res, sizeof(res), "%.2f bar", med_prod);
    printf("| %-2s | %-46s | %15s |\n", "b1", "Media de pressao - Producao", res);

    snprintf(res, sizeof(res), "%.2f bar", med_inj);
    printf("| %-2s | %-46s | %15s |\n", "b2", "Media de pressao - Injecao", res);

    snprintf(res, sizeof(res), "%.2f %%", pct_prod_200);
    printf("| %-2s | %-46s | %15s |\n", "c1", "Producao com pressao acima de 200.0 bar", res);

    snprintf(res, sizeof(res), "%.2f %%", pct_inj_220);
    printf("| %-2s | %-46s | %15s |\n", "c2", "Injecao com pressao abaixo de 220.0 bar", res);

    snprintf(res, sizeof(res), "%.2f %%", pct_inj_zero);
    printf("| %-2s | %-46s | %15s |\n", "d", "Injecao com zero alertas", res);

    printf("+----+------------------------------------------------+-----------------+\n");
}

int main()
{
    srand(time(NULL));

    struct Duto dutos[NUM_LINHAS];

    for (int i = 0; i < NUM_LINHAS; i++) {
        if (i % 2 == 0) {
            sprintf(dutos[i].codigo, "P-%d", 77001 + i);
            dutos[i].funcao = 1;
            dutos[i].pressao = gera_pressao(MIN_PRESSAO_PRODUCAO, MAX_PRESSAO_PRODUCAO);
        } else {
            sprintf(dutos[i].codigo, "I-%d", 77001 + i);
            dutos[i].funcao = 2;
            dutos[i].pressao = gera_pressao(MIN_PRESSAO_INJECAO, MAX_PRESSAO_INJECAO);
        }

        dutos[i].alertas = rand() % (MAX_ALERTAS + 1);
    }

    float soma_alertas = 0;
    float soma_prod = 0;
    float soma_inj = 0;
    int qtd_prod = 0;
    int qtd_inj = 0;
    int prod_200 = 0;
    int inj_220 = 0;
    int inj_zero = 0;

    for (int i = 0; i < NUM_LINHAS; i++) {
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

    float med_alertas = soma_alertas / NUM_LINHAS;
    float med_prod = soma_prod / qtd_prod;
    float med_inj = soma_inj / qtd_inj;
    float pct_prod_200 = ((float)prod_200 / qtd_prod) * 100.0;
    float pct_inj_220 = ((float)inj_220 / qtd_inj) * 100.0;
    float pct_inj_zero = ((float)inj_zero / qtd_inj) * 100.0;

    struct Duto ord[NUM_LINHAS];
    memcpy(ord, dutos, sizeof(dutos));
    qsort(ord, NUM_LINHAS, sizeof(struct Duto), ord_alertas);

    mostra_tabela(dutos, NUM_LINHAS, "TELEMETRIA DOS DUTOS - ORDEM DE GERACAO");
    mostra_calc(med_alertas, med_prod, med_inj, pct_prod_200, pct_inj_220, pct_inj_zero);
    mostra_tabela(ord, NUM_LINHAS, "RELATORIO ORDENADO POR ALERTAS - DECRESCENTE");

    return 0;
}
