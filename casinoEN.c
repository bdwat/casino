#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

char* horse() {
    char* winnerHorse = malloc(20 * sizeof(char));
    srand(time(NULL));
    char horse[] = {'R', 'B', 'V', 'S', 'L'};
    int horseSelector = rand() % 5;

    switch (horse[horseSelector]) {
        case 'R':
            strcpy(winnerHorse, "Lightning");
            break;
        case 'B':
            strcpy(winnerHorse, "Bolt");
            break;
        case 'V':
            strcpy(winnerHorse, "Verstappen");
            break;
        case 'S':
            strcpy(winnerHorse, "Senna");
            break;
        case 'L':
            strcpy(winnerHorse, "Lewis");
            break;
        default:
            break;
    }
    
    return winnerHorse;
}

//Function to free the dinamicaly alocated memory for winnerHorse
void free_winnerHorse(char* winnerHorse) {
    free(winnerHorse);
}

void playHorsesRace(int *money) {
    int bet, decision;
    char exit, c;

    while (1) {
        printf("Type 'X' to exit Horses Race or 'B' to bet: \n");
        scanf(" %c", &exit);

        if (exit == 'B'|| exit == 'b') {
            printf("Make your bet (min. $150)\n");
            printf("Current balance: $%d\n", *money);
            scanf("%d", &bet);
            while ((c = getchar()) != '\n' && c != EOF); // Clear buffer

            if (bet < 150) {
                printf("The minimum bet is $150, try again.\n\n");
                continue;
            } else if (bet > *money) {
                printf("Insufficient balance.\n\n");
                continue;
            } else {
                *money -= bet;
                char* winnerHorse = horse();
                while (1) {
                    printf("Make your bet:\n");
                    printf("1.Lightninh   2.Bolt   3.Verstappen   4.Senna   5.Lewis  6.Cancelar\n");
                    scanf("%d", &decision);
                    while ((c = getchar()) != '\n' && c != EOF); // Clear buffer

                    if (decision >= 1 && decision <= 5) {
                        if (strcmp(winnerHorse, "Lightning") == 0 && decision == 1 ||
                            strcmp(winnerHorse, "Bolt") == 0 && decision == 2 ||
                            strcmp(winnerHorse, "Verstappen") == 0 && decision == 3 ||
                            strcmp(winnerHorse, "Senna") == 0 && decision == 4 ||
                            strcmp(winnerHorse, "Lewis") == 0 && decision == 5) {
                            printf("You won!\n");
                            *money += 3 * bet;
                        } else {
                            printf("You lost! The horse Winner was: %s\n", winnerHorse);
                        }
                        free_winnerHorse(winnerHorse);
                        break;
                    } else if (decision == 6) {
                        printf("Forfeited!\n");
                        free_winnerHorse(winnerHorse);
                        break;
                    } else {
                        printf("Invalid choice, try again.\n");
                    }
                }
            }
        } else if (exit == 'X' || exit == 'x') {
            clrscr();
            break;
        } else {
            printf("Invalid command\n");
            continue;
        }
    }
}

