#ifndef SHAPES_H_
#define SHAPES_H_

typedef struct
{
    int x;
    int y;
} Point;

Point *create_point(int px, int py);
void delete_point(Point *p);
void print_point(Point *p);


typedef struct
{
    Point *p1;
    Point *p2;
} Line;

Line *create_line(Point *p1, Point *p2);
void delete_line(Line *l);
void print_line(Line *l);


typedef struct {
    Point *p;
    int lenght;
} Square;

Square *create_square(Point *p, int lenght);
void delete_square(Square *s);
void print_square(Square *s);


typedef struct
{
    Point *p;
    int width;
    int height;
} Rect;

Rect *create_rect(Point *p, int width, int height);
void delete_rect(Rect *s);
void print_rect(Rect *s);


typedef struct
{
    Point *center;
    int radius;
} Circle;

Circle *create_circle(Point *center, int radius);
void delete_circle(Circle *c);
void print_circle(Circle *c);


typedef struct
{
    int n;
    Point **points;
} Polygon;

Polygon *create_polygon(int n);
void delete_polygon(Polygon *p);
void print_polygon(Polygon *p);


typedef enum { POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;

typedef struct {
    int id;
    SHAPE_TYPE shape_type;
    void *ptrShape;
} Shape;

unsigned int get_next_id();
Shape *create_empty_shape(SHAPE_TYPE st);
Shape *create_point_shape(int x, int y);
Shape *create_line_shape(int x1, int y1, int x2, int y2);
Shape *create_square_shape(int x, int y, int lenght);
Shape *create_rect_shape(int x, int y, int width, int height);
Shape *create_circle_shape(int x, int y, int radius);
Shape *create_polygon_shape(Point *points[], int n);
void delete_shape(Shape *shp);
void print_shape(Shape *shp);

#endif