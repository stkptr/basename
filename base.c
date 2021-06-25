#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

enum ELEMENT_VALUE {
    ELEMENT_VALUE_INVALID = 999,

    // Special prefixes
    ELEMENT_VALUE_NEGA = -1, // * -1
    ELEMENT_VALUE_VOT = -11,  // pow(-1)

    // finals are prefixed with 6 since the sixth letter of the alphabet is F for final
    // bares are prefixed with 1
    // Base case bases              Non-final multiplicatives   Special
    ELEMENT_VALUE_NULLARY = 60,
    ELEMENT_VALUE_UNARY = 61,       ELEMENT_VALUE_UN = 1, ELEMENT_VALUE_HEN = 80, ELEMENT_VALUE_SNA = 81,
    ELEMENT_VALUE_BINARY = 62,      ELEMENT_VALUE_BI = 2,
    ELEMENT_VALUE_TRINARY = 63,     ELEMENT_VALUE_TRI = 3,
    ELEMENT_VALUE_QUATERNARY = 64,  ELEMENT_VALUE_TETRA = 4,
    ELEMENT_VALUE_QUINARY = 65,     ELEMENT_VALUE_PENTA = 5,
    ELEMENT_VALUE_SEXIMAL = 66,     ELEMENT_VALUE_HEXA = 6,
    ELEMENT_VALUE_SEPTIMAL = 67,    ELEMENT_VALUE_HEPTA = 7,
    ELEMENT_VALUE_OCTAL = 68,       ELEMENT_VALUE_OCTO = 8,
    ELEMENT_VALUE_NONARY = 69,      ELEMENT_VALUE_ENNA = 9,
    ELEMENT_VALUE_DECIMAL = 110,    ELEMENT_VALUE_GESIMAL = 10,
    ELEMENT_VALUE_ELEVENARY = 611,  ELEMENT_VALUE_LEVA = 11,
    ELEMENT_VALUE_DOZENAL = 612,    ELEMENT_VALUE_DOZA = 12,
    ELEMENT_VALUE_BAKERS_DOZENAL = 113, ELEMENT_VALUE_KERS_DOZENAL = 13,
    ELEMENT_VALUE_HEX = 616,        ELEMENT_VALUE_TESSER = 16,
    ELEMENT_VALUE_SUBOPTIMAL = 617, ELEMENT_VALUE_MAL = 17,
    ELEMENT_VALUE_VIGESIMAL = 620,  ELEMENT_VALUE_ICOSI = 20,
    ELEMENT_VALUE_NIFTIMAL = 636,   ELEMENT_VALUE_FETA = 36,
    ELEMENT_VALUE_CENTESIMAL = 600, ELEMENT_VALUE_HECTO = 100, // just to make it 3 digits

    // Suffixes                     Shortened
    ELEMENT_VALUE_NARY = 90,        ELEMENT_VALUE_ARY = 91,
    ELEMENT_VALUE_IMAL = 92,        ELEMENT_VALUE_AL = 93,

    ELEMENT_VALUE_PREFER_NEITHER = 50,
    ELEMENT_VALUE_PREFER_FIRST = 51,
    ELEMENT_VALUE_PREFER_LAST = 52
};


