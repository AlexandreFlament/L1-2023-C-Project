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
    clear_area(area);

    int nb_pixels;
    Pixel **pixels;

    for (int shpnb = 0; shpnb<area->nb_shape; shpnb++) {
        pixels = create_shape_to_pixel(area->shapes[shpnb], &nb_pixels);
        for (int pix = 0; pix<nb_pixels; pix++) {
            area->mat[pixels[pix]->py][pixels[pix]->px] = 1;
        }
        delete_pixel_shape(pixels, nb_pixels);
    }
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

Pixel** create_shape_to_pixel(Shape* shape, int *nb_pixels) {
    switch (shape->shape_type) {
        case POINT:
            return pixel_point(shape, nb_pixels);
            break;
        
        case LINE:
            return pixel_line(shape, nb_pixels);
            break;

        case SQUARE:
            return pixel_square(shape, nb_pixels);
            break;

        case RECTANGLE:
            return pixel_rectangle(shape, nb_pixels);
            break;
        /*
        case CIRCLE:
            return pixel_circle(shape, nb_pixels);
            break;
        */
        case POLYGON:
            return pixel_polygon(shape, nb_pixels);
            break;

        default:
            return NULL;
            break;
    }
}

void delete_pixel_shape(Pixel** pixel, int nb_pixels) {
    for (int i = 0; i<nb_pixels; i++) {
        free(pixel[i]);
    }
    free(pixel);
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
        x = ln->p1->x;
        y = ln->p1->y;
    } else {
        x = ln->p2->x;
        y = ln->p2->y;
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

Pixel **pixel_square(Shape *shp, int* nb_pixels) {
    Square *sq = (Square*)shp->ptrShape;

    int nbpix1, nbpix2, nbpix3, nbpix4; 

    Pixel **p1 = pixel_line(create_line_shape(sq->p->x, sq->p->y, sq->p->x+sq->lenght, sq->p->y), &nbpix1);
    Pixel **p2 = pixel_line(create_line_shape(sq->p->x, sq->p->y, sq->p->x, sq->p->y+sq->lenght), &nbpix2);
    Pixel **p3 = pixel_line(create_line_shape(sq->p->x, sq->p->y+sq->lenght, sq->p->x+sq->lenght, sq->p->y+sq->lenght), &nbpix3);
    Pixel **p4 = pixel_line(create_line_shape(sq->p->x, sq->p->y+sq->lenght, sq->p->x+sq->lenght, sq->p->y+sq->lenght), &nbpix4);
    
    *nb_pixels = nbpix1 + nbpix2 + nbpix3 + nbpix4;
    Pixel **pixel_tab = malloc(*nb_pixels * sizeof(Pixel*));

    for (int i = 0; i < nbpix1; i++) {
        pixel_tab[i] = p1[i];
    }
    for (int i = 0; i < nbpix2; i++) {
        pixel_tab[i + nbpix1] = p2[i];
    }
    for (int i = 0; i < nbpix3; i++) {
        pixel_tab[i + nbpix1 + nbpix2] = p3[i];
    }
    for (int i = 0; i < nbpix4; i++) {
        pixel_tab[i + nbpix1 + nbpix2 + nbpix3] = p4[i];
    }

    return pixel_tab;
}

Pixel **pixel_rectangle(Shape *shp, int* nb_pixels) {
    Rect *rect = (Rect*)shp->ptrShape;

    int nbpix1, nbpix2, nbpix3, nbpix4;

    Pixel **p1 = pixel_line(create_line_shape(rect->p->x, rect->p->y, rect->p->x+rect->width, rect->p->y), &nbpix1);
    Pixel **p2 = pixel_line(create_line_shape(rect->p->x, rect->p->y, rect->p->x, rect->p->y+rect->height), &nbpix2);
    Pixel **p3 = pixel_line(create_line_shape(rect->p->x, rect->p->y+rect->height, rect->p->x+rect->width, rect->p->y+rect->height), &nbpix3);
    Pixel **p4 = pixel_line(create_line_shape(rect->p->x+rect->width, rect->p->y, rect->p->x+rect->width, rect->p->y+rect->height), &nbpix4);

    *nb_pixels = nbpix1 + nbpix2 + nbpix3 + nbpix4;
    Pixel **pixel_tab = malloc(*nb_pixels * sizeof(Pixel*));

    for (int i = 0; i < nbpix1; i++) {
        pixel_tab[i] = p1[i];
    }
    for (int i = 0; i < nbpix2; i++) {
        pixel_tab[i + nbpix1] = p2[i];
    }
    for (int i = 0; i < nbpix3; i++) {
        pixel_tab[i + nbpix1 + nbpix2] = p3[i];
    }
    for (int i = 0; i < nbpix4; i++) {
        pixel_tab[i + nbpix1 + nbpix2 + nbpix3] = p4[i];
    }

    return pixel_tab;
}

Pixel **pixel_polygon(Shape *shp, int* nb_pixels) { // not sure if it works, will see when pixel_line works
    Polygon *pol = (Polygon*)shp->ptrShape;

    Pixel ***lines = malloc(sizeof(Line***)*(pol->n-1));
    int lines_size[pol->n-1];

    for (int i = 0; i<pol->n-1; i++) { 
        Shape *line = create_line_shape(pol->points[i]->x,pol->points[i]->y,pol->points[i+1]->x,pol->points[i+1]->y);
        lines[i] = pixel_line(line, &lines_size[i]);
        free_shape(line);
    }

    Pixel **pixel_tab = malloc(sizeof(Pixel*)*lines_size[pol->n-1]);
    *nb_pixels = 0;
    for (int i = 0; i<pol->n-1; i++) {
        for (int j = 0; j<lines_size[i]; j++) {
            pixel_tab[*nb_pixels] = lines[i][j];
            (*nb_pixels)++;
        }
        delete_pixel_shape(lines[i], lines_size[i]);
    }

    free(lines);

    return pixel_tab;
}