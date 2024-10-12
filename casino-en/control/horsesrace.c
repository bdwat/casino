#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

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
