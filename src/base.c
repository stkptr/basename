#include <math.h>

#include "base.h"
#include "element.h"
#include "elist.h"
#include "trie.h"


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


char *name(int n) {
    struct element_list_s *el = elist_new();
    char *str;
    construct(el, n, 1, 0);
    str = elist_name(el);
    elist_free(el);
    return str;
}
