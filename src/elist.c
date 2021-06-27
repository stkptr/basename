#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "elist.h"
#include "element.h"


struct element_list_s *elist_new() {
    struct element_list_s *el = malloc(sizeof(struct element_list_s));
    el->element_count = 0;
    el->box_size = 128;
    el->elements = calloc(el->box_size, sizeof(enum ELEMENT_VALUE));
    return el;
}


void elist_free(struct element_list_s *el) {
    free(el->elements);
    free(el);
}


void elist_append(struct element_list_s *el, enum ELEMENT_VALUE value) {
    // expand forward
    if (el->element_count == el->box_size) {
        el->box_size *= 2;
        el->elements = realloc(el->elements, el->box_size * sizeof(enum ELEMENT_VALUE));
    }
    el->elements[el->element_count++] = value;
}


void elist_append_with_favor(struct element_list_s *el, enum ELEMENT_VALUE value) {
    if (el->element_count) {
        enum ELEMENT_VALUE previous = el->elements[el->element_count - 1];
        elist_append(el, pair_favor(previous, value));
    }
    elist_append(el, value);
}

#define max(n, m) (((n) > (m)) ? (n) : (m))

char *elist_numeric(struct element_list_s *el) {
    size_t count = el->element_count * 4 + 1;
    char *str = calloc(count, sizeof(char));
    int written = 0;
    int offset = 0;

    for (int i = 0; i < el->element_count; i++) {
        // yes %n
        sprintf(str + offset, "%i_%n", el->elements[i], &written);
        offset += written;
    }

    str[max(0, offset - 1)] = '\0';

    return str;
}


char *elist_hyphenated(struct element_list_s *el) {
    // maximum medial element length is 6, except for bakers which is 13 (nice), add one for the hyphen
    // maximum final is 10, except for bakers which is 15
    // +1 for the nul, of course
    // this is extra big if the list has preferences, oh well
    int length = el->element_count * 14 + 15 + 1;
    char *str = calloc(length, sizeof(char));
    int offset = 0;

    for (int i = 0; i < el->element_count; i++) {
        enum ELEMENT_VALUE ev = el->elements[i];
        // skip preferences
        if (ev == ELEMENT_VALUE_PREFER_FIRST
                || ev == ELEMENT_VALUE_PREFER_LAST
                || ev == ELEMENT_VALUE_PREFER_NEITHER) {
            continue;
        }

        int elength = element_length(ev);
        const char *cstr = element_as_string(ev);
        for (int si = 0; si < elength; si++) {
            str[offset++] = cstr[si];
        }

        if (i < el->element_count - 1) {
            str[offset++] = '-';
        }
    }

    return str;
}


char *elist_name(struct element_list_s *el) {
    // see hyphen for details on this equation
    // with divide by two to account for the preferences
    int length = (el->element_count / 2) * 13 + 15 + 1;
    char *str = calloc(length, sizeof(char));
    int offset = 0;

    for (int i = 0; i < el->element_count; i+= 2) {
        enum ELEMENT_VALUE previous, current, next;
        int keep_first = 1, keep_last = 1;

        current = el->elements[i];

        if (i) {
            previous = el->elements[i - 1];
            if (previous == ELEMENT_VALUE_PREFER_FIRST) {
                keep_first = 0;
            }
        }

        if (i < el->element_count - 1) {
            next = el->elements[i + 1];
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


char *elist_shortcode(struct element_list_s *el, int has_favors) {
    int length = el->element_count / (has_favors + 1);
    char *str = calloc(length + 1, sizeof(char));
    int si = 0;

    for (int i = 0; i < el->element_count; i += has_favors + 1) {
        str[si++] = short_code(el->elements[i]);
    }

    return str;
}
