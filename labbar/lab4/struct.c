#include <stdio.h>

struct point
{
  int x;
  int y;
};

struct point p;


int main() {
    p.x = 10;
    p.y = -42;
    printf("point(x=%d,y=%d)\n", p.x, p.y);
    return 0;
}