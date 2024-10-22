#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void jogarAdivinha(int *dinheiro);