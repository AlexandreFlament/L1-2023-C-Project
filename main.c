#include <stdio.h>
#include "shapes.h"

int main() {

    Point *p1 = create_point(5,5);
    Point *p2 = create_point(10,10);
    Line *l = create_line(p1, p2);
    print_point(p1);
    printf("\n");
    print_line(l);
    delete_line(l);
    delete_point(p1);
    delete_point(p2);

    return 0;
}