#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numericDecision() {
    char entry[100];
    int decision;
    
    while (1) {
        fgets(entry, sizeof(entry), stdin);
        if (sscanf(entry, "%d", &decision) == 1) {
            return decision;
        } else {
            printf("\n");
        }
    }
}