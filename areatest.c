#include <stdio.h>
#include "area.h"

int main() {

    Area *ar = create_area(9,9);

    /*
    int x1,y1,x2,y2;
    printf("x1, y1, x2, y2: ");
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    Shape *shp = create_line_shape(x1,y1,x2,y2);
    add_shape_to_area(ar,shp);

    int x, y, l;
    printf("x, y, l: ");
    scanf("%d %d %d",&x, &y, &l);
    Shape *shp = create_square_shape(x, y, l);
    add_shape_to_area(ar, shp);

    int x, y, w, h;
    printf("x, y, w, h: ");
    scanf("%d %d %d %d", &x, &y, &w, &h);
    Shape *shp = create_rect_shape(x, y, w, h);
    add_shape_to_area(ar, shp);

    int counter = 0, running = 1, x, y;
    Point *points[100];
    printf("The program will stop once the first and last point are the same\n");
    while (running) {
        printf("         >> Enter the x and y coordinates the point %i: ", counter);
        scanf("%i %i", &x, &y);
        points[counter] = create_point(x,y);
        counter++;
        if (points[0]->x == points[counter-1]->x && points[0]->y == points[counter-1]->y && counter>1) {
            running = 0;
        }
    }
    Shape *shp = create_polygon_shape(points, counter);
    add_shape_to_area(ar, shp);
    */
    draw_area(ar);
    print_area(ar);

    return 0;
}