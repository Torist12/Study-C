//
// Created by William on 19/03/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main(void)
{
    setlocale(LC_ALL, "pt-BR.UTF-8");

    int ano = 2026, ano_nas = 0, idade = 0;
    float alt, peso, imc;
    char name[40], class[20];

    printf("==== Calculador de Idade e IMC ====\n");
    printf("Qual seu nome? ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // remove o \n

    printf("Qual seu ano de nascimento? ");
    scanf("%d", &ano_nas);

    printf("Qual sua altura em metros? ");
    scanf("%f", &alt);

    printf("Qual seu peso em kg? ");
    scanf("%f", &peso);

    // Limpa o buffer do teclado após os scanf's
    while (getchar() != '\n');

    imc = peso / (alt * alt);

    // Classificação do IMC
    if (imc < 18.5)
        strcpy(class, "abaixo do peso");
    else if (imc <= 24.9)
        strcpy(class, "peso normal");
    else if (imc <= 29.9)
        strcpy(class, "excesso de peso");
    else
        strcpy(class, "obesidade");

    // Verificação do ano de nascimento
    if (ano_nas > ano)
    {
        printf("\nVocê nem nasceu ainda!\n");
    }
    else if (ano_nas == ano)
    {
        printf("\nVocê nasceu este ano!\n");
    }
    else
    {
        idade = ano - ano_nas;
        printf("\n%s, sua idade em %d é %d.\n", name, ano, idade);
        printf("Seu IMC é %.2f e sua classificação é: %s.\n", imc, class);
    }

    printf("\nPressione Enter para sair...");
    getchar(); // Aguarda o usuário pressionar Enter

    return 0;
}