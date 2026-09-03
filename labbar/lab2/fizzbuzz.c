#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void print_num(int num) {
    if (num % 15 == 0) {
                printf("Fizz Buzz, ");
            } else if (num % 3 == 0) {
                printf("Fizz, ");
            } else if (num % 5 == 0) {
                printf("Buzz, ");
            } else {
                printf("%d, ", num);
            }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out number\n");
        return 0;
    }
        int x = 0;
        while (argv[1][x] != '\0') {
            if (!isdigit(argv[1][x])) {
                printf("Usage: ./a.out number\n");
                return 0;
            }   
        x++;
    } 
        int input = atoi(argv[1]);

        int i = 1;

        while (i < input) {
            print_num(i); 
            i++;
        }
        printf("%d\n", input);
        return 0; 
}
