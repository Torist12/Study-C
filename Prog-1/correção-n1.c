#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    
    srand(time(NULL));
    
    int cont = 0, na;
    char codigo[15];
    int tp, dias;
    char tipo[15];
    int lc;
    char local[15], mes[10];
    float valor, per15int = 0;
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
    
    while(cont < 123)
    {
        cont++;
        
        tp = rand() % 2;
        lc = rand() % 2;
        dias = (rand() % 30) + 1;
        
        if(cont <= 39)
            sprintf(mes, "Setembro");
        else if(cont <= 80)
            sprintf(mes, "Outubro");
        else
            sprintf(mes, "Novembro");
        
        if(tp == 0)
        {
            sprintf(codigo, "NT%dF", na + cont);
            sprintf(tipo, "Fretamento");
            valor = dias * 300 + 500;
            tf++;
            tdf += dias;
            
            if(cont <= 39) { soma_valor_set += valor; cont_set++; }
            else if(cont <= 80) { soma_valor_out += valor; cont_out++; }
            else { soma_valor_nov += valor; cont_nov++; }
        }
        else
        {
            sprintf(codigo, "NT%dT", na + cont);
            sprintf(tipo, "Transporte");
            valor = dias * 450 + 750;
            tt++;
            tdt += dias;
            
            if(cont <= 39) { soma_valor_set += valor; cont_set++; }
            else if(cont <= 80) { soma_valor_out += valor; cont_out++; }
            else { soma_valor_nov += valor; cont_nov++; }
        }
        
        if(lc == 0)
            sprintf(local, "Estadual");
        else
            sprintf(local, "Interestadual");
        
        if(dias < 15)
        {
            tot15++;
            if(lc == 1)
                tot15int++;
        }
        
        if(valor > maior_valor)
        {
            maior_valor = valor;
            sprintf(maior_codigo, "%s", codigo);
            sprintf(maior_mes, "%s", mes);
            sprintf(maior_tipo, "%s", tipo);
            sprintf(maior_local, "%s", local);
            maior_dias = dias;
        }
        
        printf("%-12s %-6s %-15s %-15s %-6d R$ %8.2f\n", 
             codigo, mes, tipo, local, dias, valor);
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
    
    printf("6 - Total de dias de servico:\n");
    printf("    Total geral de dias: %.0f dias\n", tdf + tdt);
    printf("    Media de dias por NT: %.2f dias\n\n", (tdf + tdt) / 123);

    printf("7 - Percentual de dias de Fretamento e Transporte:\n");
    printf("    Fretamento: %.2f%% dos dias\n", tdf / (tdf + tdt) * 100);
    printf("    Transporte: %.2f%% dos dias\n\n", tdt / (tdf + tdt) * 100);

    return 0;
}