void playBlackJack(int *money) {
    srand(time(NULL));

    while(1){
        int cards[12] = {1,2,3,4,5,6,7,8,9,10,10,10};
        int cardsUser = 0, cardsHouse = 0, decision, bet;
        float blackJack, victory;
        char exit;

        cardsHouse = 0;
        cardsUser = 0;
        cardsHouse += cards[rand() % 12];
        cardsUser += cards[rand() % 12];
        printf("Type 'X' to exit BlackJack or 'B' to bet: \n");
        scanf(" %c",&exit);
        if(exit == 'B'|| exit == 'b'){
            printf("Make your bet (min. $100)\n");
            printf("Current balance: $%d\n\n", *money);
            scanf("%d", &bet);
            blackJack = (2.5 * bet);
            victory = (2 * bet);

            if(bet < 100){
                printf("The minimum bet is $100, try again.\n\n");
                continue;
            } else if(bet > *money){
                printf("Insufficient balance.\n\n");
                continue;
            }else {
                *money -= bet;
                printf("Your sum = %d\n", cardsUser);
                printf("House's sum = %d\n", cardsHouse);
                while(1){
                    if(cardsHouse < 21 && cardsUser < 21){
                        printf("Escolha:\n");
                        printf("1. Buy  2. Keep  3. Forfeit\n");
                        scanf("%d", &decision);

                        if(decision == 1 && cardsHouse > 17){
                            cardsUser += cards[rand() % 12];
                            if (cardsUser > 21){
                                printf("You lost!\n\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                break;
                            } else if (cardsUser == 21){
                                printf("Blackjack!\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                *money += blackJack;
                                break;
                            } else {
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                continue;
                            }
                        } else if(decision == 1 && cardsHouse <= 17){
                            cardsUser += cards[rand() %12];
                            if(cardsHouse > 21){
                                printf("You won!The House busted!\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                *money += victory;
                                break;
                            } else if(cardsUser == 21){
                                printf("Blackjack!\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                *money += blackJack;
                                break;
                            } else if (cardsHouse == 21){
                                printf("House's BlackJack!\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                break;
                            } else if (cardsUser > 21){
                                printf("You lost!\n\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                break;
                            } else {
                                cardsHouse += cards[rand() % 12];
                                if(cardsHouse > 21){
                                    printf("You won!The House busted!\n");
                                    printf("Your sum = %d\n", cardsUser);
                                    printf("House's sum = %d\n", cardsHouse);
                                    *money += victory;
                                    break;
                                } else if (cardsHouse == 21){
                                    printf("House's BlackJack!\n");
                                    printf("Your sum = %d\n", cardsUser);
                                    printf("House's sum = %d\n", cardsHouse);
                                    break;
                                } else {
                                    printf("Your sum = %d\n", cardsUser);
                                    printf("House's sum = %d\n", cardsHouse);
                                    continue;
                                }
                            }
                        } else if(decision == 2 && cardsHouse < cardsUser){
                            cardsHouse += cards[rand() % 12];
                            if(cardsHouse > 21){
                                printf("You won!The House busted!\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                *money += victory;
                                break;
                            } else if (cardsHouse == 21){
                                printf("House's BlackJack!\n");
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                break;
                            } else {
                                printf("Your sum = %d\n", cardsUser);
                                printf("House's sum = %d\n", cardsHouse);
                                continue;
                            }
                        } else if(decision == 2 && cardsHouse >= cardsUser){
                            printf("You lost!\n\n");
                            printf("Your sum = %d\n", cardsUser);
                            printf("House's sum = %d\n", cardsHouse);
                            break;
                        } else {
                            printf("Forfeited!\n");
                            printf("Your sum = %d\n", cardsUser);
                            printf("House's sum = %d\n", cardsHouse);
                            break;
                        }
                    }
                }
            }
        }else if(exit == 'X' || exit == 'x'){
            clrscr();
            break;
        }else{
            printf("Invalid command");
            continue;
        }
    }
}

void playRoulette(int *money) {
    srand(time(NULL));
    int bet, decision, chute, sorteio;
    char exit, c;

    while(1) {
        printf("Type 'X' to exit Roullete or 'B' to bet: \n");
        scanf(" %c", &exit);
        while ((c = getchar()) != '\n' && c != EOF); // Clear buffer

        if(exit == 'B'|| exit == 'b') {
            printf("Make your bet (min. $50)\n");
            printf("Current balance: $%d\n", *money);
            scanf("%d", &bet);

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
                    printf("1. Evens  2. Odds  3. 0 or 00  4. Choose a number  5. Cancel\n");
                    scanf("%d", &decision);
                    sorteio = rand() % 38;

                    if(decision == 1) {
                        if (sorteio != 0 && sorteio % 2 == 0) {
                            printf("You won!The drawn number was: %d\n", sorteio);
                            *money += 2 * bet;
                            break;
                        } else {
                            printf("You lost! The drawn number was: %d\n", sorteio);
                            break;
                        }
                    } else if (decision == 2) {
                        if(sorteio % 2 != 0 && sorteio != 37) {
                            printf("You won!The drawn number was: %d\n", sorteio);
                            *money += 2 * bet;
                            break;
                        } else {
                            printf("You lost! The drawn number was: %d\n", sorteio);
                            break;
                        }
                    } else if(decision == 3) {
                        if(sorteio == 0 || sorteio == 37) {
                            printf("You won!The drawn number was: 0\n");
                            *money += 5 * bet;
                            break;
                        } else {
                            printf("You lost! The drawn number was: %d\n", sorteio);
                            break;
                        }
                    } else if(decision == 4) {
                        printf("Choose a number (from 0 to 36): ");
                        scanf("%d", &chute);
                        if(chute == sorteio) {
                            printf("You won!The drawn number was: %d\n", sorteio);
                            *money += 10 * bet;
                            break;
                        }else if(chute == 0 && sorteio == 37){
                            printf("You won!The drawn number was: 00\n");
                            *money += 10 * bet;
                            break;
                        } else {
                            printf("You lost! The drawn number was: %d\n", sorteio);
                            break;
                        }
                    } else if(decision == 5) {
                        printf("exiting...\n");
                        break;
                    }
                }
            }
        } else if(exit == 'x' || exit == 'X') {
            clrscr();
            break;
        } else {
            printf("Invalid command\n");
            continue;
        }
    }
}

void playAdivinha(int *money) {
    srand(time(NULL));
    int tries = 0, secretNumber, guess, bet;
    char exit, c;

    while(1) {
        printf("Type 'X' to exit Guess the Number or 'B' to bet: \n");
        scanf(" %c", &exit);
        while ((c = getchar()) != '\n' && c != EOF); // Clear buffer

        if(exit == 'B'|| exit == 'b') {
            printf("Make your bet (min. $10)\n");
            printf("Current balance: $%d\n", *money);
            scanf("%d", &bet);
            while ((c = getchar()) != '\n' && c != EOF); // Clear buffer

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
                    scanf("%d", &guess);
                    if(guess > 10 || guess < 1){
                        continue;
                    }else{
                        if (tries < 2) {
                        if (guess > secretNumber) {
                            printf("The secret number is lower than %d\n", guess);
                            tries++;
                            printf("%d tries restantes\n\n", 3 - tries);
                        } else if (guess < secretNumber) {
                            printf("The secret number is higher than %d\n", guess);
                            tries++;
                            printf("%d tries left\n\n", 3 - tries);
                        } else {
                            printf("You got it!\n");
                            *money += 1.5 * bet;
                            break;
                        }
                    } else if (tries == 2) {
                        if (guess == secretNumber) {
                            printf("You got it!\n");
                            *money += 1.5 * bet;
                        } else {
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

int main() {
    int decision, money = 500;
    while(money >= 50) {
        printf("Current balance: $%d\n", money);
        printf("Choose what to play:\n");
        printf("1. BlackJack  2. Roulette  3. Horse Race  4.Guess the number  5. Exit\n");
        scanf("%d", &decision);

        if(decision == 1) {
            playBlackJack(&money);
        } else if(decision == 2) {
            playRoulette(&money);
        } else if(decision == 3) {
            playHorsesRace(&money);
        }else if(decision ==4){
            playAdivinha(&money);
        } else if(decision == 5) {
            printf("exiting casino...\n");
            printf("Final balance: $%d",money);
            break;
        } else {
            printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}
