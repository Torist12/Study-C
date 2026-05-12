#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    
    int usr;
    int jogar =1;
    
    while (jogar == 1) {
    
    srand(time(NULL));

    int moeda = rand() % 2;

    printf("Digite 0 para cara e 1 para coroa:\n");
    scanf("%d", &usr);

    if (moeda ==0) {
        printf("cara\n");
    }
    else{
        printf("coroa\n");
    }
    if (usr == moeda) {
        printf("Você acertou!\n");
    }
    else {
        printf("Você errou!\n");
    }

    printf("deseja jogar novamente? 1 = sim, 0 = não;\n");
    scanf("%d", &jogar);
    }
     return 0;
    }
