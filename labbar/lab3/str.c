#include <string.h>
#include <stdio.h>

int string_length(char argv[]) {
    int count = 0;
    
    while (argv[count] != '\0') {
        count++;
    } return count;
}

int print(char argv[]) {
    int chtr = 0;
    while (argv[chtr] != '\0') {
        putchar(argv[chtr]);
        chtr++;
    }
    return 0;
}

int println(char argv[]) {
    print(argv);
    print("\n");
    return 0;
}


int main() {
    println ("hej");
    return 0;
}