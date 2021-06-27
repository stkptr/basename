#include "base.h"
#include "elist.h"
#include "element.h"
#include "trie.h"


void test_factor() {
    for (int i = 1; i < 25; i++) {
        struct pair_s s = factorize(i);
        printf("%i: %i %i %s\n", i, s.lower, s.upper, (s.lower == 1) ? "prime" : "compound");
    }
}


void test_elist() {
    enum ELEMENT_VALUE ev[] = {
        ELEMENT_VALUE_CENTESIMAL,
        ELEMENT_VALUE_NULLARY,
        ELEMENT_VALUE_UN,
        ELEMENT_VALUE_INVALID,
        ELEMENT_VALUE_SEXIMAL,
        ELEMENT_VALUE_VOT,
        ELEMENT_VALUE_SUBOPTIMAL
    };
    struct element_list_s *el = elist_new();
    char *str;

    for (int i = 0; i < sizeof(ev) / sizeof(enum ELEMENT_VALUE); i++) {
        elist_append(el, ev[i]);
    }

    str = elist_numeric(el);

    printf("Elist: %s\n", str);

    free(str);
    elist_free(el);
}


void test_construct() {
    int values[] = {1, 2, 81, 9023, -5758, 8891, 8213};

    for (int vi = 0; vi < sizeof(values) / sizeof(int); vi++) {
        struct element_list_s *el = elist_new();
        char *str;

        construct(el, values[vi], 1, 0);

        printf("%i\n", values[vi]);

        str = elist_numeric(el);

        printf("  Roots: ");

        for (int i = 0; i < el->element_count; i++) {
            enum ELEMENT_VALUE ev = el->elements[i];
            const char *s = element_as_string(ev);
            if (!element_value_is_preference(ev)) {
                printf("%s ", s);
            }
        }

        printf("\n");

        char *shortcode = elist_shortcode(el, 1);
        printf("  Shortcode: %s\n", shortcode);
        free(shortcode);

        printf("  Numeric: %s\n", str);
        elist_free(el);
    }
}


void test_trie(const char *name) {
    struct element_list_s *el;
    char *str;

    el = elist_from_base_name(name);

    if (el) {
        str = elist_hyphenated(el);
        elist_free(el);
        printf("%s\n", str);
        free(str);
    } else {
        printf("String '%s' could not be parsed.\n", name);
    }
}
