#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void jogarCrash(int *dinheiro) {
    int aposta, tentativas = 0;
    char decisao, sair, c;

    srand(time(NULL));

    printf("Bem-vindo ao jogo Crash!\n\n");

    while (1) {
        printf("Digite 'X' para sair do jogo ou 'A' para apostar: \n");
        scanf(" %c", &sair);
        while ((c = getchar()) != '\n' && c != EOF); // Limpar o buffer do teclado
        clrscr();

        if (sair == 'A' || sair == 'a') {
            printf("Saldo disponível: $%d\n", *dinheiro);
            printf("Faça a sua aposta(min. 25$)\n");
            aposta = decisaoNumerica();

            if(aposta < 25){
                printf("A aposta mínima é $25,tente novamente\n");
                continue;
            }else if(aposta > *dinheiro){
                printf("Saldo Insuficiente\n");
                continue;
            }else{
                float multiplicador = 1;
                while (1) {
                    printf("Multiplicador atual: %.2f\n", multiplicador);
                    printf("Digite 'c' para cash out ou 'r' para continuar: ");
                    scanf(" %c", &decisao);
                    clrscr();    
                    if (decisao == 'c' && tentativas > 0) {
                        *dinheiro += aposta * multiplicador;
                        break;
                    } else if (decisao == 'r') {
                        int chance = rand() % 8;
                        if (chance == 1) {
                            printf("Você crashou! Perdeu a aposta.\n");
                            *dinheiro -= aposta;
                            break;
                        }
                        multiplicador += 0.15;
                        tentativas++;
                    } else {
                        printf("Opção inválida! Tente novamente.\n");
                    }
                }
            }
            if (*dinheiro <= 0) {
                printf("Você ficou sem saldo. Fim de jogo!\n");
                break;
            }

            continue;
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