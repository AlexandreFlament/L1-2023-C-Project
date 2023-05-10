#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "area.h"

typedef struct cmd {
    char *name;
    int int_size;
    int int_param[200];
    int char_size;
    char char_param[200][50];
} Command;

Command *create_command();
void add_str_param(Command *cmd, char *p);
void add_int_param(Command *cmd, int p);
void free_cmd(Command *cmd);
int read_exec_cmd(Command *cmd, Area *ar);
int Xisnumber(char *str);
void read_from_stdin(Command *cmd);

#endif