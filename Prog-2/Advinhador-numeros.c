#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void)
{

    int cont, numero, chute, tentativas = 0,acerto = 0;

    srand(time(NULL));
    numero = (rand() % 30) + 1;

    printf("Bem-vindo ao jogo de adivinhação!\n");
    printf("Tente adivinhar o número entre 1 e 30.\n");

    for (cont=1; cont <=3; cont++ && numero != chute) 
    {
        printf("Digite seu chute:\n");
        scanf("%d", &chute);
        tentativas++;

        if (chute < numero) 
        {
            printf("errou o numero é maior que %d \n", chute);
        } 
        
        else if (chute > numero) 
        {
            printf("errou o numero é menor que %d \n", chute);
        } 
        
        else 
        {
            printf("Parabéns! Você acertou o número %d em %d tentativas.\n", numero, tentativas);
            acerto =1;
        }
    } 

    if (!acerto) {
        printf("O número era %d. Deseja boa sorte na próxima vez!\n", numero);
        main();
    }
    else {
        printf("Você acertou o número %d em %d tentativas. Parabéns!\n", numero, tentativas);
    }

    return 0;
}