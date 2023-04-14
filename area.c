#include <stdio.h>
#include <stdlib.h>
#include "area.h"


// AREA

Area* create_area(unsigned int width, unsigned int height) {
    Area *ar = malloc(sizeof(Area));

    ar->height = height;
    ar->width = width;

    BOOL **mat = (BOOL**) malloc(sizeof(BOOL*)*height);
    for (int i = 0; i<height; i++) {
        mat[i] = (BOOL*) malloc(sizeof(BOOL)*width);
    }

    ar->mat = mat;
    ar->nb_shape = 0;

    return ar;
}

void add_shape_to_area(Area* area, Shape* shape) {
    area->shapes[area->nb_shape] = shape;
    area->nb_shape++;
}

void clear_area(Area* area) {
    for (int i = 0; i<area->height; i++) {
        for (int j = 0; j<area->width; j++) {
            area->mat[i][j] = 0;
        }
    }
}

void erase_area(Area* area) {
    for (int i = 0; i<area->nb_shape; i++) {
        free(area->shapes[i]);
    }
    area->nb_shape = 0;
    clear_area(area);
}

void delete_area(Area* area) {
    erase_area(area);
    free(area);
}

void draw_area(Area* area) {
    // Done later in the doc
}

void print_area(Area* area) {
    for (int i = 0; i<area->height; i++) {
        for (int j = 0; j< area->width; j++) {
            if (area->mat[i][j]) {
                printf("X ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}


// PIXEL

Pixel* create_pixel(int px, int py) {
    Pixel *p = malloc(sizeof(Pixel));

    p->px = px;
    p->py = py;

    return p;
}

void delete_pixel(Pixel* pixel) {
    free(pixel);
}


// PIXEL DRAWING

Pixel **pixel_point(Shape *shp, int *nb_pixels) {
    Pixel *p = create_pixel(shp->ptrShape->x, shp->ptrShape->y);
    Pixel **pixel_tab = malloc(sizeof(Pixel*));
    pixel_tab[0] = p;
    *nb_pixels = 1;
    return pixel_tab;
}

Pixel **pixel_line(Shape *shp, int *nb_pixels) {
    Point pbegin = shp->ptrShape->p1;
    Point pend = shp->ptrShape->p2;
}