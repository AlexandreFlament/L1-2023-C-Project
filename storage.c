#include <stdlib.h>
#include <stdio.h>
#include "shapes.h"


// SHAPENODE

typedef struct ShapeNode {
    struct ShapeNode* next;
    Shape* shp;
} ShapeNode;

ShapeNode *create_shape_node() {
    ShapeNode *node = malloc(sizeof(ShapeNode));
    if (node != NULL) {
        node->next = NULL;
        node->shp = NULL;
    }
    return node;
}

void delete_shape_node(ShapeNode *node) {
    free(node);
}

void add_shape_to_node(ShapeNode *node, Shape *shp) {
    ShapeNode *shpnode = create_shape_node();
    shpnode->shp = shp;

    if (node->shp == NULL) {
        node->shp = shp;
        return;
    }
    
    ShapeNode *curr = node;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = shpnode;
}

void print_shape_node(ShapeNode *ShpNode) {
    ShapeNode *curr = ShpNode;
    while (curr != NULL) {
        print_shape(curr->shp);
        printf("\n");
        curr = curr->next;
    }
}


// LAYERNODE

typedef struct LayerNode
{
    int id;
    ShapeNode* shps;
    struct LayerNode* next;
} LayerNode;

LayerNode *create_layer_node() {
    LayerNode *node = malloc(sizeof(LayerNode));
    if (node != NULL) {
        node->id = NULL;
        node->shps = NULL;
        node->next = NULL;
    }
    return node;
}

void delete_layer_node(LayerNode *node) {
    free(node);
}