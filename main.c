#include <stdio.h>
#include "shapes.h"

int main() {

    Point *p1 = create_point(5,5);
    Point *p2 = create_point(10,10);

    print_point(p1);
    printf("\n");

    Line *l = create_line(p1, p2);
    
    print_line(l);
    printf("\n");

    Square *s = create_square(p1, 10);

    print_square(s);
    printf("\n");

    Rect *r = create_rect(p1, 10, 5);

    print_rect(r);
    printf("\n");

    Circle *c = create_circle(p1, 15);

    print_circle(c);
    printf("\n");

    Polygon *p = create_polygon(2);

    p->points[0] = p1;
    p->points[1] = p2;
    print_polygon(p);

    delete_point(p1);
    delete_point(p2);
    delete_line(l);
    delete_square(s);
    delete_rect(r);
    delete_circle(c);
    delete_polygon(p);

    return 0;
}