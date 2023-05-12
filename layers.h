#ifndef LAYERS_H_
#define LAYERS_H_

#include <stdio.h>
#include <stdlib.h>
#include "area.h"

typedef struct Layer {
    unsigned int id;
    int visible;
    Area *ar;
    struct Layer *succ;
} Layer;

Layer *create_layer(Area *ar);
void delete_layer(Layer *lyr);
void add_layer(Layer *head, Layer *toadd);
int remove_layer(Layer *head, unsigned int id);
void print_layer(Layer *head, unsigned int selectedid);
int change_layer_visibility(Layer *lyr, int id);

#endif