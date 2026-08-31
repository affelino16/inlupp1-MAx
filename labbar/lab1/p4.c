#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int total = 0;
    for(int i = 1; i <= argc; i++) {
        for(int j = 1; j <= i; j + argv[0]) {
            char *ast = "*";
            printf("%s",ast);
            
            
        } printf("\n");
        total = total + i;
    } printf("total: %d\n", total);
    return 0;
}