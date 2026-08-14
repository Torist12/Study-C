#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL 145

typedef struct {
    char   codigo[12];
    int    tipo;
    float  vida_util;
    int    quantidade;
} Equipamento;

const char *prefixo(int tipo) {
    switch (tipo) {
        case 1: return "ES";
        case 2: return "FE";
        default: return "EE";
    }
}

const char *nome_tipo(int tipo) {
    switch (tipo) {
        case 1: return "Equipamento de Segurança";
        case 2: return "Ferramenta Elétrica    ";
        default: return "Equipamento de Elevação";
    }
}

void gerar_equipamentos(Equipamento v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i].tipo       = (rand() % 3) + 1;
        v[i].vida_util  = 12.0f + (rand() % 2291) / 10.0f;
        v[i].quantidade = rand() % 51;
        snprintf(v[i].codigo, 12, "%s%d", prefixo(v[i].tipo), 5001 + i);
    }
}

int cmp_desc(const void *a, const void *b) {
    return ((Equipamento *)b)->quantidade
         - ((Equipamento *)a)->quantidade;
}

void imprimir_tabela(Equipamento v[], int n, const char *titulo) {
    printf("\n%s\n", titulo);
    printf("%-10s %-27s %12s %12s\n", "Código", "Tipo", "Vida(meses)", "Qtd");
    printf("%s\n", "--------------------------------------------------------------");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-27s %12.1f %12d\n",
               v[i].codigo, nome_tipo(v[i].tipo),
               v[i].vida_util, v[i].quantidade);
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    Equipamento equip[TOTAL];
    gerar_equipamentos(equip, TOTAL);

    imprimir_tabela(equip, TOTAL, "=== CADASTRO DE EQUIPAMENTOS (ordem de geração) ===");

    double soma_geral = 0;
    for (int i = 0; i < TOTAL; i++) soma_geral += equip[i].vida_util;
    double media_geral = soma_geral / TOTAL;

    double soma_tipo[4]  = {0, 0, 0, 0};
    int    count_tipo[4] = {0, 0, 0, 0};

    for (int i = 0; i < TOTAL; i++) {
        soma_tipo [equip[i].tipo] += equip[i].vida_util;
        count_tipo[equip[i].tipo]++;
    }

    int seg_menor36 = 0;
    for (int i = 0; i < TOTAL; i++)
        if (equip[i].tipo == 1 && equip[i].vida_util < 36.0f)
            seg_menor36++;

    Equipamento ordenado[TOTAL];
    memcpy(ordenado, equip, sizeof(equip));
    qsort(ordenado, TOTAL, sizeof(Equipamento), cmp_desc);

    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf(    "║           ANÁLISES ESTATÍSTICAS                          ║\n");
    printf(    "╚══════════════════════════════════════════════════════════╝\n");

    printf("\na) Média geral da vida útil: %.2f meses\n", media_geral);

    printf("\nb) Média da vida útil por tipo:\n");
    for (int t = 1; t <= 3; t++) {
        double media_t = count_tipo[t] > 0 ? soma_tipo[t] / count_tipo[t] : 0.0;
        printf("   Tipo %d - %-27s : %.2f meses  (%d equipamentos)\n",
               t, nome_tipo(t), media_t, count_tipo[t]);
    }

    printf("\nc) Percentual de cada tipo em relação ao total (%d):\n", TOTAL);
    for (int t = 1; t <= 3; t++) {
        double pct = (double)count_tipo[t] / TOTAL * 100.0;
        printf("   Tipo %d - %-27s : %6.2f%%  (%d equipamentos)\n",
               t, nome_tipo(t), pct, count_tipo[t]);
    }

    double pct_seg_menor = count_tipo[1] > 0
                           ? (double)seg_menor36 / count_tipo[1] * 100.0
                           : 0.0;
    printf("\nd) Equipamentos de Segurança com vida útil < 3 anos (36 meses):\n");
    printf("   %d de %d  ->  %.2f%% dos Equipamentos de Segurança\n",
           seg_menor36, count_tipo[1], pct_seg_menor);

    imprimir_tabela(ordenado, TOTAL,
        "\ne) EQUIPAMENTOS ORDENADOS POR QUANTIDADE DISPONÍVEL (decrescente)");

    printf("\n");
    return 0;
}