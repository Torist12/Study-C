//By William Daudt Penna
//Inclui Bibliotecas para uso no codigo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");//Colocando para aceitar caracter Português Br (UTF-8)
	
	//declaração de variaveis
	int cont=0; 
	int totuo1 = 0, totuo2 = 0, totts1 = 0, totts2 = 0, totts3 =0;//totuo = total de unidade operacional
	int soma1 = 0, soma2 = 0, soma3 = 0;//soma dos valores dos serviços
	int altcomp = 0;//Alta complexidade
	int cod, nh, destino;//cod = Codigo da nota fiscal, nh = horas gastas, destino = destino do serviço
	int uo, ts;//uo = Unidade Operacional, ts = tipo de serviço
	float valor;//valor = valor do serviço
	
	char *opcoes[] = {"Estadual", "Interestadual"}; //Sistema de ponteiro traduz 0 e 1 para estadual ou interestadual
	
	srand(time(NULL));//Inicializa rand (randomizador)
	
	printf("\t ---------------------------------------------------------------\n");
	printf("\t| NF     | Via             | UO | Tipo | Horas |      Valor (R$)|\n");
	printf("\t ---------------------------------------------------------------\n");
	
	while(cont<120)//contador de Notas fiscais
	{
		cont ++;
		
		cod = 122000 + cont;//Codigo da Nota Fiscal
		destino = rand()%2;//Destino do serviço| Estadual ou Interestadual |
		uo = (rand() % 2) + 1;//Unidade Operacional| 1 – Cabiúnas ou 2 – PQ Tubos |
		ts = (rand() % 3) + 1;//Tipo de Serviço| 1 – Manutenção, 2 – Reparo ou 3 - Montagem |
		nh = (rand () % 40) + 1;//Horas Gastas | 1 a 40 hrs |
		
		valor = 1200 + (200*ts*nh);//Formula do valor
		
		//contabiliza a quantidade feita de cada Unidade operacional
		if (uo == 1)
		{
			totuo1++;
		}
		if (uo == 2)
		{
			totuo2++;
		}
		
		//contabiliza tant valor como quantidade feita de cada serviço
		if (ts == 1)
		{
			totts1 ++;
			soma1 += valor;
		}
		
		if (ts == 2)
		{
			totts2 ++;
			soma2 += valor;
		}
		
		else
		{
			totts3 ++;
			soma3 += valor;
		}
		
		//Serviços que passam de 10hrs são considerados de alta complexidade e é contabilizado
		if (ts == 3 && nh < 10)
		{
			altcomp++;
		}
		
		//formatação da tabela
		printf("\t| %-6d | %-15s | %-2d | %-4d | %-5d | %14.2f |\n",
	       cod, opcoes[destino], uo, ts, nh, valor);
	}
	//Percentual dos tipos de serviços e os de alta complexidade
	printf("\t ---------------------------------------------------------------\n");
	
	printf("\t| Percentual dos servicos por tipo %%                            |\n");
	printf("\t| Tipo 1: %.2f%%                                                |\n", (totts1/120.0)*100);
	printf("\t| Tipo 2: %.2f%%                                                |\n", (totts2/120.0)*100);
	printf("\t| Tipo 3: %.2f%%                                                |\n", (totts3/120.0)*100);
	printf("\t| Percentual Alta Complexidade (Maior que 10hrs): %.2f%%        |\n", (altcomp/120.0)*100);
	printf("\t ---------------------------------------------------------------\n");

	//Media do valor por tipo de serviço realizado
	printf("\t| Media de valor por tipo:                                      |\n");
	if (totts1 > 0)
		printf("\t| Tipo 1: R$ %.2f                                               |\n", soma1/totts1);
	if (totts2 > 0)
		printf("\t| Tipo 2: R$ %.2f                                               |\n", soma2/totts2);
	if (totts3 > 0)
		printf("\t| Tipo 3: R$ %.2f                                               |\n", soma3/totts3);
		printf("\t ---------------------------------------------------------------\n");
	
	
	
	
	
	return 0;
}
