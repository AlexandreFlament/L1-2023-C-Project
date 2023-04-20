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
    Point *pt = (Point*)shp->ptrShape;
    Pixel *p = create_pixel(pt->x, pt->y);
    Pixel **pixel_tab = malloc(sizeof(Pixel*));
    pixel_tab[0] = p;
    *nb_pixels = 1;
    return pixel_tab;
}

Pixel **pixel_line(Shape *shp, int *nb_pixels) {
    Line *ln = (Line*)shp->ptrShape;

    int dx = ln->p2->x - ln->p1->x;
    int dy = ln->p2->y - ln->p1->y;

    int x,y;
    if (dx > 0) {
        int x = ln->p1->x;
        int y = ln->p1->y;
    } else {
        int x = ln->p2->x;
        int y = ln->p2->y;
    }

    int dmin, dmax;
    if (dx < abs(dy)) {
        dmin = dx;
        dmax = abs(dy);
    } else {
        dmin = abs(dy);
        dmax = dx;
    }

    int nb_seg = dmin + 1;
    int nb_pts = (dmax + 1) / nb_seg;
    int remaining = (dmax + 1) % nb_seg;
    *nb_pixels = nb_seg * nb_pts + remaining;

    Pixel **pixel_tab = malloc(*nb_pixels * sizeof(Pixel*));

    int dx_step = dx / dmax;
    int dy_step = dy / dmax;
    int i = 0;
    for (i = 0; i < nb_pts; i++) {
        pixel_tab[i] = create_pixel(x, y);
        x += dx_step * nb_seg;
        y += dy_step * nb_seg;
        for (int j = 1; j < nb_seg; j++) {
            pixel_tab[i * nb_seg + j] = create_pixel(x, y);
            x += dx_step;
            y += dy_step;
        }
    }

    for (int j = 0; j < remaining; j++) {
        pixel_tab[i * nb_seg + j] = create_pixel(x, y);
        x += dx_step;
        y += dy_step;
    }

    return pixel_tab;
}