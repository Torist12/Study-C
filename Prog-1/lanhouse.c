// Sistema de lan house aleatorizado 3 computadores de preços diferentes com 15 maquinas ao total e seu valor em hr 
// pc 1 == 12,50 pc 2 == 15,90 pc 3 == 19,90; todos os valores se referem a hr da workstation, o programa multiplica pelo tempo aleatorio.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void gerar_tempo_aleatorio(int *horas, int *minutos) 
{
    // Total de minutos: 60 a 720
    int total_minutos = 60 + rand() % (720 - 60 + 1);
    
    *horas = total_minutos / 60;
    *minutos = total_minutos % 60;
}

int main()
{
    srand(time(NULL));

    int i;
    int pc[15];
    int horas[15], minutos[15];
    float tempo[15];
    float valor[15];
    float total = 0;
    float price1 = 12.50, price2 = 15.90, price3 = 19.90;
    
    for(i=0; i<15; i++)
    {
        pc[i] = rand() % 3 + 1; //inicializando o randomizador do PC

        gerar_tempo_aleatorio(&horas[i], &minutos[i]);//gerando o tempo aleatorio para cada PC

        tempo[i] = horas[i] + minutos[i] / 60.0;//convertendo o tempo para horas decimais
        
        // Calcular valor baseado no tipo de PC
        if(pc[i] == 1) {
            valor[i] = tempo[i] * price1;
        } else if(pc[i] == 2) {
            valor[i] = tempo[i] * price2;
        } else {
            valor[i] = tempo[i] * price3;
        }
        
        total += valor[i];//acumulando o total arrecadado
        
        printf("\nPC %d: Tipo %d, Tempo: %d horas e %d minutos (%.2f horas), Valor: R$ %.2f\n", i+1, pc[i], horas[i], minutos[i], tempo[i], valor[i]);
    }
    
    printf("\nTotal arrecadado: R$ %.2f\n", total);
    
    return 0;
}