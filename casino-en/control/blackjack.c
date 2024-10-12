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

void playBlackJack(int *money) {
    srand(time(NULL));

    while(1){
        int cartas[12] = {1,2,3,4,5,6,7,8,9,10,10,10};
        int userCards = 0, houseCards = 0, decision, bet;
        char exit,c;
        double win,blackJack;

        houseCards = 0;
        userCards = 0;
        houseCards += cartas[rand() % 12];
        userCards += cartas[rand() % 12];
        printf("Type 'X' to exit BlackJack or 'B' to bet: \n");
        scanf(" %c",&exit);
        if(exit == 'b' || exit == 'B'){
            printf("Make your bet (min. $100)\n");
            printf("Current balance: $%d\n\n", *money);
            bet = numericDecision();
            blackJack = (2.5 * bet);
            win = (2 * bet);


            if(bet < 100){
                printf("The minimum bet is $100, try again.\n\n");
                continue;
            } else if(bet > *money){
                printf("Insufficient balance.\n\n");
                continue;
            }else {
                clrscr();
                *money -= bet;
                printf("Your sum = %d\n", userCards);
                printf("House's sum = %d\n", houseCards);
                while(1){
                    if(houseCards < 21 && userCards < 21){
                        printf("Choose:\n");
                        printf("1. Buy  2. Keep  3. Forfei\n");
                        decision = numericDecision();

                        if(decision == 1 && houseCards > 17){
                            userCards += cartas[rand() % 12];
                            if (userCards > 21){
                                clrscr();
                                printf("You lost!\n\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                break;
                            } else if (userCards == 21){
                                clrscr();
                                printf("Blackjack!\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                *money += blackJack;
                                break;
                            } else {
                                clrscr();
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                continue;
                            }
                        } else if(decision == 1 && houseCards <= 17){
                            userCards += cartas[rand() %12];
                            if(houseCards > 21){
                                clrscr();
                                printf("You won! The house busted\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                *money += win;
                                break;
                            } else if(userCards == 21){
                                clrscr();
                                printf("Blackjack!\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                *money += blackJack;
                                break;
                            } else if (houseCards == 21){
                                clrscr();
                                printf("House's BlackJack!\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                break;
                            } else if (userCards > 21){
                                clrscr();
                                printf("You lost!\n\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                break;
                            } else {
                                clrscr();
                                houseCards += cartas[rand() % 12];
                                if(houseCards > 21){
                                    printf("You won! The house busted!\n");
                                    printf("Your sum = %d\n", userCards);
                                    printf("House's sum = %d\n", houseCards);
                                    *money += win;
                                    break;
                                } else if (houseCards == 21){
                                    printf("House's BlackJack\n");
                                    printf("Your sum = %d\n", userCards);
                                    printf("House's sum = %d\n", houseCards);
                                    break;
                                } else {
                                    printf("Your sum = %d\n", userCards);
                                    printf("House's sum = %d\n", houseCards);
                                    continue;
                                }
                            }
                        } else if(decision == 2 && houseCards < userCards){
                            clrscr();
                            houseCards += cartas[rand() % 12];
                            if(houseCards > 21){
                                printf("You won! The house busted!\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                *money += win;
                                break;
                            } else if (houseCards == 21){
                                printf("House's BlackJack!\n");
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                break;
                            } else {
                                printf("Your sum = %d\n", userCards);
                                printf("House's sum = %d\n", houseCards);
                                continue;
                            }
                        } else if(decision == 2 && houseCards >= userCards){
                            clrscr();
                            printf("You lost!\n\n");
                            printf("Your sum = %d\n", userCards);
                            printf("House's sum = %d\n", houseCards);
                            break;
                        } else if(decision == 3) {
                            clrscr();
                            printf("You forfeited!\n");
                            printf("Your sum = %d\n", userCards);
                            printf("House's sum = %d\n", houseCards);
                            break;
                        }else{
                            printf("Invalid command\n");
                            continue;
                        }
                    }
                }
            }
        }else if(exit == 'X' || exit == 'x'){
            clrscr();
            break;
        }else{
            printf("Invalid command\n");
            continue;
        }
    }
}