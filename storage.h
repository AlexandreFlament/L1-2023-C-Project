#ifndef STORAGE_H_
#define STORAGE_H_

#include "shapes.h"

typedef struct ShapeNode {
    struct ShapeNode* next;
    Shape* shp;
} ShapeNode;

ShapeNode *create_shape_node();
void delete_shape_node(ShapeNode *node);
void add_shape_to_node(ShapeNode *node, Shape *shp);
void print_shape_node(ShapeNode *ShpNode);

#endif