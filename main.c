#include <stdio.h>
#include "shapes.h"

 
int main() {

    Shape *f1 = create_line_shape(5,5,10,10);
    Shape *f2 = create_line_shape(5,5,10,10);
    Shape *f3 = create_line_shape(5,5,10,10);


    print_shape(f1);
    printf("\n");
    print_shape(f2);
    printf("\n");
    print_shape(f3);

    delete_shape(f1);
    delete_shape(f2);
    delete_shape(f3);



    return 0;
}