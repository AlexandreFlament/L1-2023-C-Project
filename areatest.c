#include <stdio.h>
#include "area.h"

int main() {

    Area *ar = create_area(9,9);

    int x1,y1,x2,y2;
    printf("x1, y1, x2, y2: ");
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    Shape *shp = create_line_shape(x1,y1,x2,y2);
    add_shape_to_area(ar,shp);

    Shape *shp2 = create_point_shape(4,4);

    draw_area(ar);
    print_area(ar);

    return 0;
}