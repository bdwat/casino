#include "control/blackjack.c"
#include "control/crash.c"
#include "control/guessthenumber.c"
#include "control/horsesrace.c"
#include "control/numericdecision.c"
#include "control/roulette.c"

int main() {
    int decision;
    int money = 500;
    while(money >= 50) {
        printf("Current balance: $%d\n\n", money);
        printf("Choose what to play:\n");
        printf("1.Horse race  2.BlackJack  3.Roulette  4.Guess the number  5.Crash  6. Exit\n");

        decision = numericDecision();

        if(decision == 1){
            playHorseRace(&money);
        }else if(decision == 2){
            playBlackJack(&money);
        }else if(decision == 3){
            playRoulette(&money);
        }else if(decision == 4){
            playGuessTheNumber(&money);
        }else if(decision == 5){
            playCrash(&money);
        }else if(decision == 6){
            printf("Exiting casino...\n");
            printf("Final balance: $%d\n", money);
            break;
        }else{
            printf("Invalid choice, try again..\n");
        }
    }
    return 0;
}
