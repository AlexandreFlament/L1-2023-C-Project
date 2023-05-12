#include "commands.h"

Command *create_command() {
    Command *cmd = malloc(sizeof(Command));
    cmd->name = malloc(sizeof(char)*10);
    cmd->int_size = 0;
    cmd->char_size = 0;
    return cmd;
}

void add_str_param(Command *cmd, char *p) {
    if (cmd->char_size == 200) {
        return;
    }
    int i = 0;
    while (p[i] != '\0') {
        cmd->char_param[cmd->char_size][i] = p[i];
        i++;
    }
    cmd->char_param[cmd->char_size][i] = '\0';
    cmd->char_size++;
}

void add_int_param(Command *cmd, int p) {
    if (cmd->int_size == 200) {
        return;
    }
    cmd->int_param[cmd->int_size++] = p;
}

void free_cmd(Command *cmd) {
    free(cmd);
}

int read_exec_cmd(Command *cmd, Area *ar, Layer *lyr, int *sid) {
    if (!strcmp(cmd->name, "clear")) {
        printf("\e[1;1H\e[2J");
        return 0;
    } else
    if (!strcmp(cmd->name, "exit")) {
        _Exit(0);
    }
    if (!strcmp(cmd->name, "point")) {
        if (cmd->int_size >= 2) {
            add_shape_to_area(ar, create_point_shape(cmd->int_param[0], cmd->int_param[1], 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "line")) {
        if (cmd->int_size >= 4) {
            add_shape_to_area(ar, create_line_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], cmd->int_param[3], 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "circle")) {
        if (cmd->int_size >= 3) {
            add_shape_to_area(ar, create_circle_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "square")) {
        if (cmd->int_size >= 3) {
            add_shape_to_area(ar, create_square_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "rectangle")) {
        if (cmd->int_size >= 4) {
            add_shape_to_area(ar, create_rect_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], cmd->int_param[3], 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "polygon")) {
        if (cmd->int_size == 4) {
            add_shape_to_area(ar, create_line_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], cmd->int_param[3], 1));
        } else if (cmd->int_size >= 6 && cmd->int_size % 2 == 0) {
            add_shape_to_area(ar, create_polygon_shape(create_point_list(cmd->int_param, cmd->int_size), cmd->int_size, 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "plot")) {
        draw_area(ar);
        return 0;
    }
    if (!strcmp(cmd->name, "list")) {
        if (ar->nb_shape == 0) {
            printf("No shape to display\n");
            return 0;
        }
        for (int i = 0; i < ar->nb_shape; i++) {
            print_shape(ar->shapes[i]);
            printf("\n");
        }
        printf("\n");
        return 0;
    }
    if (!strcmp(cmd->name, "print")) {
        print_area(ar);
    }
    if (!strcmp(cmd->name, "delete")) {
        if (cmd->int_size >= 1 && cmd->int_param[0] > 0) {
            remove_shape(ar, cmd->int_param[0]);
        }
        return 0;
    }
    if (!strcmp(cmd->name, "erase")) {
        erase_area(ar);
        return 0;
    }
    if (!strcmp(cmd->name, "help")) {
        printf("ahah no\n");
        return 0;
    }
    if (!strcmp(cmd->name, "layer")) {
        if (cmd->char_size<1) {
            return 0;
        }

        if (!strcmp(cmd->char_param[0], "draw")) {
            draw_layers(lyr);
            printf("Layers drawn\n");
        }

        if (!strcmp(cmd->char_param[0], "print")) {
            print_area(lyr->ar);
        }

        if (!strcmp(cmd->char_param[0], "list")) {
            print_layer(lyr, *sid);
        }

        if (!strcmp(cmd->char_param[0], "shapes")) {
            if (lyr->ar->nb_shape == 0) {
                printf("No shape to display\n");
                return 0;
            }
            for (int i = 0; i < lyr->ar->nb_shape; i++) {
                print_shape(lyr->ar->shapes[i]);
                printf("\n");
            }
            printf("\n");
            return 0;
        }

        if (!strcmp(cmd->char_param[0], "add")) {
            add_layer(lyr, create_layer(create_area(20,20)));
            printf("Layer added\n");
        }

        if (cmd->int_size<1) {
            return 0;
        }

        if (!strcmp(cmd->char_param[0], "visible")) {
            int res = change_layer_visibility(lyr, cmd->int_param[0]);
            if (res == -1) {
                printf("Layer id doesn't exist\n");
            }
            if (res == 0) {
                printf("Layer visibility changed to visible\n");
            }
            if (res == 1) {
                printf("Layer visibility changed to invisible\n");
            }
        }

        if (!strcmp(cmd->char_param[0], "select")) {
            *sid = cmd->int_param[0];
        }

        if (!strcmp(cmd->char_param[0], "remove") ) {
            if (cmd->char_size>=2) {
                if (!strcmp(cmd->char_param[1], "shape")) {
                    Layer *curr = lyr;
                    while (curr != NULL) {
                        remove_shape(curr->ar, cmd->int_param[0]);
                        curr = curr->succ;
                    }
                    return 0;
                }
            }
            if (cmd->int_param[0] == 0) {
                printf("You may not remove the initial layer.\n");
            } else {
                if (remove_layer(lyr, cmd->int_param[0]) == 1) {
                    printf("Layer removed\n");
                } else {
                    printf("Layer doesn't exist\n");
                }
                if (cmd->int_param[0] == *sid) {
                    *sid = 0;
                }
            }
        }

        if (!strcmp(cmd->char_param[0], "point")) {
            if (cmd->int_size<2) {
                printf("Not enough arguments given\n");
                return 0;
            }
            Layer *curr = lyr;
            while (curr != NULL) {
                if (curr->id == *sid) {
                    Shape *p = create_point_shape(cmd->int_param[0], cmd->int_param[1], 1);
                    add_shape_to_area(curr->ar, p);
                    printf("Point added to Layer %i\n", *sid);
                }

                curr = curr->succ;
            }
        }

        if (!strcmp(cmd->char_param[0], "line")) {
            if (cmd->int_size<4) {
                printf("Not enough arguments given\n");
                return 0;
            }
            Layer *curr = lyr;
            while (curr != NULL) {
                if (curr->id == *sid) {
                    Shape *p = create_line_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], cmd->int_param[3], 1);
                    add_shape_to_area(curr->ar, p);
                    printf("Line added to Layer %i\n", *sid);
                }

                curr = curr->succ;
            }
        }

        if (!strcmp(cmd->char_param[0], "circle")) {
            if (cmd->int_size<3) {
                printf("Not enough arguments given\n");
                return 0;
            }
            Layer *curr = lyr;
            while (curr != NULL) {
                if (curr->id == *sid) {
                    Shape *p = create_circle_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], 1);
                    add_shape_to_area(curr->ar, p);
                    printf("Circle added to Layer %i\n", *sid);
                }

                curr = curr->succ;
            }
        }

        if (!strcmp(cmd->char_param[0], "square")) {
            if (cmd->int_size<3) {
                printf("Not enough arguments given\n");
                return 0;
            }
            Layer *curr = lyr;
            while (curr != NULL) {
                if (curr->id == *sid) {
                    Shape *p = create_square_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], 1);
                    add_shape_to_area(curr->ar, p);
                    printf("Square added to Layer %i\n", *sid);
                }

                curr = curr->succ;
            }
        }

        if (!strcmp(cmd->char_param[0], "rectangle")) {
            if (cmd->int_size<4) {
                printf("Not enough arguments given\n");
                return 0;
            }
            Layer *curr = lyr;
            while (curr != NULL) {
                if (curr->id == *sid) {
                    Shape *p = create_rect_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], cmd->int_param[3], 1);
                    add_shape_to_area(curr->ar, p);
                    printf("Rectangle added to Layer %i\n", *sid);
                }

                curr = curr->succ;
            }
        }

        if (!strcmp(cmd->char_param[0], "polygon")) {
            if (cmd->int_size<6) {
                printf("Not enough arguments given\n");
                return 0;
            }
            Layer *curr = lyr;
            while (curr != NULL) {
                if (curr->id == *sid) {
                    Shape *p = create_polygon_shape(create_point_list(cmd->int_param, cmd->int_size), cmd->int_size/2, 1);
                    add_shape_to_area(curr->ar, p);
                    printf("Square added to Layer %i\n", *sid);
                }

                curr = curr->succ;
            }
        }

        return 0;
    }
}

int Xisnumber(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            
        } else {
            return 0;
        }
        i++;
    }
    return 1;
}

void read_from_stdin(Command *cmd) {
    char input[1024];
    fgets(input, 1024, stdin);

    char *curr = strtok(input, " \n");
    cmd->name = curr;
    curr = strtok(NULL, " \n");

    while (curr != NULL) {
        if (Xisnumber(curr)) {
            add_int_param(cmd, atoi(curr));
        } else {
            add_str_param(cmd, curr);
        }
        curr = strtok(NULL, " \n");
    }
}
