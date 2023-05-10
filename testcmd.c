#include <stdio.h>
#include "commands.h"
int main(int argc, char *argv[]) {
    while (1) {
        Command *c = create_command();
        read_from_stdin(c);
        printf("Name: %s\n", c->name);
        printf("int_size: %d\nint_param: ", c->int_size);
        for (int i = 0; i<c->int_size; i++) {
            printf("%d ", c->int_param[i]);
        }
        printf("\nchar_size: %d\nchar_param: ", c->char_size);
        for (int i = 0; i<c->char_size; i++) {
            printf("%s ", c->char_param[i]);
        }
        printf("\n");
        free_cmd(c);
    }
}