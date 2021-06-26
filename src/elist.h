#ifndef ELIST_H
#define ELIST_H

#include "element.h"

// Holds a list of ELEMENT_VALUEs
struct element_list_s {
    int element_count;
    int box_size;
    enum ELEMENT_VALUE *elements;
};

// Constructor
struct element_list_s *elist_new();

// Free an elist
void elist_free(struct element_list_s *el);

// Append/push a value to an elist
void elist_append(struct element_list_s *el, enum ELEMENT_VALUE value);

// Append while automatically adding the favor direction
void elist_append_with_favor(struct element_list_s *el, enum ELEMENT_VALUE value);


// Create a compact representation for a elist
// in the form: 1_8_2_7 for unoctobiseptimal (113)
// User must free
char *elist_str(struct element_list_s *el);

// Create a hyphenated name
// User must free
char *elist_hyphen(struct element_list_s *el);

// Names the elist el according to the vowel ommitting rules
// el MUST have the preference values between each element
// User must free
char *elist_name(struct element_list_s *el);

// Make a shortened code for a base
// User must free
char *elist_shortcode(struct element_list_s *el, int has_favors);

#endif