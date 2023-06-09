#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shapes.h"
#include "area.h"

#define _USE_MATH_DEFINES

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

    clear_area(ar);

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
        delete_shape(area->shapes[i]);
    }
    area->nb_shape = 0;
    clear_area(area);
}

void delete_area(Area* area) {
    for (int i = 0; i<area->height; i++) {
        free(area->mat[i]);
    }
    free(area->mat);
    free(area);
}

void draw_area(Area* area) {
    clear_area(area);

    int nb_pixels;
    Pixel **pixels;
    for (int shpnb = 0; shpnb<area->nb_shape; shpnb++) {
        pixels = create_shape_to_pixel(area->shapes[shpnb], &nb_pixels);
        for (int pix = 0; pix<nb_pixels; pix++) {
            if (area->height > pixels[pix]->py && pixels[pix]->py >= 0 && area->width > pixels[pix]->px && area->width >= 0) {
                area->mat[pixels[pix]->py][pixels[pix]->px] = 1;
            }
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

void remove_shape(Area* area, unsigned int shapeid) {
    for (int i = 0; i<area->nb_shape; i++) {
        if (area->shapes[i]->id == shapeid) {
            int j=i;
            delete_shape(area->shapes[i]);
            for (; j < area->nb_shape; j++) {
                area->shapes[j] = area->shapes[j + 1];
            }
            free(area->shapes[j]);
            area->nb_shape--;
            return;
        }
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

        case CIRCLE:
            return pixel_circle(shape, nb_pixels);
            break;

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
    Line *line = (Line*)shp->ptrShape;

    int xa = line->p1->x;
    int xb = line->p2->x;
    int ya = line->p1->y;
    int yb = line->p2->y;

    if (xa > xb) {
        int temp = xa;
        xa = xb;
        xb = temp;
        temp = ya;
        ya = yb;
        yb = temp;
    }

    int dx = xb - xa;
    int dy = yb - ya;

    int dmin = abs(dx) < abs(dy) ? abs(dx) : abs(dy);
    int dmax = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    int nb_segs = dmin + 1;
    int base_size = (dmax + 1) / nb_segs;
    int remaining = (dmax + 1) % nb_segs;

    int *segments = malloc(nb_segs * sizeof(int));
    for (int i = 0; i < nb_segs; i++) {
        segments[i] = base_size;
    }
    for (int i = 0; i < remaining; i++) {
        segments[i]++;
    }

    Pixel **pixels = malloc((dmax + 1) * sizeof(Pixel *));
    *nb_pixels = 0;

    int x = xa;
    int y = ya;

    int direction = dy < 0 ? -1 : 1;

    for (int i = 0; i < nb_segs; i++) {
        int is_horizontal = abs(dx) > abs(dy);

        for (int j = 0; j < segments[i]; j++) {
            pixels[*nb_pixels] = malloc(sizeof(Pixel));
            pixels[*nb_pixels]->px = x;
            pixels[*nb_pixels]->py = y;
            (*nb_pixels)++;

            if (is_horizontal) {
                x += direction;
            } else {
                y += direction;
            }
        }

        if (is_horizontal) {
            y -= direction;
        } else {
            x += direction;
        }
    }

    return pixels;
}

Pixel **pixel_square(Shape *shp, int* nb_pixels) {
    Square *sq = (Square*)shp->ptrShape;

    int nbpix1, nbpix2, nbpix3, nbpix4; 

    Shape *ln1 = create_line_shape(sq->p->x, sq->p->y, sq->p->x+sq->lenght, sq->p->y, 0);
    Shape *ln2 = create_line_shape(sq->p->x, sq->p->y, sq->p->x, sq->p->y+sq->lenght, 0);
    Shape *ln3 = create_line_shape(sq->p->x, sq->p->y+sq->lenght, sq->p->x+sq->lenght, sq->p->y+sq->lenght, 0);
    Shape *ln4 = create_line_shape(sq->p->x+sq->lenght, sq->p->y, sq->p->x+sq->lenght, sq->p->y+sq->lenght, 0);

    Pixel **p1 = pixel_line(ln1, &nbpix1);
    Pixel **p2 = pixel_line(ln2, &nbpix2);
    Pixel **p3 = pixel_line(ln3, &nbpix3);
    Pixel **p4 = pixel_line(ln4, &nbpix4);
    
    *nb_pixels = nbpix1 + nbpix2 + nbpix3 + nbpix4;
    Pixel **pixel_tab = malloc(*nb_pixels * sizeof(Pixel*));

    delete_shape(ln1); delete_shape(ln2); delete_shape(ln3); delete_shape(ln4);

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

    Shape *ln1 = create_line_shape(rect->p->x, rect->p->y, rect->p->x+rect->width, rect->p->y, 0);
    Shape *ln2 = create_line_shape(rect->p->x, rect->p->y, rect->p->x, rect->p->y+rect->height, 0);
    Shape *ln3 = create_line_shape(rect->p->x, rect->p->y+rect->height, rect->p->x+rect->width, rect->p->y+rect->height, 0);
    Shape *ln4 = create_line_shape(rect->p->x+rect->width, rect->p->y, rect->p->x+rect->width, rect->p->y+rect->height, 0);

    Pixel **p1 = pixel_line(ln1, &nbpix1);
    Pixel **p2 = pixel_line(ln2, &nbpix2);
    Pixel **p3 = pixel_line(ln3, &nbpix3);
    Pixel **p4 = pixel_line(ln4, &nbpix4);

    delete_shape(ln1); delete_shape(ln2); delete_shape(ln3); delete_shape(ln4);

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

Pixel **pixel_polygon(Shape *shp, int* nb_pixels) {
    Polygon *pol = (Polygon*)shp->ptrShape;

    Pixel ***pixel_tab = malloc(sizeof(Pixel**)*(pol->n-1));
    int pixel_count[pol->n];

    *nb_pixels = 0;
    for (int i = 0; i < pol->n-1; i++) {
        Shape *ln = create_line_shape(pol->points[i]->x, pol->points[i]->y, pol->points[i+1]->x, pol->points[i+1]->y, 0);
        pixel_tab[i] = pixel_line(ln, &pixel_count[i]);
        delete_shape(ln);
        *nb_pixels += pixel_count[i];
    }

    Pixel **pixels = malloc(sizeof(Pixel*)*(*nb_pixels));

    int k = 0;
    for (int i = 0; i < pol->n-1; i++) {
        for (int j = 0; j < pixel_count[i]; j++) {
            pixels[k++] = pixel_tab[i][j];
        }
    }

    return pixels;
}

Pixel **pixel_circle(Shape *shape, int *nb_pixels) {
    Circle *circle = (Circle*)shape->ptrShape;

    int x = 0;
    int y = circle->radius;
    int d = circle->radius-1;
    *nb_pixels = 0;

    while (y >= x) {
        *nb_pixels += 8;

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        } else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        } else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }


    Pixel **pixels = malloc(sizeof(Pixel)*(*nb_pixels));
    Pixel *px = NULL;

    x = 0;
    y = circle->radius;
    d = circle->radius-1;
    *nb_pixels = 0;

    while (y >= x) {
        px = create_pixel(circle->center->x + x, circle->center->y + y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x + y, circle->center->y + x);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x - x, circle->center->y + y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x - y, circle->center->y + x);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x + x, circle->center->y - y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x + y, circle->center->y - x);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x - x, circle->center->y - y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x - y, circle->center->y - x);
        pixels[(*nb_pixels)++] = px;

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        } else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        } else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }

    return pixels;
}