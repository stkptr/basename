#ifndef BASE_H
#define BASE_H

#include "elist.h"

struct pair_s {
    int lower;
    int upper;
};

// Returns the closest factors for n
struct pair_s factorize(int n);

// Factorize more similarly to the reference implementation
struct pair_s smart_factor(int n);

// Construct an elist for an integer
void construct(struct element_list_s *el, int n, int is_final, int depth);

// Name the integral base n
// User must free
char *name(int n);

#endif
