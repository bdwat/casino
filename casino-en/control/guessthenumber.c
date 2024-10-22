#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void playGuessTheNumber(int *money) {
    srand(time(NULL));
    int tries = 0, secretNumber, guess, bet;
    char exit, c;

    while(1) {
        printf("Type 'X' to exit Guess The Number or 'B' to bet: \n");
        scanf(" %c", &exit);
        while ((c = getchar()) != '\n' && c != EOF); // Clear buffer

        if(exit == 'B' || exit == 'b') {
            printf("Make your bet (min. $10)\n");
            printf("Current balance: $%d\n", *money);
            bet = numericDecision();

            if(bet < 10) {
                printf("The minimum bet is $10, try again.\n\n");
                continue;
            } else if(bet > *money) {
                printf("Insufficient balance.\n\n");
                continue;
            } else {
                *money -= bet;
                secretNumber = rand() % 10 + 1;
                while (1) {
                    printf("\nType a number from 1 to 10\n");
                    guess = numericDecision();
                    if(guess > 10 || guess < 0){
                        continue;
                    }else{
                        if (tries < 2) {
                            if (guess > secretNumber) {
                                clrscr();
                                printf("The secret number is less than %d\n", guess);
                                tries++;
                                printf("%d tries left\n\n", 3 - tries);
                            } else if (guess < secretNumber) {
                                clrscr();
                                printf("The secret number is greater than %d\n", guess);
                                tries++;
                                printf("%d tries left\n\n", 3 - tries);
                            } else {
                                clrscr();
                                printf("You got it!\n");
                                *money += 1.5 * bet;
                                break;
                            }
                        } else if (tries == 2) {
                            if (guess == secretNumber) {
                                clrscr();
                                printf("You got it\n");
                                *money += 1.5 * bet;
                            } else {
                                clrscr();
                                printf("You lost, the secret number was: %d\n", secretNumber);
                            }
                            break;
                        }
                    }
                }
            }
        } else if(exit == 'X' || exit == 'x') {
            clrscr();
            break;
        } else {
            printf("Invalid command\n");
            continue;
        }
    }
}
