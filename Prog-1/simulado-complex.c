#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int Media, nf;
    int i = 0;
    int soma = 0;
    int Local[120];
    int Servtype[120];
    char serie[120][3];
    char Destino[120][20];
    int horasGastas[120];
    int codigos[120];
    float valorServico[120];
    
    // Variáveis para estatísticas
    int contagemTipos[3] = {0, 0, 0};
    int contagemAltaComplexidadeMenor10h = 0;
    int contagemAltaComplexidadeTotal = 0;
    float somaValoresTipos[3] = {0, 0, 0};
    int contagemValoresTipos[3] = {0, 0, 0};
    float percentuais[3];
    float percentualAltaComplexidade;
    float medias[3];

    srand(time(NULL));

    for(i = 0; i < 120; i++) 
    {
        codigos[i] = 122001 + i;

        strcpy(serie[i], "A1");

        Local[i] = (rand() % 2) + 1;  // local (1 - Cabiúnas, 2 - PQ Tubos)

        Servtype[i] = (rand() % 3) + 1;  // tipo de servico (1 - Manutenção, 2 - Reparo, 3 - Montagem)

        if(rand() % 2 == 0) {
            strcpy(Destino[i], "Estadual");
        } else {
            strcpy(Destino[i], "Interestadual");
        }

        horasGastas[i] = (rand() % 40) + 1;  // horas de 1 a 40

        float valorTipo;
        if(Servtype[i] == 1) {
            valorTipo = 200.00;  // Manutenção
        } else if(Servtype[i] == 2) {
            valorTipo = 400.00;  // Reparo
        } else {
            valorTipo = 600.00;  // Montagem
        }

        // Calcular valor do serviço
        valorServico[i] = 1200.00 + (valorTipo * horasGastas[i]);
    }
    
    // Exibir todas as notas fiscais
    printf("\n=== NOTAS FISCAIS ===\n");
    printf("========================================================================================\n");
    printf("Código\tSérie\tLocal\t\tTipo\t\tDestino\t\tHoras\tValor (R$)\n");
    printf("========================================================================================\n");
    
    for(i = 0; i < 120; i++) {
        char localStr[20];
        char tipoStr[20];
        
        // Converter local para string
        if(Local[i] == 1) {
            strcpy(localStr, "Cabiúnas");
        } else {
            strcpy(localStr, "PQ Tubos");
        }
        
        // Converter tipo de serviço para string
        if(Servtype[i] == 1) {
            strcpy(tipoStr, "Manutenção");
        } else if(Servtype[i] == 2) {
            strcpy(tipoStr, "Reparo");
        } else {
            strcpy(tipoStr, "Montagem");
        }
        
        printf("%d\t%s\t%-10s\t%-10s\t%-13s\t%d\t%.2f\n", 
               codigos[i],
               serie[i],
               localStr,
               tipoStr,
               Destino[i],
               horasGastas[i],
               valorServico[i]);
    }
    
    // 3 - Calcular percentual de serviços de cada tipo
    for(i = 0; i < 120; i++) {
        if(Servtype[i] == 1) {
            contagemTipos[0]++;  // Manutenção
        } else if(Servtype[i] == 2) {
            contagemTipos[1]++;  // Reparo
        } else {
            contagemTipos[2]++;  // Montagem
        }
    }
    
    for(i = 0; i < 3; i++) {
        percentuais[i] = (contagemTipos[i] * 100.0) / 120;
    }
    
    // 4 - Calcular percentual de serviços de Alta Complexidade com duração menor que 10 horas
    for(i = 0; i < 120; i++) {
        // Considerando serviços de Montagem (tipo 3) como Alta Complexidade
        if(Servtype[i] == 3) {
            contagemAltaComplexidadeTotal++;
            if(horasGastas[i] < 10) {
                contagemAltaComplexidadeMenor10h++;
            }
        }
    }
    
    if(contagemAltaComplexidadeTotal > 0) {
        percentualAltaComplexidade = (contagemAltaComplexidadeMenor10h * 100.0) / contagemAltaComplexidadeTotal;
    } else {
        percentualAltaComplexidade = 0;
    }
    
    // 5 - Calcular média de valor para os serviços de cada tipo
    for(i = 0; i < 120; i++) {
        if(Servtype[i] == 1) {
            somaValoresTipos[0] += valorServico[i];
            contagemValoresTipos[0]++;
        } else if(Servtype[i] == 2) {
            somaValoresTipos[1] += valorServico[i];
            contagemValoresTipos[1]++;
        } else {
            somaValoresTipos[2] += valorServico[i];
            contagemValoresTipos[2]++;
        }
    }
    
    for(i = 0; i < 3; i++) {
        if(contagemValoresTipos[i] > 0) {
            medias[i] = somaValoresTipos[i] / contagemValoresTipos[i];
        } else {
            medias[i] = 0;
        }
    }
    
    // Exibir estatísticas
    printf("\n\n=== ESTATÍSTICAS ===\n");
    printf("================================================================================\n");
    printf("3 - PERCENTUAL DE SERVIÇOS DE CADA TIPO:\n");
    printf("    Manutenção: %.2f%% (%d de 120 notas)\n", percentuais[0], contagemTipos[0]);
    printf("    Reparo: %.2f%% (%d de 120 notas)\n", percentuais[1], contagemTipos[1]);
    printf("    Montagem: %.2f%% (%d de 120 notas)\n", percentuais[2], contagemTipos[2]);
    
    printf("\n4 - PERCENTUAL DE SERVIÇOS DE ALTA COMPLEXIDADE COM DURAÇÃO MENOR QUE 10 HORAS:\n");
    printf("    %d de %d serviços de Montagem (Alta Complexidade) têm duração < 10 horas\n", 
           contagemAltaComplexidadeMenor10h, contagemAltaComplexidadeTotal);
    printf("    Percentual: %.2f%%\n", percentualAltaComplexidade);
    
    printf("\n5 - MÉDIA DE VALOR PARA OS SERVIÇOS DE CADA TIPO:\n");
    printf("    Manutenção: R$ %.2f\n", medias[0]);
    printf("    Reparo: R$ %.2f\n", medias[1]);
    printf("    Montagem: R$ %.2f\n", medias[2]);
    
    return 0;
}
