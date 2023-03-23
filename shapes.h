#ifndef SHAPES_H_
#define SHAPES_H_

typedef struct
{
    int x;
    int y;
} Point ;

Point *create_point(int px, int py);
void delete_point(Point *p);
void print_point(Point *p);



#endif