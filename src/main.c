#include <stdlib.h>
#include <stdio.h>

#include "base.h"

void print_help(const char *program_name) {
    printf(
        "Usage: %s [base...]\n"
        "\n"
        "Convert decimal base numbers into jan Misali style base names\n",
        program_name);
}


int main(int argc, char *argv[]) {
    // help
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'h') {
            print_help(argv[0]);
            exit(0);
        }
    }

    for (int i = 1; i < argc; i++) {
        char *str = name(atoi(argv[i]));
        printf("%s\n", str);
        free(str);
    }

    return 0;
}
