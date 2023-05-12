#include "layers.h"

unsigned int id=0;

int getid() {
    return id++;
}

Layer *create_layer(Area *ar) {
    Layer *lyr = malloc(sizeof(Layer));

    lyr->id = getid();
    lyr->visible = 1;
    lyr->ar = ar;
    lyr->succ = NULL;

    return lyr;
}

void delete_layer(Layer *lyr) {
    delete_area(lyr->ar);
    free(lyr);
}

void add_layer(Layer *head, Layer *toadd) {
    Layer *curr = head;
    while (curr->succ != NULL) {
        curr = curr->succ;
    }
    curr->succ = toadd;
}

int remove_layer(Layer *head, unsigned int id) {
    if (head->succ == NULL) {
        return 2;
    }
    Layer *prev = head;
    Layer *curr = head->succ;
    while (curr != NULL) {
        if (curr->id == id) {
            prev->succ = curr->succ;
            delete_layer(curr);
            return 1;
        }
        prev = curr;
        curr = curr->succ;
    }
    return 0;
}

void print_layer(Layer *head, unsigned int selectedid) {
    Layer *curr = head;
    while (curr != NULL) {
        if (curr->id == selectedid) {
            printf(" * ");
        } else {
            printf(" - ");
        }
        if (curr->visible) {
            printf("Visible layer %i\n", curr->id);
        } else {
            printf("Invisible layer %i\n", curr->id);
        }
        curr = curr->succ;
    }
}

int change_layer_visibility(Layer *head, int id) {
    Layer *curr = head;
    while (curr != NULL) {
        if (curr->id == id) {
            if (curr->visible == 0) {
                curr->visible = 1;
                return 0;
            } else {
                curr->visible = 0;
                return 1;
            }
        }
        curr = curr->succ;
    }
    return -1;
}

void draw_layers(Layer *head) {
    Layer *curr = head;
    while (curr != NULL) {
        draw_area(curr->ar);
        curr = curr->succ;
    }
    curr = head;
    while (curr != NULL) {
        for (int i = 0; i<head->ar->height; i++) {
            for (int j = 0; j<head->ar->width; j++) {
                if (curr->ar->mat[i][j] == 1) {
                    head->ar->mat[i][j] = 1;
                }
            }
        }
        curr = curr->succ;
    }
}