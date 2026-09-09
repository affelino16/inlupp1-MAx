#include <string.h>
#include <stdio.h>
char *pr(char *str) {
    char buf[255];
    
    return strdup(buf);
}


int main () {
   char *str = pr("hej");
    printf("%s\n", str);
    return 0;

}