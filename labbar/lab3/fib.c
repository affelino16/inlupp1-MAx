#include <stdio.h>
#include <stdlib.h>

/// Den intressanta delen av programmet
long fib_help(int numbers[], int num_size, int index) {
    if (index < num_size  ) {
      if (index == 0) {
        numbers[index] = 0;
      } else if (index == 1) {
        numbers[index] = 1;
      } else {
        numbers[index] = numbers[index - 1] + numbers[index - 2];
      }
        return numbers[index] + fib_help(numbers, num_size, index + 1);

    } else {
       return 0;
    }
}

int fib (int num_size) {
    int numbers[num_size + 1];
     numbers[0] = 0;
    numbers[1] = 1;
    int result;
    result = fib_help(numbers, num_size, 1);
    return result;

}

/// Den ointressanta main()-funktionen
int main(int argc, char *argv[])
{
 printf("%d\n", fib(10));
}
  