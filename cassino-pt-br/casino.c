#include "control/decisaonumerica.c"
#include "control/corridacavalos.c"
#include "control/blackjack.c"
#include "control/roleta.c"
#include "control/adivinha.c"
#include "control/crash.c"

int main() {
    int decisao;
    int dinheiro = 500;
    while(dinheiro >= 50) {
        printf("Saldo disponível: $%d\n\n", dinheiro);
        printf("Escolha o que jogar:\n");
        printf("1.Corrida de Cavalos  2.BlackJack  3.Roleta  4.Adivinha  5.Crash  6. Sair\n");

        decisao = decisaoNumerica();

        if(decisao == 1){
            jogarCorridaCavalos(&dinheiro);
        }else if(decisao == 2){
            jogarBlackJack(&dinheiro);
        }else if(decisao == 3){
            jogarRoulette(&dinheiro);
        }else if(decisao == 4){
            jogarAdivinha(&dinheiro);
        }else if(decisao == 5){
            jogarCrash(&dinheiro);
        }else if(decisao == 6){
            printf("Saindo do cassino...\n");
            printf("Saldo final: $%d\n", dinheiro);
            break;
        }else{
            printf("Escolha inválida, tente novamente.\n");
        }
    }
    return 0;
}
