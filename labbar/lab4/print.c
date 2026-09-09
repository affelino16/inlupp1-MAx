#include <stdio.h>


void print(char *text) {
    char *chtr = text;
while (*chtr != '\0') {
putchar(*chtr);
++chtr;
    } chtr = '\0';
}


int main() {
    print("tjabba\n");
    return 0;
}