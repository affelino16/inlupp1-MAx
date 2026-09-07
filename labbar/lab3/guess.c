#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

int main() {
    char *name;
    int number = random() % 1001;
    int guess_count = 1;
    int guess;


   name = ask_question_string("Skriv in ditt namn:\n");

    printf("Du %s", name);
   guess = ask_question_int(", jag tänker på ett tal ... kan du gissa vilket?\n");
    while (guess_count <= 15) {
        if (guess < number) {
            guess_count++; 
            guess = ask_question_int("för litet!");
        } else if (guess > number) {
            guess_count++;
            guess = ask_question_int("för stort");
        } else if (guess == number) {
            printf("Bingo!\n");
            printf("Det tog %s, %d försök att gissa talet!", name, guess_count);
            break; 
        } 
    } printf("Du har slut på gissningar, talet var %d\n" , number);
    return 0; 
}