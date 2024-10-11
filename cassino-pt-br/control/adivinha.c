#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void jogarAdivinha(int *dinheiro) {
    srand(time(NULL));
    int tentativas = 0, numero_secreto, palpite, aposta;
    char sair, c;

    while(1) {
        printf("Digite 'X' para sair do jogo de Adivinha ou 'A' para apostar: \n");
        scanf(" %c", &sair);
        while ((c = getchar()) != '\n' && c != EOF); // Limpar o buffer do teclado

        if(sair == 'A' || sair == 'a') {
            printf("Faça a sua aposta (min. $10)\n");
            printf("Saldo disponível: $%d\n", *dinheiro);
            aposta = decisaoNumerica();

            if(aposta < 10) {
                printf("A aposta mínima é de $10, tente novamente.\n\n");
                continue;
            } else if(aposta > *dinheiro) {
                printf("Saldo não disponível.\n\n");
                continue;
            } else {
                *dinheiro -= aposta;
                numero_secreto = rand() % 10 + 1;
                while (1) {
                    printf("\nDigite um número de 1 a 10\n");
                    palpite = decisaoNumerica();
                    if(palpite > 10 || palpite < 0){
                        continue;
                    }else{
                        if (tentativas < 2) {
                            if (palpite > numero_secreto) {
                                clrscr();
                                printf("O número secreto é menor que %d\n", palpite);
                                tentativas++;
                                printf("%d tentativas restantes\n\n", 3 - tentativas);
                            } else if (palpite < numero_secreto) {
                                clrscr();
                                printf("O número secreto é maior que %d\n", palpite);
                                tentativas++;
                                printf("%d tentativas restantes\n\n", 3 - tentativas);
                            } else {
                                clrscr();
                                printf("Você acertou!\n");
                                *dinheiro += 1.5 * aposta;
                                break;
                            }
                        } else if (tentativas == 2) {
                            if (palpite == numero_secreto) {
                                clrscr();
                                printf("Você acertou!\n");
                                *dinheiro += 1.5 * aposta;
                            } else {
                                clrscr();
                                printf("Você perdeu, o número secreto era %d\n", numero_secreto);
                            }
                            break;
                        }
                    }
                }
            }
        } else if(sair == 'X' || sair == 'x') {
            clrscr();
            break;
        } else {
            printf("Comando inválido\n");
            continue;
        }
    }
}