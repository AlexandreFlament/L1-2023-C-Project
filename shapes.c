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
    return rect;
}

void delete_rect(Rect *r) {
    free(r);
}

void print_rect(Rect *r) {
    printf("RECT | P %i %i | W %i | H %i", r->p->x, r->p->y, r->width, r->height);
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
    free(c);
}

void print_circle(Circle *c) {
    printf("CIRCLE | P %i %i | R %i", c->center->x, c->center->y, c->radius);
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
    free(p);
}

void print_polygon(Polygon *p) {
    /* 
    if (p->points[0]->x != p->points[p->n]->x || p->points[0]->y != p->points[p->n]->y) {
        printf("Invalid polygon, P1 != P%i", p->n);
    }
    */
    printf("POLYGON | N %i", p->n);
    for (int i = 0; i<p->n; i++) {
        printf(" | P%i %i %i", i, p->points[i]->x, p->points[i]->y);
    }
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

Shape *create_empty_shape(SHAPE_TYPE st) {
    Shape *shape = malloc(sizeof(Shape));
    if (shape != NULL) {
        shape->id = get_next_id();
        shape->shape_type = st;
        shape->ptrShape = NULL;
    }
    return shape;
}

Shape *create_point_shape(int x, int y) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(x,y);
    shp->ptrShape = p;
    return shp;   
}

Shape *create_line_shape(int x1, int y1, int x2, int y2) {
    Shape *shp = create_empty_shape(LINE);
    Point *p1 = create_point(x1,y1);
    Point *p2 = create_point(x2,y2);
    Line *l = create_line(p1, p2);
    shp->ptrShape = l;
    return shp;
}

Shape *create_square_shape(int x, int y, int lenght) {
    Shape *shp = create_empty_shape(SQUARE);
    Point *p = create_point(x,y);
    Square *sq = create_square(p, lenght);
    shp->ptrShape = sq;
    return shp;
}

Shape *create_rect_shape(int x, int y, int width, int height) {
    Shape *shp = create_empty_shape(RECTANGLE);
    Point *p = create_point(x,y);
    Rect *r = create_rect(p, width, height);
    shp->ptrShape = r;
    return shp;
}

Shape *create_circle_shape(int x, int y, int radius) {
    Shape *shp = create_empty_shape(CIRCLE);
    Point *p = create_point(x,y);
    Circle *c = create_circle(p, radius);
    shp->ptrShape = c;
    return shp;
}

Shape *create_polygon_shape(Point *points[], int n) {
    Shape *shp = create_empty_shape(POLYGON);
    Polygon *p = create_polygon(n);
    p->points = points;
    shp->ptrShape = p;
    return shp;
}

void delete_shape(Shape *shp) {
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
    printf(" | ID %i", shp->id);
}