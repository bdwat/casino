#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void playRoulette(int *money) {
    srand(time(NULL));
    int bet, decision, guess, draw;
    char exit, c;

    while(1) {
        printf("Type 'X' to exit Roulette or 'B' to bet: \n");
        scanf(" %c", &exit);
        clrscr();
        while ((c = getchar()) != '\n' && c != EOF); // Clear buffer

        if(exit == 'B' || exit == 'b') {
            clrscr();
            printf("Make your bet (min. $50)\n");
            printf("Current balance: $%d\n", *money);
            bet = numericDecision();

            if(bet < 50) {
                printf("The minimum bet is $50, try again.\n\n");
                continue;
            } else if(bet > *money) {
                printf("Insufficient balance.\n\n");
                continue;
            } else {
                *money -= bet;
                while (1) {
                    printf("Make your bet:\n");
                    printf("1. Even  2. Odd  3. 0 or 00  4. Choose number 5. Cancel\n");
                    decision = numericDecision();

                    draw = rand() % 38;

                    if(decision == 1) {
                        if (draw != 0 && draw % 2 == 0) {
                            clrscr();
                            printf("You won! The drawn number was: %d\n", draw);
                            *money += 2 * bet;
                            break;
                        } else {
                            clrscr();
                            printf("You lost! The drawn number was: %d\n", draw);
                            break;
                        }
                    } else if (decision == 2) {
                        if(draw % 2 != 0 && draw != 37) {
                            clrscr();
                            printf("You won! The drawn number was: %d\n", draw);
                            *money += 2 * bet;
                            break;
                        } else {
                            clrscr();
                            printf("You lost! The drawn number was: %d\n", draw);
                            break;
                        }
                    } else if(decision == 3) {
                        if(draw == 0 || draw == 37) {
                            clrscr();
                            printf("You won! The drawn number was: 0\n");
                            *money += 5 * bet;
                            break;
                        } else {
                            clrscr();
                            printf("You lost! The drawn number was: %d\n", draw);
                            break;
                        }
                    } else if(decision == 4) {
                        clrscr();
                        printf("Choose the number (1 to 36): \n");
                        scanf("%d", &guess);
                        if(guess == draw) {
                            clrscr();
                            printf("You won! The drawn number was: %d\n", draw);
                            *money += 10 * bet;
                            break;
                        } else {
                            clrscr();
                            printf("You lost! The drawn number was: %d\n", draw);
                            break;
                        }
                    } else if(decision == 5) {
                        clrscr();
                        printf("Exiting...\n");
                        break;
                    } else {
                        printf("Invalid command!\n");
                    }
                }
            }
            if (*money <= 0) {
                printf("No money left! Game Over\n");
                break;
            }
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