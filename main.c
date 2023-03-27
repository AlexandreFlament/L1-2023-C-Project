#include <stdio.h>
#include "shapes.h"
#include "storage.h"


int main() {
    ShapeNode *shape_list = create_shape_node();

    Shape *f1 = create_line_shape(5,5,10,10);
    Shape *f2 = create_line_shape(5,5,10,10);
    Shape *f3 = create_line_shape(5,5,10,10);

    ShapeNode *n1 = create_shape_node();
    add_shape_to_node(n1, f1);
    add_shape_to_node(n1, f2);
    add_shape_to_node(n1, f3);

    print_shape_node(n1);
    
    delete_shape_node(n1->next->next);
    delete_shape_node(n1->next);
    delete_shape_node(n1);

    return 0;
}