#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef union { 
int   int_value;
float float_value;
char *string_value;
} answer_t;

typedef bool check_func(char *); 
typedef answer_t convert_func(char *);

extern char *strdup(const char *);



int clear_input_buffer(void) {
int c;
do
        {
c = getchar();
        }
while (c != '\n' && c != EOF);
putchar('\n');
return 0; 
}

bool not_empty(char *str)
{
return strlen(str) > 0;
}

bool is_number(char *str)
{
int len = strlen(str);
int i = 0;
if (str[i] == '-') {
i++;
    }
for (; i < len; i++) {
if (!isdigit(str[i])) {
return false;
            }

        }
return true;
}

int print(char text[]) {
int chtr = 0;
while (text[chtr] != '\0') {
putchar(text[chtr]);
chtr++;
    }
return 0;
}

int println(char text[]) {
print(text);
print("\n");
return 0;
}


int read_string(char *buf, int buf_siz) {
int count = 0;
char scan;
do
    {
scan = getchar();
if (scan == '\n') {
break;
        } else {
buf[count] = scan;
count++;
        }
    } while (count < buf_siz);

if (scan != '\n' || count == buf_siz) {
clear_input_buffer();
        }
buf[count] = '\0';  
return count; 
}

answer_t ask_question(char *question, check_func *check, convert_func *convert) {
int buf_size = 255;
char buf[buf_size];
int read;
do { print(question);
print("\n");
read = read_string(buf, buf_size);
if (!check(buf)) {
read = 0;
print("Uppfyller inte kraven!\n");
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