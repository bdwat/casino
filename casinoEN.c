#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

int numericDecision() {
    char entry[100];
    int decision;
    
    while (1) {
        fgets(entry, sizeof(entry), stdin);
        if (sscanf(entry, "%d", &decision) == 1) {
            return decision;
        } else {
            printf("\n");
        }
    }
}

char* horses() {
    char* winnerHorse = malloc(20 * sizeof(char));
    srand(time(NULL));
    char horses[] = {'R', 'B', 'V', 'S', 'L'};
    int horseSelector = rand() % 5;

    switch (horses[horseSelector]) {
        case 'R':
            strcpy(winnerHorse, "Lightghting");
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

void playHorseRace(int *money) {
    int bet, decision;
    char exit;

    while (1) {
        printf("Type 'X' to exit Horse Race or 'B' to bet: \n");
        scanf(" %c", &exit);
        getchar(); // Clear buffer

        if (exit == 'B' || exit == 'b') {
            printf("Make your bet (min. $150)\n");
            printf("Current balance: $%d\n", *money);
            bet = numericDecision();

            if (bet < 150) {
                printf("The minimum bet is $150, try again.\n\n");
                continue;
            } else if (bet > *money) {
                printf("Insufficient balance.\n\n");
                continue;
            } else {
                *money -= bet;
                char* winnerHorse = horses();
                while (1) {
                    printf("Make your bet:\n");
                    printf("1.Lightning   2.Bolt   3.Verstappen   4.Senna   5.Lewis  6.Cancelar\n");
                    decision = numericDecision();

                    if (decision >= 1 && decision <= 5) {
                        if ((strcmp(winnerHorse, "Lightning") == 0 && decision == 1) ||
                            (strcmp(winnerHorse, "Bolt") == 0 && decision == 2) ||
                            (strcmp(winnerHorse, "Verstappen") == 0 && decision == 3) ||
                            (strcmp(winnerHorse, "Senna") == 0 && decision == 4) ||
                            (strcmp(winnerHorse, "Lewis") == 0 && decision == 5)) {
                            printf("Você venceu!\n");
                            *money += 3 * bet;
                        } else {
                            clrscr();
                            printf("You lost! The winner horse was:: %s\n", winnerHorse);
                        }
                        free_winnerHorse(winnerHorse);
                        break;
                    } else if (decision == 6) {
                        clrscr();
                        printf("You forfeited!\n");
                        free_winnerHorse(winnerHorse);
                        break;
                    } else {
                        printf("Invalid choice, try again..\n");
                    }
                }
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
