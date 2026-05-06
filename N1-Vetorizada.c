#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX 123//definindo o MAX para 123

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    int na = (rand() % 251) + 1550;

    char codigo[MAX][15];
    char mes[MAX][10];
    char tipo[MAX][15];
    char local[MAX][15];
    int dias[MAX];
    int lc[MAX];
    int tp[MAX];
    float valor[MAX];

    int tot15 = 0;
    int tot15int = 0;
    float soma_valor_set = 0, soma_valor_out = 0, soma_valor_nov = 0;
    int cont_set = 0, cont_out = 0, cont_nov = 0;
    float tdf = 0, tdt = 0, tf = 0, tt = 0;

    float maior_valor = -1;
    char maior_codigo[15], maior_mes[10], maior_tipo[15], maior_local[15];
    int maior_dias = 0;

    for (int i = 0; i < MAX; i++)
    {
        tp[i] = rand() % 2;
        lc[i] = rand() % 2;
        dias[i] = (rand() % 30) + 1;

        if (i < 39)
            strcpy(mes[i], "Setembro");
        else if (i < 80)
            strcpy(mes[i], "Outubro");
        else
            strcpy(mes[i], "Novembro");

        if (tp[i] == 0)
        {
            sprintf(codigo[i], "NT%dF", na + i + 1);
            strcpy(tipo[i], "Fretamento");
            valor[i] = dias[i] * 300 + 500;
        }
        else
        {
            sprintf(codigo[i], "NT%dT", na + i + 1);
            strcpy(tipo[i], "Transporte");
            valor[i] = dias[i] * 450 + 750;
        }

        if (lc[i] == 0)
            strcpy(local[i], "Estadual");
        else
            strcpy(local[i], "Interestadual");
    }

    for (int i = 0; i < MAX; i++)
    {
        if (dias[i] < 15)
        {
            tot15++;
            if (lc[i] == 1)
                tot15int++;
        }

        if (tp[i] == 0)
        {
            tf++;
            tdf += dias[i];
        }
        else
        {
            tt++;
            tdt += dias[i];
        }

        if (i < 39)
        {
            soma_valor_set += valor[i];
            cont_set++;
        }
        else if (i < 80)
        {
            soma_valor_out += valor[i];
            cont_out++;
        }
        else
        {
            soma_valor_nov += valor[i];
            cont_nov++;
        }

        if (valor[i] > maior_valor)
        {
            maior_valor = valor[i];
            strcpy(maior_codigo, codigo[i]);
            strcpy(maior_mes, mes[i]);
            strcpy(maior_tipo, tipo[i]);
            strcpy(maior_local, local[i]);
            maior_dias = dias[i];
        }
    }

    printf("=== VETOR DE NTs ===\n");
    printf("%-12s %-10s %-15s %-15s %-6s %-10s\n", "Codigo", "Mes", "Tipo", "Local", "Dias", "Valor");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < MAX; i++)
    {
        printf("%-12s %-10s %-15s %-15s %-6d R$ %8.2f\n",
               codigo[i], mes[i], tipo[i], local[i], dias[i], valor[i]);
    }

    printf("\n(Total de %d NTs cadastradas)\n\n", MAX);

    float per15int = tot15 > 0 ? ((float)tot15int / tot15) * 100.0f : 0.0f;
    float mdf = tf > 0 ? tdf / tf : 0.0f;
    float mdt = tt > 0 ? tdt / tt : 0.0f;
    float media_geral = (tf + tt) > 0 ? (tdf + tdt) / (tf + tt) : 0.0f;

    printf("2 - Percentual de NT's com duracao menor que 15 dias que eram interestaduais:\n");
    printf("    %.2f%%\n\n", per15int);

    printf("3 - Media de Dias das NT's de cada tipo e geral:\n");
    printf("    Fretamento: %.2f dias\n", mdf);
    printf("    Transporte: %.2f dias\n", mdt);
    printf("    Geral: %.2f dias\n\n", media_geral);

    printf("4 - NT de maior valor com todas as informacoes:\n");
    printf("    Codigo: %s\n", maior_codigo);
    printf("    Mes: %s\n", maior_mes);
    printf("    Tipo: %s\n", maior_tipo);
    printf("    Local: %s\n", maior_local);
    printf("    Dias: %d\n", maior_dias);
    printf("    Valor: R$ %.2f\n\n", maior_valor);

    printf("5 - Valor medio das NT's por mes:\n");
    printf("    Setembro: R$ %.2f\n", cont_set > 0 ? soma_valor_set / cont_set : 0.0f);
    printf("    Outubro: R$ %.2f\n", cont_out > 0 ? soma_valor_out / cont_out : 0.0f);
    printf("    Novembro: R$ %.2f\n", cont_nov > 0 ? soma_valor_nov / cont_nov : 0.0f);
    printf("---------------------------------------------------------------------\n");
    return 0;
}
