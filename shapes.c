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

Point **create_point_list(int lst[], int n) {
    Point **p = malloc(sizeof(Point)*n);
    int c = 0;
    for (int i = 0; i<n; i++) {
        p[i] = create_point(lst[c], lst[c+1]);
        c+=2;
        
    }
    return p;
}

void delete_point(Point *p) {
    free(p);
}

void print_point(Point *p) {
    printf("POINT   | P : %i %i\n       ", p->x, p->y);
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
    free(l->p1);
    free(l->p2);
    free(l);
}

void print_line(Line *l) {
    printf("LINE    | P1: %i %i\n        | P2: %i %i\n       ", l->p1->x,l->p1->y,l->p2->x,l->p2->y);
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
    free(s->p);
    free(s);
}

void print_square(Square *s) {
    printf("SQUARE  | P : %i %i\n        | L : %i\n       ", s->p->x, s->p->y, s->lenght);
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
    return rect;
}

void delete_rect(Rect *r) {
    free(r->p);
    free(r);
}

void print_rect(Rect *r) {
    printf("RECT    | P : %i %i\n        | W : %i\n        | H : %i\n       ", r->p->x, r->p->y, r->width, r->height);
}


// CIRCLES

typedef struct
{
    Point *center;
    int radius;
} Circle;

Circle *create_circle(Point *center, int radius) {
    Circle *circle = malloc(sizeof(Circle));
    if (circle != NULL) {
        circle->center = center;
        circle->radius = radius;
    }
    return circle;
}

void delete_circle(Circle *c) {
    free(c->center);
    free(c);
}

void print_circle(Circle *c) {
    printf("CIRCLE  | P : %i %i\n        | R : %i\n       ", c->center->x, c->center->y, c->radius);
}


// POLYGONS

typedef struct
{
    int n;
    Point **points;
} Polygon;

Polygon *create_polygon(int n) {
    Polygon *polygon = malloc(sizeof(Polygon));
    if (polygon != NULL) {
        polygon->n = n;
    }
    return polygon;
}

void delete_polygon(Polygon *p) {
    for (int i = 0; i < p->n; i++) {
        delete_point(p->points[i]);
    }
    free(p->points);
    free(p);
}

void print_polygon(Polygon *p) {
    /* 
    if (p->points[0]->x != p->points[p->n]->x || p->points[0]->y != p->points[p->n]->y) {
        printf("Invalid polygon, P1 != P%i", p->n);
    }
    */
    printf("POLYGON | N : %i", p->n);
    for (int i = 0; i<p->n; i++) {
        printf("\n        | P%i: %i %i", i, p->points[i]->x, p->points[i]->y);
    }
    printf("\n       ");
}


// SHAPES

typedef enum { POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;

typedef struct {
    int id;
    SHAPE_TYPE shape_type;
    void *ptrShape;
} Shape;

unsigned int global_id = 0;

unsigned int get_next_id() {
    global_id++;
    return global_id;
}

Shape *create_empty_shape(SHAPE_TYPE st, int isid) {
    Shape *shape = malloc(sizeof(Shape));
    if (shape != NULL) {
        shape->id = isid ? get_next_id() : 0;
        shape->shape_type = st;
        shape->ptrShape = NULL;
    }
    return shape;
}

Shape *create_point_shape(int x, int y, int isid) {
    Shape *shp = create_empty_shape(POINT, isid);
    Point *p = create_point(x,y);
    shp->ptrShape = p;
    return shp;   
}

Shape *create_line_shape(int x1, int y1, int x2, int y2, int isid) {
    Shape *shp = create_empty_shape(LINE, isid);
    Point *p1 = create_point(x1,y1);
    Point *p2 = create_point(x2,y2);
    Line *l = create_line(p1, p2);
    shp->ptrShape = l;
    return shp;
}

Shape *create_square_shape(int x, int y, int lenght, int isid) {
    Shape *shp = create_empty_shape(SQUARE, isid);
    Point *p = create_point(x,y);
    Square *sq = create_square(p, lenght);
    shp->ptrShape = sq;
    return shp;
}

Shape *create_rect_shape(int x, int y, int width, int height, int isid) {
    Shape *shp = create_empty_shape(RECTANGLE, isid);
    Point *p = create_point(x,y);
    Rect *r = create_rect(p, width, height);
    shp->ptrShape = r;
    return shp;
}

Shape *create_circle_shape(int x, int y, int radius, int isid) {
    Shape *shp = create_empty_shape(CIRCLE, isid);
    Point *p = create_point(x,y);
    Circle *c = create_circle(p, radius);
    shp->ptrShape = c;
    return shp;
}

Shape *create_polygon_shape(Point *points[], int n, int isid) {
    Shape *shp = create_empty_shape(POLYGON, isid);
    Polygon *p = create_polygon(n);
    p->points = malloc(sizeof(Point)*n);
    for (int i = 0; i < n; i++) {
        p->points[i] = create_point(points[i]->x, points[i]->y);
    }
    shp->ptrShape = p;
    return shp;
}

void delete_shape(Shape *shp) {
    switch (shp->shape_type) {
        case POINT:
            delete_point(shp->ptrShape);
            break;
        case LINE:
            delete_line(shp->ptrShape);
            break;
        case SQUARE:
            delete_square(shp->ptrShape);
            break;
        case RECTANGLE:
            delete_rect(shp->ptrShape);
            break;
        case CIRCLE:
            delete_circle(shp->ptrShape);
            break;
        case POLYGON:
            delete_polygon(shp->ptrShape);
            break;
    }
    free(shp);
}

void print_shape(Shape *shp) {
    switch (shp->shape_type)
    {
    case POINT:
        print_point(shp->ptrShape);
        break;
    case LINE:
        print_line(shp->ptrShape);
        break;
    case SQUARE:
        print_square(shp->ptrShape);
        break;
    case RECTANGLE:
        print_rect(shp->ptrShape);
        break;
    case CIRCLE:
        print_circle(shp->ptrShape);
        break;
    case POLYGON:
        print_polygon(shp->ptrShape);
        break;
    default:
        printf("Invalid shape");
        break;
    }
    printf(" | ID: %i", shp->id);
}