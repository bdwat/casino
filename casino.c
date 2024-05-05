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

int decisaoNumerica() {
    char entrada[100];
    int decisao;
    
    while (1) {
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &decisao) == 1) {
            return decisao;
        } else {
            printf("\n");
        }
    }
}

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

int main() {
    int decisao;
    int dinheiro = 500;
    while(dinheiro >= 50) {
        printf("Saldo disponível: $%d\n\n", dinheiro);
        printf("Escolha o que jogar:\n");
        printf("1.Corrida de Cavalos  2.BlackJack  3.Roleta  4.Adivinha  5.Crash  6. Sair\n");

        decisao = decisaoNumerica();

        if(decisao == 1){
            jogarCorridaCavalos(&dinheiro);
        }else if(decisao == 2){
            jogarBlackJack(&dinheiro);
        }else if(decisao == 3){
            jogarRoulette(&dinheiro);
        }else if(decisao == 4){
            jogarAdivinha(&dinheiro);
        }else if(decisao == 5){
            jogarCrash(&dinheiro);
        }else if(decisao == 6){
            printf("Saindo do cassino...\n");
            printf("Saldo final: $%d\n", dinheiro);
            break;
        }else{
            printf("Escolha inválida, tente novamente.\n");
        }
    }
    return 0;
}
