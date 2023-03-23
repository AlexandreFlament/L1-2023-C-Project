#include "shapes.h"

int main() {

    Point *p = create_point(5,5);
    print_point(p);
    delete_point(p);

    return 0;
}