#include "utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool check_func(char *); 
typedef answer_t convert_func(char *);

bool is_number(char *str)
{
    int len = strlen(str);
    int i = 0;
    if (str[i] == '-') {
        i++;
    }
        for ( i; i < len; i++) {
            if (!isdigit(str[i])) {
                return false;
            }

        }
    
  return true;
}

answer_t ask_question(char *question, check_func *check, convert_func *convert) {
    int buf_size = 30;
    char buf[buf_size];
    int read;
    do { print(question);
        print("\n");
        read = read_string(buf, buf_size);
        if (!check(buf)) {
            read = 0;
        }
    } while(read == 0); 
     answer_t result = convert(buf); 
     return result;
}



int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func *) atoi);
  return answer.int_value; 
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func *) strdup).string_value;
}


int main() {
    int input = ask_question_int1("tjo");
    printf("%d \n", input);
    return 0; 
}