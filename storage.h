#ifndef STORAGE_H_
#define STORAGE_H_

#include "shapes.h"


// SHAPENODE

typedef struct ShapeNode {
    struct ShapeNode* next;
    Shape* shp;
} ShapeNode;

ShapeNode *create_shape_node();
void delete_shape_node(ShapeNode *node);
void add_shape_to_node(ShapeNode *node, Shape *shp);
void print_shape_node(ShapeNode *ShpNode);


// LAYERNODE

typedef struct LayerNode
{
    int id;
    ShapeNode* shps;
    struct LayerNode* next;
} LayerNode;

LayerNode *create_layer_node();
void delete_layer_node(LayerNode *node);

#endif