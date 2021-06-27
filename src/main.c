#include <stdlib.h>
#include <stdio.h>

#include "base.h"

#if defined(HYPHEN) || defined(PARSE)
    #include "elist.h"
    #include "trie.h"
#endif


void print_help(const char *program_name) {
    printf(
        "Usage: %s [base...]\n"
        "\n"
#if defined(NAME)
        "Convert decimal base numbers into jan Misali style base names\n"
#elif defined(HYPHEN)
        "Hyphenate the roots of a base name\n"
#elif defined(PARSE)
        "Convert base names into decimal base numbers\n"
#endif
        , program_name);
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
#if defined(NAME)
        char *str = name(atoi(argv[i]));
        printf("%s\n", str);
        free(str);
#elif defined(HYPHEN)
        struct element_list_s *el;
        char *str;
        el = elist_from_base_name(argv[i]);
        str = elist_hyphenated(el);
        printf("%s\n", str);
        elist_free(el);
        free(str);
#elif defined(PARSE)
#endif
    }

    return 0;
}
