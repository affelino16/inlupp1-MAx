#include "utils.h"


struct point
{
  int x;
  int y;
};
typedef struct point point_t;

struct rectangle {
    point_t ul;
    point_t lr;
};
typedef struct rectangle rectangle_t;

void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}

void print_point(point_t *p) {
    printf("point(%d,%d)", p->x, p->y);

}


point_t make_point(int *x_cor, int *y_cor) {

        point_t point = {.x = *x_cor, .y = *y_cor};
        return point;
    
} 

void print_rect (rectangle_t *r) {
    point_t *up_left = &r->ul;
    point_t *low_right = &r->lr; 
    printf("rectangle(upper_left=");
    print_point(up_left);
    printf(", lower_right=");
    print_point(low_right);
    printf("\n");
}

rectangle_t make_rect(int x_cor1, int y_cor1, int x_cor2, int y_cor2) {

        point_t point1 = {.x = x_cor1, .y = y_cor1};
        point_t point2 = {.x = x_cor2, .y = y_cor2};
        rectangle_t rect = { .ul = point1, .lr = point2};
        return rect;
    
} 



int area_rect (rectangle_t *rect){
    point_t up_left = rect->ul;
    point_t low_right = rect->lr;
    int height = up_left.y - low_right.y;
    int base = up_left.x - low_right.x;
    int area = height * base;
    return area;
}

bool intersects_rect(rectangle_t *r1, rectangle_t *r2) {
    point_t ul1 = r1->ul;
    point_t ul2 = r2->ul;
    point_t lr1 = r1->lr;
    point_t lr2 = r2->lr;
    if (ul1.x < lr2.x || )

}

int main() {
    rectangle_t rect = make_rect(0, 0, 5, 6);
    int area = area_rect(&rect);
    printf("%d\n", area);

    return 0;
}