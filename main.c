#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "storage.h"

int running = 1;
int c;

void optionA(ShapeNode *shape_list) {
    int choice = 0;
    while (choice < 1 || choice > 7 ) {
        printf("    Please select an action:\n");
        printf("        1. Add a point\n");
        printf("        2. Add a line\n");
        printf("        3. Add a circle\n");
        printf("        4. Add a square\n");
        printf("        5. Add a rectangle\n");
        printf("        6. Add a polygon\n");
        printf("        7. Return to previous menu\n");
        printf("     >> Your choice: ");
        scanf("%i", &choice);
        printf("\n");
    }
    int x, y, x1, y1, r, w, h, l;
    switch (choice) {
        case 1:
            printf("         >> Enter the x and y coordinates: ");
            scanf("%i %i", &x, &y);
            add_shape_to_node(shape_list, create_point_shape(x,y));
            break;
        
        case 2:
            printf("         >> Enter the x and y coordinates of the first point: ");
            scanf("%i %i", &x, &y);
            printf("         >> Enter the x and y coordinates of the second point: ");
            scanf("%i %i", &x1, &y1);
            add_shape_to_node(shape_list, create_line_shape(x,y,x1,y1));
            break;
        
        case 3:
            printf("         >> Enter the x and y coordinates of the origin: ");
            scanf("%i %i", &x, &y);
            printf("         >> Enter the radius of the circle: ");
            scanf("%i", &r);
            add_shape_to_node(shape_list, create_circle_shape(x,y,r));
            break;
        case 4:
            printf("         >> Enter the x and y coordinates of the top left point: ");
            scanf("%i %i", &x, &y);
            printf("         >> Enter the length: ");
            scanf("%i", &l);
            add_shape_to_node(shape_list, create_square_shape(x,y,l));
            break;
        case 5:
            printf("         >> Enter the x and y coordinates of the top left point: ");
            scanf("%i %i", &x, &y);
            printf("         >> Enter the width: ");
            scanf("%i", &w);
            printf("         >> Enter the height: ");
            scanf("%i", &h);
            add_shape_to_node(shape_list, create_rect_shape(x, y, w, h));
            break;
        case 6:
            int counter = 0, running = 1;
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
            add_shape_to_node(shape_list, create_polygon_shape(points, counter));
            break;
        
        default:
            break;
    }
}

int main() {
    ShapeNode *shape_list = create_shape_node();
    char choice;
    while (running == 1) {
        choice = 'Z';
        printf("Please select an action:\n");
        printf("    A. Add a shape\n");
        printf("    B. Display the list of shapes\n");
        printf("    C. Delete a shape (WIP)\n");
        printf("    D. Draw the shapes (WIP)\n");
        printf("    E. Help (WIP)\n");
        printf("    F. Exit\n");
        printf(" >> Your choice: ");
        scanf("%c[¨n]", &choice);
        printf("\n");
        
        switch (choice) {
            case 'F':
            case 'f':
                running = 0;
                break;
            
            case 'A':
            case 'a':
                optionA(shape_list);
                printf("\n");
                break;
            
            case 'B':
            case 'b':
                if (shape_list->shp == NULL) {
                    printf("No shape to display\n\n");
                    break;
                }
                printf("\n");
                print_shape_node(shape_list);
                printf("\n");
                break;

            default:
                break;
        }
        
        if (choice == 'B' || choice == 'b' || choice == 'D' || choice == 'd') {
            printf("Press enter to continue...");
            scanf("%c", &c);
        }
    }

    return 0;
}