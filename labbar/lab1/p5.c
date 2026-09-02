#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("inte ett tal\n");
    } else {
    int prime = atoi(argv[1]);
    float square = sqrt(prime);
    int limit = floor(square) + 1;
    for (int x = 2; x <= limit; x++) {
        for (int y = 1; y <= prime; y++) {
            int test = y*x;
            if (test == prime ) {
                printf("inte prime\n");
                return 0;
            }
            
            }
        } printf("ärprime\n");
    }

        return 0;
} 