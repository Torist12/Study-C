// Sistema de lan house aleatorizado 3 computadores de preços diferentes com limite de maquinas por tier
// Tier 1 (pc 1) == R$ 12,50/hr (máx 5), Tier 2 (pc 2) == R$ 15,90/hr (máx 5), Tier 3 (pc 3) == R$ 19,90/hr (máx 5)
//sistema de karma funcionando de 0 a 10, é a avaliação do cliente no sistema interno 0 a 2 == ruim, 3 a 7 == regular/padrão, 8 a 10 == bom/otimo
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_TIER1 5
#define MAX_TIER2 5
#define MAX_TIER3 5
#define MAX_TOTAL 15
#define MAX_FUNCIONARIOS 3
#define MAX_CLIENTES 10

typedef struct {
    int id;
} Funcionario;

typedef struct {
    int id;
    long long cpf;
    int id_funcionario;
    int id_maquina;
    int karma;
} Cliente;

typedef struct {
    int id;
    int tier;
    int horas;
    int minutos;
    float tempo;
    float valor;
    float preco_hora;
} Maquina;

//gerar um CPF aleatorio de 11 digitos
long long gerar_cpf_aleatorio()
{
    return 10000000000LL + rand() % 90000000000LL;
}

void gerar_tempo_aleatorio(int *horas, int *minutos) 
{
    // Total de minutos: 60 a 720
    int total_minutos = 60 + rand() % (720 - 60 + 1);
    
    *horas = total_minutos / 60;
    *minutos = total_minutos % 60;
}

//preço por tier
float obter_preco_tier(int tier)
{
    switch(tier) {
        case 1: return 12.50;
        case 2: return 15.90;
        case 3: return 19.90;
        default: return 0.0;
    }
}

//função principal
int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Inicializar funcionários
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    printf("=== GERANDO FUNCIONÁRIOS ===\n");
    for(int i = 0; i < MAX_FUNCIONARIOS; i++) {
        funcionarios[i].id = i + 1;
        printf("Funcionário %d\n", funcionarios[i].id);
    }
    
    // Inicializar máquinas
    Maquina maquinas[MAX_TOTAL];
    Cliente clientes[MAX_CLIENTES];
    float total = 0;
    
    int contador_tier1 = 0, contador_tier2 = 0, contador_tier3 = 0;
    int i = 0;
    int total_clientes = 0;
    
    printf("\n=== SISTEMA DE LAN HOUSE ===\n");
    printf("Gerando %d máquinas com limite por tier:\n", MAX_TOTAL);
    printf("Tier 1: máx %d máquinas (R$ 12.50/hr)\n", MAX_TIER1);
    printf("Tier 2: máx %d máquinas (R$ 15.90/hr)\n", MAX_TIER2);
    printf("Tier 3: máx %d máquinas (R$ 19.90/hr)\n\n", MAX_TIER3);
    
    while(i < MAX_TOTAL)
    {
        int tier_aleatorio = rand() % 3 + 1;
        
        // Validar limite de máquinas por tier
        if(tier_aleatorio == 1 && contador_tier1 >= MAX_TIER1) continue;
        if(tier_aleatorio == 2 && contador_tier2 >= MAX_TIER2) continue;
        if(tier_aleatorio == 3 && contador_tier3 >= MAX_TIER3) continue;
        
        // Preencher dados da máquina
        maquinas[i].id = i + 1;
        maquinas[i].tier = tier_aleatorio;
        maquinas[i].preco_hora = obter_preco_tier(tier_aleatorio);
        
        gerar_tempo_aleatorio(&maquinas[i].horas, &maquinas[i].minutos);
        maquinas[i].tempo = maquinas[i].horas + maquinas[i].minutos / 60.0;
        maquinas[i].valor = maquinas[i].tempo * maquinas[i].preco_hora;
        
        // Incrementar contador do tier
        if(tier_aleatorio == 1) contador_tier1++;
        else if(tier_aleatorio == 2) contador_tier2++;
        else contador_tier3++;
        
        total += maquinas[i].valor;
        
        printf("Máquina %2d | Tier %d | Tempo: %dh %02dmin (%.2f h) | Valor: R$ %.2f\n", 
               maquinas[i].id, maquinas[i].tier, maquinas[i].horas, maquinas[i].minutos, 
               maquinas[i].tempo, maquinas[i].valor);
        
        i++;
    }
    
    // Gerar clientes para cada máquina
    printf("\n=== GERANDO CLIENTES ===\n");
    for(int j = 0; j < MAX_TOTAL && total_clientes < MAX_CLIENTES; j++) {
        clientes[total_clientes].id = total_clientes + 1;
        clientes[total_clientes].cpf = gerar_cpf_aleatorio();
        clientes[total_clientes].id_funcionario = (rand() % MAX_FUNCIONARIOS) + 1;
        clientes[total_clientes].id_maquina = maquinas[j].id;
        clientes[total_clientes].karma = rand() % 11; 

        char *status_karma;
        if (clientes[total_clientes].karma <= 2) status_karma = "Ruim";
        else if (clientes[total_clientes].karma <= 7) status_karma = "Regular";
        else status_karma = "Bom/Ótimo";

        printf("Cliente %2d | CPF: %lld | Func: %d | Máq: %d | Karma: %2d [%s]\n",
               clientes[total_clientes].id, 
               clientes[total_clientes].cpf,
               clientes[total_clientes].id_funcionario,
               clientes[total_clientes].id_maquina,
               clientes[total_clientes].karma,
               status_karma);
        
        total_clientes++;
    }
    
    printf("\n=== RESUMO ===\n");
    printf("Máquinas Tier 1: %d\n", contador_tier1);
    printf("Máquinas Tier 2: %d\n", contador_tier2);
    printf("Máquinas Tier 3: %d\n", contador_tier3);
    printf("Total de máquinas: %d\n", i);
    printf("Total de clientes: %d\n", total_clientes);
    printf("Total arrecadado: R$ %.2f\n", total);
    
    return 0;
}