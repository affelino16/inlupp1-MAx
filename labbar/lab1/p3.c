#include <stdio.h>

int main(void) {
    int total = 0;
    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= i; j++) {
            char *ast = "*";
            printf("%s",ast);
            
            
        } printf("\n");
        total = total + i;
    } printf("total: %d\n", total);
    return 0;
}