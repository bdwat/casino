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

void jogarBlackJack(int *dinheiro) {
    srand(time(NULL));

    while(1){
        int cartas[12] = {1,2,3,4,5,6,7,8,9,10,10,10};
        int cartasUser = 0, cartasCasa = 0, decisao, aposta;
        char sair,c;
        double vitoria,blackJack;

        cartasCasa = 0;
        cartasUser = 0;
        cartasCasa += cartas[rand() % 12];
        cartasUser += cartas[rand() % 12];
        printf("Digite 'X' para sair de BlackJack ou 'A' para apostar: \n");
        scanf(" %c",&sair);
        if(sair == 'a' || sair == 'A'){
            printf("Faça a sua aposta (min. $100)\n");
            printf("Saldo disponível: $%d\n\n", *dinheiro);
            aposta = decisaoNumerica();
            blackJack = (2.5 * aposta);
            vitoria = (2 * aposta);


            if(aposta < 100){
                printf("A aposta mínima é de $100, tente novamente.\n\n");
                continue;
            } else if(aposta > *dinheiro){
                printf("Saldo não disponível.\n\n");
                continue;
            }else {
                clrscr();
                *dinheiro -= aposta;
                printf("Sua soma = %d\n", cartasUser);
                printf("Soma da casa = %d\n", cartasCasa);
                while(1){
                    if(cartasCasa < 21 && cartasUser < 21){
                        printf("Escolha:\n");
                        printf("1. Comprar  2. Manter  3. Desistir\n");
                        decisao = decisaoNumerica();

                        if(decisao == 1 && cartasCasa > 17){
                            cartasUser += cartas[rand() % 12];
                            if (cartasUser > 21){
                                clrscr();
                                printf("Você perdeu!\n\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                break;
                            } else if (cartasUser == 21){
                                clrscr();
                                printf("Blackjack!\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                *dinheiro += blackJack;
                                break;
                            } else {
                                clrscr();
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                continue;
                            }
                        } else if(decisao == 1 && cartasCasa <= 17){
                            cartasUser += cartas[rand() %12];
                            if(cartasCasa > 21){
                                clrscr();
                                printf("Você venceu! A casa estourou!\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                *dinheiro += vitoria;
                                break;
                            } else if(cartasUser == 21){
                                clrscr();
                                printf("Blackjack!\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                *dinheiro += blackJack;
                                break;
                            } else if (cartasCasa == 21){
                                clrscr();
                                printf("Blackjack da Casa!\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                break;
                            } else if (cartasUser > 21){
                                clrscr();
                                printf("Você perdeu!\n\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                break;
                            } else {
                                clrscr();
                                cartasCasa += cartas[rand() % 12];
                                if(cartasCasa > 21){
                                    printf("Você venceu! A casa estourou!\n");
                                    printf("Sua soma = %d\n", cartasUser);
                                    printf("Soma da casa = %d\n", cartasCasa);
                                    *dinheiro += vitoria;
                                    break;
                                } else if (cartasCasa == 21){
                                    printf("Blackjack da Casa!\n");
                                    printf("Sua soma = %d\n", cartasUser);
                                    printf("Soma da casa = %d\n", cartasCasa);
                                    break;
                                } else {
                                    printf("Sua soma = %d\n", cartasUser);
                                    printf("Soma da casa = %d\n", cartasCasa);
                                    continue;
                                }
                            }
                        } else if(decisao == 2 && cartasCasa < cartasUser){
                            clrscr();
                            cartasCasa += cartas[rand() % 12];
                            if(cartasCasa > 21){
                                printf("Você venceu! A casa estourou!\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                *dinheiro += vitoria;
                                break;
                            } else if (cartasCasa == 21){
                                printf("Blackjack da Casa!\n");
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                break;
                            } else {
                                printf("Sua soma = %d\n", cartasUser);
                                printf("Soma da casa = %d\n", cartasCasa);
                                continue;
                            }
                        } else if(decisao == 2 && cartasCasa >= cartasUser){
                            clrscr();
                            printf("Você perdeu!\n\n");
                            printf("Sua soma = %d\n", cartasUser);
                            printf("Soma da casa = %d\n", cartasCasa);
                            break;
                        } else if(decisao == 3) {
                            clrscr();
                            printf("Você desistiu!\n");
                            printf("Sua soma = %d\n", cartasUser);
                            printf("Soma da casa = %d\n", cartasCasa);
                            break;
                        }else{
                            printf("Comando inválido\n");
                            continue;
                        }
                    }
                }
            }
        }else if(sair == 'X' || sair == 'x'){
            clrscr();
            break;
        }else{
            printf("Comando inválido\n");
            continue;
        }
    }
}
