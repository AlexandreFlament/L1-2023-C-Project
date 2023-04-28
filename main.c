#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "storage.h"
#include "area.h"

int running = 1, c;

void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void optionA(Area *ar) {
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
        clear_buffer();
        printf("\n");

    }
    int x, y, x1, y1, r, w, h, l;
    switch (choice) {
        case 1:
            printf("         >> Enter the x and y coordinates: ");
            scanf("%i %i", &x, &y);
            clear_buffer();
            add_shape_to_area(ar, create_point_shape(x,y, 1));
            break;
        
        case 2:
            printf("         >> Enter the x and y coordinates of the first point: ");
            scanf("%i %i", &x, &y);
            clear_buffer();
            printf("         >> Enter the x and y coordinates of the second point: ");
            scanf("%i %i", &x1, &y1);
            clear_buffer();
            add_shape_to_area(ar, create_line_shape(x,y,x1,y1, 1));
            break;
        
        case 3:
            printf("         >> Enter the x and y coordinates of the origin: ");
            scanf("%i %i", &x, &y);
            clear_buffer();
            printf("         >> Enter the radius of the circle: ");
            scanf("%i", &r);
            clear_buffer();
            add_shape_to_area(ar, create_circle_shape(x,y,r, 1));
            break;
        case 4:
            printf("         >> Enter the x and y coordinates of the top left point: ");
            scanf("%i %i", &x, &y);
            clear_buffer();
            printf("         >> Enter the length: ");
            scanf("%i", &l);
            clear_buffer();
            add_shape_to_area(ar, create_square_shape(x,y,l, 1));
            break;
        case 5:
            printf("         >> Enter the x and y coordinates of the top left point: ");
            scanf("%i %i", &x, &y);
            clear_buffer();
            printf("         >> Enter the width: ");
            scanf("%i", &w);
            clear_buffer();
            printf("         >> Enter the height: ");
            scanf("%i", &h);
            clear_buffer();
            add_shape_to_area(ar, create_rect_shape(x, y, w, h, 1));
            break;
        case 6:
            int counter = 0, running = 1;
            Point *points[100];
            printf("The program will stop once the first and last point are the same\n");
            while (running) {
                printf("         >> Enter the x and y coordinates the point %i: ", counter);
                scanf("%i %i", &x, &y);
                clear_buffer();
                points[counter] = create_point(x,y);
                counter++;
                if (points[0]->x == points[counter-1]->x && points[0]->y == points[counter-1]->y && counter>1) {
                    running = 0;
                }
            }
            add_shape_to_area(ar, create_polygon_shape(points, counter, 1));
            break;
        
        default:
            break;
    }
}

int main() {
    Area *ar = create_area(20, 20);
    clear_area(ar);
    char choice;
    while (running == 1) {
        choice = 'Z';
        printf("Please select an action:\n");
        printf("    A. Add a shape\n");
        printf("    B. Display the list of shapes\n");
        printf("    C. Delete a shape (WIP)\n");
        printf("    D. Draw the shapes\n");
        printf("    E. Help (WIP)\n");
        printf("    F. Exit\n");
        printf(" >> Your choice: ");
        scanf("%c", &choice);
        clear_buffer();
        printf("\n");

        switch (choice) {
            case 'F':
            case 'f':
                running = 0;
                break;
            
            case 'A':
            case 'a':
                optionA(ar);
                printf("\n");
                break;
            
            case 'B':
            case 'b':
                if (ar->nb_shape == 0) {
                    printf("No shape to display\n\n");
                    break;
                }
                for (int i = 0; i < ar->nb_shape; i++) {
                    print_shape(ar->shapes[i]);
                    printf("\n");
                }
                printf("\n");
                break;
            
            case 'D':
            case 'd':
                draw_area(ar);
                print_area(ar);
                printf("\n\n");
                break;

            default:
                break;
        }
        
        if (choice == 'B' || choice == 'b' || choice == 'D' || choice == 'd') {
            printf("Press enter to continue...");
            scanf("%c", &c);
            clear_buffer();
        }
    }

    return 0;
}