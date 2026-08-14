#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//sistema de caça niquel aonde o usuario insere um valor inicial de creditos e vai apostando o valor necessario e ganha de acordo com a % do valor da combinação
//e o sistema pode para se o usuario pedir
int main (void){

    int v1, v2, v3, v4, aposta, creditos, continuar;

    srand(time(NULL));//inicializa o gerador de numeros aleatorios

    printf("=======+ Bem vindo ao tigrinho do PIX 2.0 +=======\n");
    printf("Digite a quantidade de creditos que deseja apostar: ");
    scanf("%d", &creditos);

    continuar = 1;

    while (continuar == 1 && creditos > 0)//verifica se o usuario quer continuar jogando e se ainda tem creditos
    {
        printf("========================================\n");
        printf("Digite o valor da aposta:\n");
        scanf("%d", &aposta);
        creditos -= aposta;

        //gera tres numeros aleatorios entre 1 e 9
        v1 = (rand() % 9) + 1;
        v2 = (rand() % 9) + 1;
        v3 = (rand() % 9) + 1;
        v4 = (rand() % 9) + 1;

        printf("Resultado: %d %d %d %d\n", v1, v2, v3, v4);

        //verifica se os numeros sao iguais e calcula o valor ganho de acordo com a % do valor da aposta
        if (v1 == v2 && v2 == v3 && v3 == v4) {
            printf("TIGRINHO SOLTOU CARTA\n");
            creditos += aposta * 10;
        } else if (v1 == v2 || v1 == v3 || v2 == v3 || v2 == v4 || v3 == v4 || v1 == v4) {
            printf("Tigrinho foi bondoso\n");
            creditos += aposta * 5;
        }else if (v1 == 6 && v2 == 7 && v3 == 6 && v4 == 7) {
            printf("SIX SEVEN\n");
            creditos += aposta * 6.7;
        }else if (v1 == 6 && v2 == 9 && v3 == 6 && v4 == 9) {
            printf("69 HEHEHEHEHHEHE\n");
            creditos += aposta * 6.9;
        }
        else {
            printf("Perdeu tudo agora vai morar de aluguel.\n");
        }
        printf("========================================\n");
        printf("Créditos restantes: %d\n", creditos);

        //pergunta se o usuario quer continuar jogando
        printf("Deseja continuar jogando? (1 para sim, 0 para nao): ");
        scanf("%d", &continuar);

    }

    return 0;
}