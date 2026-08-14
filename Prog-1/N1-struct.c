#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char codigo[15];
    char mes[10];
    char tipo[15];
    char local[15];
    int dias;
    float valor;
} NT;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    
    srand(time(NULL));
    
    NT nts[123];
    int i, na, tp, dias, lc;
    float per15int = 0;
    int tot15int = 0, tot15 = 0;
    float mdf, tdf = 0, tf = 0, mdt, tdt = 0, tt = 0, media_geral;
    
    float maior_valor = -1;
    char maior_codigo[15], maior_mes[10], maior_tipo[15], maior_local[15];
    int maior_dias;
    
    float soma_valor_set = 0, soma_valor_out = 0, soma_valor_nov = 0;
    int cont_set = 0, cont_out = 0, cont_nov = 0;
    
    na = (rand() % 251) + 1550;
    
    printf("=== VETOR DE NTs ===\n");
    printf("%-12s %-6s %-15s %-15s %-6s %-10s\n", 
           "Codigo", "Mes", "Tipo", "Local", "Dias", "Valor");
    printf("---------------------------------------------------------------\n");
    
    for(i=0; i<123; i++)
    {
        tp = rand() % 2;
        lc = rand() % 2;
        dias = (rand() % 30) + 1;
        
        if(i <= 39)
            strcpy(nts[i].mes, "Setembro");
        else if(i <= 80)
            strcpy(nts[i].mes, "Outubro");
        else
            strcpy(nts[i].mes, "Novembro");
        
        if(tp == 0)
        {
            sprintf(nts[i].codigo, "NT%dF", na + i);
            strcpy(nts[i].tipo, "Fretamento");
            nts[i].valor = dias * 300 + 500;
            nts[i].dias = dias;
            tf++;
            tdf += dias;
            
            if(i <= 39) { soma_valor_set += nts[i].valor; cont_set++; }
            else if(i <= 80) { soma_valor_out += nts[i].valor; cont_out++; }
            else { soma_valor_nov += nts[i].valor; cont_nov++; }
        }
        else
        {
            sprintf(nts[i].codigo, "NT%dT", na + i);
            strcpy(nts[i].tipo, "Transporte");
            nts[i].valor = dias * 450 + 750;
            nts[i].dias = dias;
            tt++;
            tdt += dias;
            
            if(i <= 39) { soma_valor_set += nts[i].valor; cont_set++; }
            else if(i <= 80) { soma_valor_out += nts[i].valor; cont_out++; }
            else { soma_valor_nov += nts[i].valor; cont_nov++; }
        }
        
        if(lc == 0)
            strcpy(nts[i].local, "Estadual");
        else
            strcpy(nts[i].local, "Interestadual");
        
        if(nts[i].dias < 15)
        {
            tot15++;
            if(lc == 1)
                tot15int++;
        }
        
        if(nts[i].valor > maior_valor)
        {
            maior_valor = nts[i].valor;
            strcpy(maior_codigo, nts[i].codigo);
            strcpy(maior_mes, nts[i].mes);
            strcpy(maior_tipo, nts[i].tipo);
            strcpy(maior_local, nts[i].local);
            maior_dias = nts[i].dias;
        }
        
        printf("%-12s %-6s %-15s %-15s %-6d R$ %8.2f\n", 
             nts[i].codigo, nts[i].mes, nts[i].tipo, nts[i].local, nts[i].dias, nts[i].valor);
    }
    
    printf("\n(Total de 123 NTs cadastradas)\n\n");
    
    per15int = (float)tot15int / tot15 * 100;
    printf("2 - Percentual de NT's com duracao menor que 15 dias que eram interestaduais:\n");
    printf("    %.2f%%\n\n", per15int);
    
    mdf = tdf / tf;
    mdt = tdt / tt;
    media_geral = (tdf + tdt) / (tf + tt);
    
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
    printf("    Setembro: R$ %.2f\n", soma_valor_set / cont_set);
    printf("    Outubro: R$ %.2f\n", soma_valor_out / cont_out);
    printf("    Novembro: R$ %.2f\n\n", soma_valor_nov / cont_nov);
    printf("---------------------------------------------------------------------\n");

    return 0;
}
