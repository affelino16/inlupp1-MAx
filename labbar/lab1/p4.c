#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int total = 0;
    if (argc < 2 || argc > 3) {
        printf("Sorry\n");
    } else {
        int add = atoi(argv[2]);
        int rows = atoi(argv[1]);
        for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= i * add; j++) {
            char *ast = "*";
            printf("%s",ast);
            total = total + 1;
        } printf("\n");
        } 
        
    } printf("total: %d\n", total);
    return 0;
} 