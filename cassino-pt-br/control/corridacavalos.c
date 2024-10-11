#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

char* cavalos() {
    char* cavaloVencedor = malloc(20 * sizeof(char));
    srand(time(NULL));
    char cavalos[] = {'R', 'B', 'V', 'S', 'L'};
    int cavaloSelector = rand() % 5;

    switch (cavalos[cavaloSelector]) {
        case 'R':
            strcpy(cavaloVencedor, "Relâmpago");
            break;
        case 'B':
            strcpy(cavaloVencedor, "Bolt");
            break;
        case 'V':
            strcpy(cavaloVencedor, "Verstappen");
            break;
        case 'S':
            strcpy(cavaloVencedor, "Senna");
            break;
        case 'L':
            strcpy(cavaloVencedor, "Lewis");
            break;
        default:
            break;
    }
    
    return cavaloVencedor;
}

// Função para liberar a memória alocada dinamicamente para o cavalo vencedor
void free_cavaloVencedor(char* cavaloVencedor) {
    free(cavaloVencedor);
}

void jogarCorridaCavalos(int *dinheiro) {
    int aposta, decisao;
    char sair;

    while (1) {
        printf("Digite 'X' para sair da Corrida de Cavalos ou 'A' para apostar: \n");
        scanf(" %c", &sair);
        getchar(); // Limpa o buffer do teclado

        if (sair == 'A' || sair == 'a') {
            printf("Faça a sua aposta (mínimo $150)\n");
            printf("Saldo disponível: $%d\n", *dinheiro);
            aposta = decisaoNumerica();

            if (aposta < 150) {
                printf("A aposta mínima é de $150, tente novamente.\n\n");
                continue;
            } else if (aposta > *dinheiro) {
                printf("Saldo não disponível.\n\n");
                continue;
            } else {
                *dinheiro -= aposta;
                char* cavaloVencedor = cavalos();
                while (1) {
                    printf("Escolha a sua aposta:\n");
                    printf("1.Relâmpago   2.Bolt   3.Verstappen   4.Senna   5.Lewis  6.Cancelar\n");
                    decisao = decisaoNumerica();

                    if (decisao >= 1 && decisao <= 5) {
                        if ((strcmp(cavaloVencedor, "Relâmpago") == 0 && decisao == 1) ||
                            (strcmp(cavaloVencedor, "Bolt") == 0 && decisao == 2) ||
                            (strcmp(cavaloVencedor, "Verstappen") == 0 && decisao == 3) ||
                            (strcmp(cavaloVencedor, "Senna") == 0 && decisao == 4) ||
                            (strcmp(cavaloVencedor, "Lewis") == 0 && decisao == 5)) {
                            printf("Você venceu!\n");
                            *dinheiro += 3 * aposta;
                        } else {
                            clrscr();
                            printf("Você perdeu! O cavalo vencedor foi: %s\n", cavaloVencedor);
                        }
                        free_cavaloVencedor(cavaloVencedor);
                        break;
                    } else if (decisao == 6) {
                        clrscr();
                        printf("Você desistiu!\n");
                        free_cavaloVencedor(cavaloVencedor);
                        break;
                    } else {
                        printf("Escolha inválida, tente novamente.\n");
                    }
                }
            }
        } else if (sair == 'X' || sair == 'x') {
            clrscr();
            break;
        } else {
            clrscr();
            printf("Comando inválido\n");
            continue;
        }
    }
}