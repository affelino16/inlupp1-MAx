#include "utils.h"
#include <stdio.h>

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
int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      clear_input_buffer();
    }
  while (conversions < 1);
  return result;
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


char *ask_question_string(char *question, char *buf, int buf_siz) {
    int read = 0; 

  do
    {
      printf("%s\n", question);
     read = read_string(buf, buf_siz);
     
      
     } while (read == 0);
  return buf;
}
