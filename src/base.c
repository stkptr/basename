#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "element.h"
#include "elist.h"
#include "trie.h"


struct pair_s {
    int lower;
    int upper;
};


// Checks if n is an integer
int integral(double n) {
    return ceil(n) == n;
}


// Swap the values in the pair if they are out of order
struct pair_s rearrange(struct pair_s s) {
    if (s.lower > s.upper) {
        int t = s.lower;
        s.lower = s.upper;
        s.upper = t;
    }

    return s;
}

// Returns the closest factors for n
struct pair_s factorize(int n) {
    // no integer n has a divisor that is ceil(sqrt(n))
    // and all divisors are obtained from floor(sqrt(n)) or less
    int fsquare = floor(sqrt(n));
    double d = fsquare + 1;
    struct pair_s s;
    double f;

    do {
        d--;
        f = (double)n / d;
    } while (!integral(f));

    s.lower = f;
    s.upper = d;

    s = rearrange(s);

    return s;
}


void test_factor() {
    for (int i = 1; i < 25; i++) {
        struct pair_s s = factorize(i);
        printf("%i: %i %i %s\n", i, s.lower, s.upper, (s.lower == 1) ? "prime" : "compound");
    }
}


// The bases that are single roots
int is_base_case(int n) {
    switch (n) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        //
        case 16:
        case 17:
        //
        case 20:
        //
        case 36:
        //
        case 100:
            return 1;
        default:
            return 0;
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


struct pair_s smart_factor(int n) {
    struct pair_s s;
    if (n % 100 == 0) {
        s.lower = n / 100;
        s.upper = 100;
        s = rearrange(s);
        return s;
    }
    
    // considering that biniftimal (72) is canonically octononary
    // checking for divisibility by 36 isn't needed

    return factorize(n);
}


void construct(struct element_list_s *el, int n, int is_final, int depth) {
    struct pair_s s;

    if (is_base_case(n)) {
        elist_append_with_favor(el, base_as_element(n, is_final, !depth));
        return;
    }

    // negative numbers
    else if (n < 0) {
        elist_append(el, ELEMENT_VALUE_NEGA);
        construct(el, n * -1, 1, depth + 1);
        return;
    }

    s = smart_factor(n);

    // Primes (un + base)
    if (s.lower == 1) {
        if (is_final) {
            elist_append_with_favor(el, ELEMENT_VALUE_UN);
        } else {
            elist_append_with_favor(el, ELEMENT_VALUE_HEN);
        }

        construct(el, n - 1, is_final, depth + 1);

        if (!is_final) {
            elist_append_with_favor(el, ELEMENT_VALUE_SNA);
        }

        return;
    }

    // Fork the tree
    construct(el, s.lower, 0, depth + 1);
    construct(el, s.upper, is_final, depth + 1);
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


// Name the integral base n
// User must free
char *name(int n) {
    struct element_list_s *el = elist_new();
    char *str;
    construct(el, n, 1, 0);
    str = elist_name(el);
    elist_free(el);
    return str;
}


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
