#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

char* cavalos();
void free_cavaloVencedor(char* cavaloVencedor);
void jogarCorridaCavalos(int *dinheiro);