int element_value_is_preference(enum ELEMENT_VALUE ev) {
    switch (ev) {
        case ELEMENT_VALUE_PREFER_NEITHER:
        case ELEMENT_VALUE_PREFER_FIRST:
        case ELEMENT_VALUE_PREFER_LAST:
            return 1;
        default:
            return 0;
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

#define OPTION(final, medial) return (is_final) ? (final) : (medial)
#define BARE(bare, medial) return (is_bare) ? (bare) : (medial)

enum ELEMENT_VALUE base_as_element(int n, int is_final, int is_bare) {
    switch (n) {
        case 0:  OPTION(ELEMENT_VALUE_NULLARY,      ELEMENT_VALUE_INVALID);
        case 1:  OPTION(ELEMENT_VALUE_UNARY,        ELEMENT_VALUE_INVALID);
        case 2:  OPTION(ELEMENT_VALUE_BINARY,       ELEMENT_VALUE_BI);
        case 3:  OPTION(ELEMENT_VALUE_TRINARY,      ELEMENT_VALUE_TRI);
        case 4:  OPTION(ELEMENT_VALUE_QUATERNARY,   ELEMENT_VALUE_TETRA);
        case 5:  OPTION(ELEMENT_VALUE_QUINARY,      ELEMENT_VALUE_PENTA);
        case 6:  OPTION(ELEMENT_VALUE_SEXIMAL,      ELEMENT_VALUE_HEXA);
        case 7:  OPTION(ELEMENT_VALUE_SEPTIMAL,     ELEMENT_VALUE_HEPTA);
        case 8:  OPTION(ELEMENT_VALUE_OCTAL,        ELEMENT_VALUE_OCTO);
        case 9:  OPTION(ELEMENT_VALUE_NONARY,       ELEMENT_VALUE_ENNA);
        case 10: BARE  (ELEMENT_VALUE_DECIMAL,      ELEMENT_VALUE_GESIMAL);
        case 11: OPTION(ELEMENT_VALUE_ELEVENARY,    ELEMENT_VALUE_LEVA);
        case 12: OPTION(ELEMENT_VALUE_DOZENAL,      ELEMENT_VALUE_DOZA);
        case 13: BARE  (ELEMENT_VALUE_BAKERS_DOZENAL, ELEMENT_VALUE_KERS_DOZENAL);
        //
        case 16: OPTION(ELEMENT_VALUE_HEX,          ELEMENT_VALUE_TESSER);
        case 17: OPTION(ELEMENT_VALUE_SUBOPTIMAL,   ELEMENT_VALUE_MAL);
        //
        case 20: OPTION(ELEMENT_VALUE_VIGESIMAL,    ELEMENT_VALUE_ICOSI);
        //
        case 36: OPTION(ELEMENT_VALUE_NIFTIMAL,     ELEMENT_VALUE_FETA);
        //
        case 100:OPTION(ELEMENT_VALUE_CENTESIMAL,   ELEMENT_VALUE_HECTO);
        //
        default: return ELEMENT_VALUE_INVALID;
    }
}

#undef OPTION


const char *element_as_string(enum ELEMENT_VALUE ev) {
    switch (ev) {
        case ELEMENT_VALUE_INVALID: return "invalid";
        //
        case ELEMENT_VALUE_NEGA: return "nega";
        case ELEMENT_VALUE_VOT: return "vot";
        //
        case ELEMENT_VALUE_NULLARY: return "nullary";
        case ELEMENT_VALUE_UNARY: return "unary";
            case ELEMENT_VALUE_UN: return "un";
            case ELEMENT_VALUE_HEN: return "hen";
            case ELEMENT_VALUE_SNA: return "sna";
        case ELEMENT_VALUE_BINARY: return "binary";
            case ELEMENT_VALUE_BI: return "bi";
        case ELEMENT_VALUE_TRINARY: return "trinary";
            case ELEMENT_VALUE_TRI: return "tri";
        case ELEMENT_VALUE_QUATERNARY: return "quaternary";
            case ELEMENT_VALUE_TETRA: return "tetra";
        case ELEMENT_VALUE_QUINARY: return "quinary";
            case ELEMENT_VALUE_PENTA: return "penta";
        case ELEMENT_VALUE_SEXIMAL: return "seximal";
            case ELEMENT_VALUE_HEXA: return "hexa";
        case ELEMENT_VALUE_SEPTIMAL: return "septimal";
            case ELEMENT_VALUE_HEPTA: return "hepta";
        case ELEMENT_VALUE_OCTAL: return "octal";
            case ELEMENT_VALUE_OCTO: return "octo";
        case ELEMENT_VALUE_NONARY: return "nonary";
            case ELEMENT_VALUE_ENNA: return "enna";
        case ELEMENT_VALUE_DECIMAL: return "decimal";
            case ELEMENT_VALUE_GESIMAL: return "gesimal";
        case ELEMENT_VALUE_ELEVENARY: return "elevenary";
            case ELEMENT_VALUE_LEVA: return "leva";
        case ELEMENT_VALUE_DOZENAL: return "dozenal";
            case ELEMENT_VALUE_DOZA: return "doza";
        case ELEMENT_VALUE_BAKERS_DOZENAL: return "baker's dozenal";
            case ELEMENT_VALUE_KERS_DOZENAL: return "ker's dozenal";
        //
        case ELEMENT_VALUE_HEX: return "hex";
            case ELEMENT_VALUE_TESSER: return "tesser";
        case ELEMENT_VALUE_SUBOPTIMAL: return "suboptimal";
            case ELEMENT_VALUE_MAL: return "mal";
        //
        case ELEMENT_VALUE_VIGESIMAL: return "vigesimal";
            case ELEMENT_VALUE_ICOSI: return "icosi";
        //
        case ELEMENT_VALUE_NIFTIMAL: return "niftimal";
            case ELEMENT_VALUE_FETA: return "feta";
        //
        case ELEMENT_VALUE_CENTESIMAL: return "centesimal";
            case ELEMENT_VALUE_HECTO: return "hecto";
        //
        case ELEMENT_VALUE_NARY: return "nary";
            case ELEMENT_VALUE_ARY: return "ary";
        case ELEMENT_VALUE_IMAL: return "imal";
            case ELEMENT_VALUE_AL: return "al";
        //
        case ELEMENT_VALUE_PREFER_NEITHER: return "0";
        case ELEMENT_VALUE_PREFER_FIRST: return "<-";
        case ELEMENT_VALUE_PREFER_LAST: return "->";
    }

    return "";
}


char element_final_char(enum ELEMENT_VALUE ev) {
    switch (ev) {
        case ELEMENT_VALUE_INVALID: return 'd';
        //
        case ELEMENT_VALUE_NEGA: return 'a';
        case ELEMENT_VALUE_VOT: return 't';
        //
        case ELEMENT_VALUE_NULLARY: return 'y';
        case ELEMENT_VALUE_UNARY: return 'y';
            case ELEMENT_VALUE_UN: return 'n';
            case ELEMENT_VALUE_HEN: return 'n';
            case ELEMENT_VALUE_SNA: return 'a';
        case ELEMENT_VALUE_BINARY: return 'y';
            case ELEMENT_VALUE_BI: return 'i';
        case ELEMENT_VALUE_TRINARY: return 'y';
            case ELEMENT_VALUE_TRI: return 'i';
        case ELEMENT_VALUE_QUATERNARY: return 'y';
            case ELEMENT_VALUE_TETRA: return 'a';
        case ELEMENT_VALUE_QUINARY: return 'y';
            case ELEMENT_VALUE_PENTA: return 'a';
        case ELEMENT_VALUE_SEXIMAL: return 'l';
            case ELEMENT_VALUE_HEXA: return 'a';
        case ELEMENT_VALUE_SEPTIMAL: return 'l';
            case ELEMENT_VALUE_HEPTA: return 'a';
        case ELEMENT_VALUE_OCTAL: return 'l';
            case ELEMENT_VALUE_OCTO: return 'o';
        case ELEMENT_VALUE_NONARY: return 'y';
            case ELEMENT_VALUE_ENNA: return 'a';
        case ELEMENT_VALUE_DECIMAL: return 'l';
            case ELEMENT_VALUE_GESIMAL: return 'l';
        case ELEMENT_VALUE_ELEVENARY: return 'y';
            case ELEMENT_VALUE_LEVA: return 'a';
        case ELEMENT_VALUE_DOZENAL: return 'l';
            case ELEMENT_VALUE_DOZA: return 'a';
        case ELEMENT_VALUE_BAKERS_DOZENAL: return 'l';
            case ELEMENT_VALUE_KERS_DOZENAL: return 'l';
        //
        case ELEMENT_VALUE_HEX: return 'x';
            case ELEMENT_VALUE_TESSER: return 'r';
        case ELEMENT_VALUE_SUBOPTIMAL: return 'l';
            case ELEMENT_VALUE_MAL: return 'l';
        //
        case ELEMENT_VALUE_VIGESIMAL: return 'l';
            case ELEMENT_VALUE_ICOSI: return 'i';
        //
        case ELEMENT_VALUE_NIFTIMAL: return 'l';
            case ELEMENT_VALUE_FETA: return 'a';
        //
        case ELEMENT_VALUE_CENTESIMAL: return 'l';
            case ELEMENT_VALUE_HECTO: return 'o';
        //
        case ELEMENT_VALUE_NARY: return 'y';
            case ELEMENT_VALUE_ARY: return 'y';
        case ELEMENT_VALUE_IMAL: return 'l';
            case ELEMENT_VALUE_AL: return 'l';
        //
        default:
            return '\0';
    }

    return '\0';
}

char element_begin_char(enum ELEMENT_VALUE ev) {
    switch (ev) {
        case ELEMENT_VALUE_INVALID: return 'i';
        //
        case ELEMENT_VALUE_NEGA: return 'n';
        case ELEMENT_VALUE_VOT: return 'v';
        //
        case ELEMENT_VALUE_NULLARY: return 'n';
        case ELEMENT_VALUE_UNARY: return 'u';
            case ELEMENT_VALUE_UN: return 'u';
            case ELEMENT_VALUE_HEN: return 'h';
            case ELEMENT_VALUE_SNA: return 's';
        case ELEMENT_VALUE_BINARY: return 'b';
            case ELEMENT_VALUE_BI: return 'b';
        case ELEMENT_VALUE_TRINARY: return 't';
            case ELEMENT_VALUE_TRI: return 't';
        case ELEMENT_VALUE_QUATERNARY: return 'q';
            case ELEMENT_VALUE_TETRA: return 't';
        case ELEMENT_VALUE_QUINARY: return 'q';
            case ELEMENT_VALUE_PENTA: return 'p';
        case ELEMENT_VALUE_SEXIMAL: return 's';
            case ELEMENT_VALUE_HEXA: return 'h';
        case ELEMENT_VALUE_SEPTIMAL: return 's';
            case ELEMENT_VALUE_HEPTA: return 'h';
        case ELEMENT_VALUE_OCTAL: return 'o';
            case ELEMENT_VALUE_OCTO: return 'o';
        case ELEMENT_VALUE_NONARY: return 'n';
            case ELEMENT_VALUE_ENNA: return 'e';
        case ELEMENT_VALUE_DECIMAL: return 'd';
            case ELEMENT_VALUE_GESIMAL: return 'g';
        case ELEMENT_VALUE_ELEVENARY: return 'e';
            case ELEMENT_VALUE_LEVA: return 'l';
        case ELEMENT_VALUE_DOZENAL: return 'd';
            case ELEMENT_VALUE_DOZA: return 'd';
        case ELEMENT_VALUE_BAKERS_DOZENAL: return 'b';
            case ELEMENT_VALUE_KERS_DOZENAL: return 'k';
        //
        case ELEMENT_VALUE_HEX: return 'h';
            case ELEMENT_VALUE_TESSER: return 't';
        case ELEMENT_VALUE_SUBOPTIMAL: return 's';
            case ELEMENT_VALUE_MAL: return 'm';
        //
        case ELEMENT_VALUE_VIGESIMAL: return 'v';
            case ELEMENT_VALUE_ICOSI: return 'i';
        //
        case ELEMENT_VALUE_NIFTIMAL: return 'n';
            case ELEMENT_VALUE_FETA: return 'f';
        //
        case ELEMENT_VALUE_CENTESIMAL: return 'c';
            case ELEMENT_VALUE_HECTO: return 'h';
        //
        case ELEMENT_VALUE_NARY: return 'n';
            case ELEMENT_VALUE_ARY: return 'a';
        case ELEMENT_VALUE_IMAL: return 'i';
            case ELEMENT_VALUE_AL: return 'a';
        //
        default:
            return '\0';
    }

    return '\0';
}


enum ELEMENT_VALUE pair_favor(enum ELEMENT_VALUE first, enum ELEMENT_VALUE last) {
    // io = io, ie = ie, ii = i, iu = i
    // ao = o,  ae = e,  ai = i, au = u
    // oo = o,  oe = e,  oi = i, ou = u
    char f = element_final_char(first);
    char l = element_begin_char(last);

    //printf("Pair: %s %s %c%c\n", element_as_string(first), element_as_string(last), f, l);

    if (f == 'i') {
        if (l == 'i' || l == 'u') {
            return ELEMENT_VALUE_PREFER_FIRST;
        } else {
            return ELEMENT_VALUE_PREFER_NEITHER;
        }
    } else if (f == 'a') {
        if (l == 'o' || l == 'e' || l == 'i' || l == 'u') {
            return ELEMENT_VALUE_PREFER_LAST;
        } else {
            return ELEMENT_VALUE_PREFER_NEITHER;
        }
    } else if (f == 'o') {
        if (l == 'o' || l == 'e' || l == 'i' || l == 'u') {
            return ELEMENT_VALUE_PREFER_LAST;
        } else {
            return ELEMENT_VALUE_PREFER_NEITHER;
        }
    } else {
        return ELEMENT_VALUE_PREFER_NEITHER;
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
    size_t count = el->element_count * 4;
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

    construct(el, 5758, 1, 0);

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


int main() {
    test_construct();
}
