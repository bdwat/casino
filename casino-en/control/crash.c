#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void playCrash(int *money) {
    int bet, tries = 0;
    char decision, exit, c;

    srand(time(NULL));

    printf("Welcome to the Crash game!\n\n");

    while (1) {
        printf("Type 'X' to exit Crash or 'B' to bet: \n");
        scanf(" %c", &exit);
        while ((c = getchar()) != '\n' && c != EOF); // Clear buffer
        clrscr();

        if (exit == 'B' || exit == 'b') {
            printf("Current balance: $%d\n", *money);
            printf("Make your bet(min. 25$)\n");
            bet = numericDecision();

            if(bet < 25){
                printf("The minimum bet is $25, try again\n");
                continue;
            }else if(bet > *money){
                printf("Insufficient balance\n");
                continue;
            }else{
                float multiplier = 1;
                while (1) {
                    printf("Current multiplier: %.2f\n", multiplier);
                    printf("Type 'C' to cash out or 'R' to continue ");
                    scanf(" %c", &decision);
                    clrscr();    
                    if (decision == 'c' && tries > 0 ||decision == 'C' && tries > 0 ) {
                        *money += bet * multiplier;
                        break;
                    } else if (decision == 'r' || decision == 'R') {
                        int chance = rand() % 8;
                        if (chance == 1) {
                            printf("Você crashou! Perdeu a bet.\n");
                            *money -= bet;
                            break;
                        }
                        multiplier += 0.15;
                        tries++;
                    } else {
                        printf("Invalid Choice! Try again.\n");
                    }
                }
            }
            if (*money <= 0) {
                printf("No money left! Game Over\n");
                break;
            }

            continue;
        } else if (exit == 'X' || exit == 'x') {
            clrscr();
            break;
        } else {
            clrscr();
            printf("Invalid command\n");
            continue;
        }
    }
}