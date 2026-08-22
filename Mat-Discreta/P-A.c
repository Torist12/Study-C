/* Operacoes com progressoes aritmeticas. */
#include <stdio.h>

float termo_geral(float primeiro_termo, float razao, int posicao) {
    return primeiro_termo + (posicao - 1) * razao;
}

float soma_pa(float primeiro_termo, float razao, int quantidade) {
    return quantidade / 2.0f *
           (2.0f * primeiro_termo + (quantidade - 1) * razao);
}

void interpolar_pa(float primeiro_termo, float ultimo_termo, int quantidade) {
    float razao = (ultimo_termo - primeiro_termo) / (quantidade + 1);

    printf("Numeros interpolados: ");
    for (int i = 1; i <= quantidade; i++) {
        printf("%.2f%s", primeiro_termo + i * razao,
               i == quantidade ? "\n" : ", ");
    }
}

void pa_segunda_ordem(void) {
    float termos[8];
    float diferencas[7];
    float segundas_diferencas[6];

    printf("Digite os 8 termos da sequencia:\n");
    for (int i = 0; i < 8; i++) {
        printf("Termo %d: ", i + 1);
        if (scanf("%f", &termos[i]) != 1) {
            printf("Entrada invalida.\n");
            return;
        }
    }

    for (int i = 0; i < 7; i++)
        diferencas[i] = termos[i + 1] - termos[i];
    for (int i = 0; i < 6; i++)
        segundas_diferencas[i] = diferencas[i + 1] - diferencas[i];

    printf("Primeiras diferencas: ");
    for (int i = 0; i < 7; i++)
        printf("%.2f%s", diferencas[i], i == 6 ? "\n" : ", ");

    printf("Segundas diferencas: ");
    for (int i = 0; i < 6; i++)
        printf("%.2f%s", segundas_diferencas[i], i == 5 ? "\n" : ", ");
}

int main(void) {
    int opcao;
    int n;
    int k;
    float a1;
    float razao;
    float an;

    do {
        printf("\n--- PROGRESSAO ARITMETICA ---\n");
        printf("1 - Calcular o enesimo termo\n");
        printf("2 - Calcular a soma de n termos\n");
        printf("3 - Interpolar k numeros\n");
        printf("4 - Gerar PA de segunda ordem\n");
        printf("0 - Sair\nOpcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }

        switch (opcao) {
            case 1:
                printf("Digite o primeiro termo, a razao e a posicao: ");
                if (scanf("%f %f %d", &a1, &razao, &n) != 3 || n < 1) {
                    printf("Dados invalidos.\n");
                    break;
                }
                printf("O %d.o termo e %.2f\n", n, termo_geral(a1, razao, n));
                break;
            case 2:
                printf("Digite o primeiro termo, a razao e a quantidade de termos: ");
                if (scanf("%f %f %d", &a1, &razao, &n) != 3 || n < 1) {
                    printf("Dados invalidos.\n");
                    break;
                }
                printf("A soma dos %d termos e %.2f\n", n, soma_pa(a1, razao, n));
                break;
            case 3:
                printf("Digite o primeiro termo, o ultimo termo e quantos numeros deseja interpolar: ");
                if (scanf("%f %f %d", &a1, &an, &k) != 3 || k < 1) {
                    printf("Dados invalidos.\n");
                    break;
                }
                interpolar_pa(a1, an, k);
                break;
            case 4:
                pa_segunda_ordem();
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
