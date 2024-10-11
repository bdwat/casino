#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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