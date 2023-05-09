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
    cmd->char_param[cmd->char_size++] = p;
}

void add_int_param(Command *cmd, int p) {
    if (cmd->int_size == 200) {
        return;
    }
    cmd->int_param[cmd->int_size++] = p;
}

void free_cmd(Command *cmd) {
    free(cmd->name);
    for (int i = 0; i < cmd->int_size; i++) {
        free(cmd->int_param[i]);
    }
    for (int i = 0; i < cmd->char_size; i++) {
        free(cmd->char_param[i]);
    }
    free(cmd);
}

int read_exec_cmd(Command *cmd, Area *ar) {
    if (!strcmp(cmd->name, "clear")) {
        printf("\e[1;1H\e[2J");
        return 0;
    }
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
            add_shape_to_area(ar, create_rectangle_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], cmd->int_param[3], 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "polygon")) {
        if (cmd->int_size == 4) {
            add_shape_to_area(ar, create_line_shapecreate_line_shape(cmd->int_param[0], cmd->int_param[1], cmd->int_param[2], cmd->int_param[3], 1));
        } else if (cmd->int_size >= 6 && cmd->int_size % 2 == 0) {
            add_shape_to_area(ar, create_polygon_shape(cmd->int_param, cmd->int_size, 1));
        }
        return 0;
    }
    if (!strcmp(cmd->name, "plot")) {
        draw_area(ar);
        return 0;
    }
    if (!strcmp(cmd->name, "list")) {
        if (ar->nb_shape == 0) {
            printf("No shape to display\n\n");
            return 0;
        }
        for (int i = 0; i < ar->nb_shape; i++) {
            print_shape(ar->shapes[i]);
            printf("\n");
        }
        printf("\n");
        return 0;
    }
    if (strcmp(cmd->name, "delete")) {
        if (cmd->int_size >= 1 && cmd->int_param[0] > 0) {
            remove_shape(ar, cmd->int_param[0]);
        }
        return 0;
    }
    if (strcmp(cmd->name, "erase")) {
        erase_area(ar);
        return 0;
    }
    if (strcmp(cmd->name, "help")) {
        printf("ahah no");
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

    char *curr = strtok(input, " ");
    cmd->name = curr;

    while (curr != NULL) {
        if (Xisnumber(curr)) {
            add_int_param(cmd, atoi(curr));
        } else {
            add_str_param(cmd, curr);
        }
        curr = strtok(NULL, " \n");
    }
}
