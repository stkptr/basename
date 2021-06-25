#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "element.h"

// https://www.youtube.com/watch?v=7OEF3JD-jYo


// hecto- is exceptional
// as is feta-

struct pair_s {
    int lower;
    int upper;
};


int integral(double n) {
    return ceil(n) == n;
}

struct pair_s rearrange(struct pair_s s) {
    if (s.lower > s.upper) {
        int t = s.lower;
        s.lower = s.upper;
        s.upper = t;
    }

    return s;
}

// returns the closest factors for n
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


struct element_list_s {
    int element_count;
    int element_begin;
    int box_size;
    enum ELEMENT_VALUE *elements;
};


struct element_list_s *elist_new() {
    struct element_list_s *el = malloc(sizeof(struct element_list_s));
    el->element_count = 0;
    el->element_begin = 15;
    el->box_size = 128;
    el->elements = calloc(el->box_size, sizeof(enum ELEMENT_VALUE));
    return el;
}

void elist_free(struct element_list_s *el) {
    free(el->elements);
    free(el);
}


void elist_resize(struct element_list_s *el) {
    // expand forward
    if (el->element_begin + el->element_count == el->box_size) {
        el->box_size *= 2;
        el->elements = realloc(el->elements, el->box_size * sizeof(enum ELEMENT_VALUE));
    // expand backward
    } else if (el->element_begin == 0) {
        int new_size = el->box_size *= 2;
        enum ELEMENT_VALUE *temp = calloc(new_size, sizeof(enum ELEMENT_VALUE));
        memmove(temp + el->box_size, el->elements, el->box_size);
        free(el->elements);
        el->elements = temp;
        el->element_begin += el->box_size;
        el->box_size = new_size;
    }
}


void elist_append(struct element_list_s *el, enum ELEMENT_VALUE value) {
    elist_resize(el);
    el->elements[el->element_begin + el->element_count++] = value;
}


void elist_append_with_favor(struct element_list_s *el, enum ELEMENT_VALUE value) {
    if (el->element_count) {
        enum ELEMENT_VALUE previous = el->elements[el->element_begin + el->element_count - 1];
        elist_append(el, pair_favor(previous, value));
    }
    elist_append(el, value);
}


void elist_prepend(struct element_list_s *el, enum ELEMENT_VALUE value) {
    elist_resize(el);
    el->element_count++;
    el->elements[--el->element_begin] = value;
}

#define max(n, m) (((n) > (m)) ? (n) : (m))

char *elist_str(struct element_list_s *el) {
    size_t count = el->element_count * 4 + 1;
    char *str = calloc(count, sizeof(char));
    int written = 0;
    int offset = 0;

    for (int i = 0; i < el->element_count; i++) {
        // yes %n
        sprintf(str + offset, "%i_%n", el->elements[el->element_begin + i], &written);
        offset += written;
    }

    str[max(0, offset - 1)] = '\0';

    return str;
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

    str = elist_str(el);

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

    return factorize(n);
}


void construct(struct element_list_s *el, int n, int is_final, int depth) {
    struct pair_s s;

    if (is_base_case(n)) {
        elist_append_with_favor(el, base_as_element(n, is_final, !depth));
        return;
    }

    else if (n < 0) {
        elist_append(el, ELEMENT_VALUE_NEGA);
        construct(el, n * -1, 1, depth + 1);
        return;
    }

    s = smart_factor(n);   // needs a better factorizer

    //printf("Factored %i as %i * %i\n", n, s.lower, s.upper);

    // special case: primes
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

    construct(el, s.lower, 0, depth + 1);
    construct(el, s.upper, is_final, depth + 1);
}


void test_construct() {
    struct element_list_s *el = elist_new();
    char *str;

    construct(el, -5758, 1, 0);

    str = elist_str(el);

    for (int i = 0; i < el->element_count; i++) {
        enum ELEMENT_VALUE ev = el->elements[el->element_begin + i];
        const char *s = element_as_string(ev);
        if (!element_value_is_preference(ev)) {
            printf("%s ", s);
        }
    }

    printf("\n");

    printf("%s\n", str);
    elist_free(el);
}


char *elist_name(struct element_list_s *el) {
    // maximum medial element length is 6, except for bakers which is 13 (nice)
    // divide by two to account for the preferences
    // maximum final is 10, except for bakers which is 15
    // +1 for the nul, of course
    int length = (el->element_count / 2) * 13 + 15 + 1;
    char *str = calloc(length, sizeof(char));
    int offset = 0;

    for (int i = 0; i < el->element_count; i+= 2) {
        enum ELEMENT_VALUE previous, current, next;
        int keep_first = 1, keep_last = 1;

        current = el->elements[el->element_begin + i];

        if (i) {
            previous = el->elements[el->element_begin + i - 1];
            if (previous == ELEMENT_VALUE_PREFER_FIRST) {
                keep_first = 0;
            }
        }

        if (i < el->element_count - 1) {
            next = el->elements[el->element_begin + i + 1];
            if (next == ELEMENT_VALUE_PREFER_LAST) {
                keep_last = 0;
            }
        }

        int elength = element_length(current);
        const char *cstr = element_as_string(current);
        int start = (keep_first) ? 0 : 1;
        int end = elength - ((keep_last) ? 0 : 1);
        for (int si = start; si < end; si++) {
            str[offset++] = cstr[si];
        }
    }

    return str;
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


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        char *str = name(atoi(argv[i]));
        printf("%s\n", str);
        free(str);
    }
}
