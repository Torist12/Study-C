#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int type, origem, age;
	int i;
	int soma1 = 0;
	int soma2 = 0;
	int totcli = 0, totort = 0;
    int totpart = 0, totplan = 0;

    int somaidpa = 0, somaidpl = 0;

    int clima60 = 0;

    // Vetores para armazenar pacientes
    int vtype[100], vorigem[100], vidade[100];

    int opcao;

    srand(time(NULL));
    
    for(i=0; i<100; i++)
    {
    	type = rand() %2;
    	origem = rand() %2;
    	age = rand() %91;

        // salvando dados
        vtype[i] = type;
        vorigem[i] = origem;
        vidade[i] = age;
    	
    	if(type==0)
    	{
    		totcli++;
    		
    		if(age>60)
    		{
    			clima60 ++;
			}
		}
		else
		{
			totort++;
		}
		
		if(origem)
		{
			totpart++;
			soma1 += age;
		}
		else
		{
			totplan++;
			soma2 += age;
		}
	}
	
	float percli = (totcli / 100.0) * 100;
    float perort = (totort / 100.0) * 100;

    float medpart = (totpart > 0) ? (soma1 / (float)totpart) : 0;
    float medplan = (totplan > 0) ? (soma2 / (float)totplan) : 0;

    float perclir60 = (totcli > 0) ? (clima60 / (float)totcli) * 100 : 0;
    
	printf("===========< Sistema Hospitalar + >==============\n");
	printf("===================================================\n");
	printf("\tMedia Particular\t\t%.2f\n", medpart);
	printf("\tMedia Plano\t\t\t%.2f\n", medplan);
	printf("\tPercentual Clinica geral\t%.0f%%\n", percli);
	printf("\tPercentual Ortopedia\t\t%.0f%%\n", perort);
	printf("\tPercentual Maior que 60\t\t%.0f%%\n", perclir60);
	printf("===================================================\n");

    printf("\nDigite 1 para mostrar os pacientes ou qualquer outra tecla para fechar: ");
    scanf("%d", &opcao);

    if(opcao == 1)
    {
        for(i = 0; i < 100; i++)
        {
            printf("Paciente %d | Tipo: %d | Origem: %d | Idade: %d\n",
                   i+1, vtype[i], vorigem[i], vidade[i]);
        }
    }
    else
    {
    	return 0;
	}
}
