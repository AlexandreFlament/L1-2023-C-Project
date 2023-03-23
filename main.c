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

    delete_point(p1);
    delete_point(p2);
    delete_line(l);
    delete_square(s);    

    return 0;
}