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

void jogarRoulette(int *dinheiro) {
    srand(time(NULL));
    int aposta, decisao, chute, sorteio;
    char sair, c;

    while(1) {
        printf("Digite 'X' para sair da Roleta ou 'A' para apostar: \n");
        scanf(" %c", &sair);
        clrscr();
        while ((c = getchar()) != '\n' && c != EOF); // Limpar o buffer do teclado

        if(sair == 'A' || sair == 'a') {
            clrscr();
            printf("Faça a sua aposta (min. $50)\n");
            printf("Saldo disponível: $%d\n", *dinheiro);
            aposta = decisaoNumerica();

            if(aposta < 50) {
                printf("A aposta mínima é de $50, tente novamente.\n\n");
                continue;
            } else if(aposta > *dinheiro) {
                printf("Saldo não disponível.\n\n");
                continue;
            } else {
                *dinheiro -= aposta;
                while (1) {
                    printf("Escolha a sua aposta:\n");
                    printf("1. Pares  2. Ímpares  3. 0 ou 00  4. Escolher número  5. Cancelar\n");
                    decisao = decisaoNumerica();

                    sorteio = rand() % 38;

                    if(decisao == 1) {
                        if (sorteio != 0 && sorteio % 2 == 0) {
                            clrscr();
                            printf("Você venceu! O número sorteado foi: %d\n", sorteio);
                            *dinheiro += 2 * aposta;
                            break;
                        } else {
                            clrscr();
                            printf("Você perdeu! O número sorteado foi: %d\n", sorteio);
                            break;
                        }
                    } else if (decisao == 2) {
                        if(sorteio % 2 != 0 && sorteio != 37) {
                            clrscr();
                            printf("Você venceu! O número sorteado foi: %d\n", sorteio);
                            *dinheiro += 2 * aposta;
                            break;
                        } else {
                            clrscr();
                            printf("Você perdeu! O número sorteado foi: %d\n", sorteio);
                            break;
                        }
                    } else if(decisao == 3) {
                        if(sorteio == 0 || sorteio == 37) {
                            clrscr();
                            printf("Você venceu! O número sorteado foi: 0\n");
                            *dinheiro += 5 * aposta;
                            break;
                        } else {
                            clrscr();
                            printf("Você perdeu! O número sorteado foi: %d\n", sorteio);
                            break;
                        }
                    } else if(decisao == 4) {
                        clrscr();
                        printf("Escolha o seu número (entre 1 e 36): \n");
                        scanf("%d", &chute);
                        if(chute == sorteio) {
                            clrscr();
                            printf("Você venceu! O número sorteado foi: %d\n", sorteio);
                            *dinheiro += 10 * aposta;
                            break;
                        } else {
                            clrscr();
                            printf("Você perdeu! O número sorteado foi: %d\n", sorteio);
                            break;
                        }
                    } else if(decisao == 5) {
                        clrscr();
                        printf("Saindo...\n");
                        break;
                    } else {
                        printf("Comando inválido!\n");
                    }
                }
            }
            if (*dinheiro <= 0) {
                printf("Você ficou sem dinheiro. Fim de jogo!\n");
                break;
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
