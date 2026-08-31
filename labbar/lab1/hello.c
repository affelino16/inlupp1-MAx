#include <stdio.h>

int main(void)
{
  int x = 1;
  int y = 2;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  puts("=====");
  int tmp = 0;
  tmp = x;
  x = y;
  y = tmp;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  return 0;
}