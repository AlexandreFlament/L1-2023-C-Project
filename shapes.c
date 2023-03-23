#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} Point;


Point *create_point(int px, int py) {
    Point *point = malloc(sizeof(Point));
    if (point != NULL) {
        point->x = px;
        point->y = py;
    }
    return point;
}

void delete_point(Point *p) {
    free(p);
}

void print_point(Point *p) {
    printf("POINT %i %i", p->x, p->y);
}