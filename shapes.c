#include <stdio.h>
#include <stdlib.h>


// POINTS

typedef struct
{
    int x;
    int y;
} Point;

Point *create_point(int px, int py) {
    Point *point = malloc(sizeof(Point));
    if (point != NULL) {
        point->x = px;
        point->y = py;
    }
    return point;
}

void delete_point(Point *p) {
    free(p);
}

void print_point(Point *p) {
    printf("POINT | %i %i", p->x, p->y);
}


// LINES

typedef struct
{
    Point *p1;
    Point *p2;
} Line;

Line *create_line(Point *p1, Point *p2) {
    Line *line = malloc(sizeof(Line));
    if (line != NULL) {
        line->p1 = p1;
        line->p2 = p2;
    }
    return line;
}

void delete_line(Line *l) {
    free(l);
}

void print_line(Line *l) {
    printf("LINE | P1 %i %i | P2 %i %i", l->p1->x,l->p1->y,l->p2->x,l->p2->y);
}


// SQUARES

typedef struct {
    Point *p;
    int lenght;
} Square;

Square *create_square(Point *p, int lenght) {
    Square *square = malloc(sizeof(Square));
    if (square != NULL) {
        square->p = p;
        square->lenght = lenght;
    }
    return square;
}

void delete_square(Square *s) {
    free(s);
}

void print_square(Square *s) {
    printf("SQUARE | P %i %i | L %i", s->p->x, s->p->y, s->lenght);
}


// RECTANGLES

typedef struct
{
    Point *p;
    int width;
    int height;
} Rect;

Rect *create_rect(Point *p, int width, int height) {
    Rect *rect = malloc(sizeof(Rect));
    if (rect != NULL) {
        rect->p = p;
        rect->width = width;
        rect->height = height;
    }
}

void delete_rect(Rect *r) {
    free(r);
}

void print_rect(Rect *r) {
    printf("RECT | P %i %i | W %i | H %i", r->p->x, r->p->y, r->width, r->height);
}