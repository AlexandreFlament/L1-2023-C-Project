#include "shapes.h"
#include <stdlib.h>

typedef struct {
    int pos;
    Layers next;
    Shapes *list;
} Layers;

typedef struct {
    Shapes next;
    Shape *shp;
} Shapes;

Layers *create_layer(int pos) {
    Layers *lyr = malloc(sizeof(Layers));
    if (lyr != NULL) {
        lyr->pos = pos;
        lyr->next = NULL;
        lyr->list = NULL;
    }
    return lyr;
}

Shapes *create_shape_list() {
    Shapes *lst = malloc(sizeof(Shapes));
    if (lst != NULL) {
        lst->next = NULL;
        lst->shp = NULL;
    }
    return lst;
}

void add_layer(Layers lyrs, int pos) {
    
}

void add_shape(Shapes lst, Shape shp) {

}

void remove_layer(Layers lys, int pos) {

}

void remove_shape(Shapes lst, Shape id) {

}