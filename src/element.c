#include "element.h"

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


#define OPTION(n, final, medial) case (n): return (is_final) ? (final) : (medial)
#define BARE(n, bare, medial) case (n): return (is_bare) ? (bare) : (medial)

enum ELEMENT_VALUE base_as_element(int n, int is_final, int is_bare) {
    switch (n) {
        OPTION(0,   ELEMENT_VALUE_NULLARY,      ELEMENT_VALUE_INVALID);
        OPTION(1,   ELEMENT_VALUE_UNARY,        ELEMENT_VALUE_INVALID);
        OPTION(2,   ELEMENT_VALUE_BINARY,       ELEMENT_VALUE_BI);
        OPTION(3,   ELEMENT_VALUE_TRINARY,      ELEMENT_VALUE_TRI);
        OPTION(4,   ELEMENT_VALUE_QUATERNARY,   ELEMENT_VALUE_TETRA);
        OPTION(5,   ELEMENT_VALUE_QUINARY,      ELEMENT_VALUE_PENTA);
        OPTION(6,   ELEMENT_VALUE_SEXIMAL,      ELEMENT_VALUE_HEXA);
        OPTION(7,   ELEMENT_VALUE_SEPTIMAL,     ELEMENT_VALUE_HEPTA);
        OPTION(8,   ELEMENT_VALUE_OCTAL,        ELEMENT_VALUE_OCTO);
        OPTION(9,   ELEMENT_VALUE_NONARY,       ELEMENT_VALUE_ENNA);
        BARE  (10,  ELEMENT_VALUE_DECIMAL,      ELEMENT_VALUE_GESIMAL);
        OPTION(11,  ELEMENT_VALUE_ELEVENARY,    ELEMENT_VALUE_LEVA);
        OPTION(12,  ELEMENT_VALUE_DOZENAL,      ELEMENT_VALUE_DOZA);
        BARE  (13,  ELEMENT_VALUE_BAKERS_DOZENAL, ELEMENT_VALUE_KERS_DOZENAL);
        //
        OPTION(16,  ELEMENT_VALUE_HEX,          ELEMENT_VALUE_TESSER);
        OPTION(17,  ELEMENT_VALUE_SUBOPTIMAL,   ELEMENT_VALUE_MAL);
        //
        OPTION(20,  ELEMENT_VALUE_VIGESIMAL,    ELEMENT_VALUE_ICOSI);
        //
        OPTION(36,  ELEMENT_VALUE_NIFTIMAL,     ELEMENT_VALUE_FETA);
        //
        OPTION(100, ELEMENT_VALUE_CENTESIMAL,   ELEMENT_VALUE_HECTO);
        //
        default: return ELEMENT_VALUE_INVALID;
    }
}

#undef OPTION
#undef BARE


#define RET(match, value) case (match): return (value)

const char *element_as_string(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(ELEMENT_VALUE_INVALID, "invalid");
        //
        RET(ELEMENT_VALUE_NEGA, "nega");
        RET(ELEMENT_VALUE_VOT, "vot");
        //
        RET(ELEMENT_VALUE_NULLARY, "nullary");
        RET(ELEMENT_VALUE_UNARY, "unary");
            RET(ELEMENT_VALUE_UN, "un");
            RET(ELEMENT_VALUE_HEN, "hen");
            RET(ELEMENT_VALUE_SNA, "sna");
        RET(ELEMENT_VALUE_BINARY, "binary");
            RET(ELEMENT_VALUE_BI, "bi");
        RET(ELEMENT_VALUE_TRINARY, "trinary");
            RET(ELEMENT_VALUE_TRI, "tri");
        RET(ELEMENT_VALUE_QUATERNARY, "quaternary");
            RET(ELEMENT_VALUE_TETRA, "tetra");
        RET(ELEMENT_VALUE_QUINARY, "quinary");
            RET(ELEMENT_VALUE_PENTA, "penta");
        RET(ELEMENT_VALUE_SEXIMAL, "seximal");
            RET(ELEMENT_VALUE_HEXA, "hexa");
        RET(ELEMENT_VALUE_SEPTIMAL, "septimal");
            RET(ELEMENT_VALUE_HEPTA, "hepta");
        RET(ELEMENT_VALUE_OCTAL, "octal");
            RET(ELEMENT_VALUE_OCTO, "octo");
        RET(ELEMENT_VALUE_NONARY, "nonary");
            RET(ELEMENT_VALUE_ENNA, "enna");
        RET(ELEMENT_VALUE_DECIMAL, "decimal");
            RET(ELEMENT_VALUE_GESIMAL, "gesimal");
        RET(ELEMENT_VALUE_ELEVENARY, "elevenary");
            RET(ELEMENT_VALUE_LEVA, "leva");
        RET(ELEMENT_VALUE_DOZENAL, "dozenal");
            RET(ELEMENT_VALUE_DOZA, "doza");
        RET(ELEMENT_VALUE_BAKERS_DOZENAL, "baker's dozenal");
            RET(ELEMENT_VALUE_KERS_DOZENAL, "ker's dozenal");
        //
        RET(ELEMENT_VALUE_HEX, "hex");
            RET(ELEMENT_VALUE_TESSER, "tesser");
        RET(ELEMENT_VALUE_SUBOPTIMAL, "suboptimal");
            RET(ELEMENT_VALUE_MAL, "mal");
        //
        RET(ELEMENT_VALUE_VIGESIMAL, "vigesimal");
            RET(ELEMENT_VALUE_ICOSI, "icosi");
        //
        RET(ELEMENT_VALUE_NIFTIMAL, "niftimal");
            RET(ELEMENT_VALUE_FETA, "feta");
        //
        RET(ELEMENT_VALUE_CENTESIMAL, "centesimal");
            RET(ELEMENT_VALUE_HECTO, "hecto");
        //
        RET(ELEMENT_VALUE_NARY, "nary");
            RET(ELEMENT_VALUE_ARY, "ary");
        RET(ELEMENT_VALUE_IMAL, "imal");
            RET(ELEMENT_VALUE_AL, "al");
        //
        RET(ELEMENT_VALUE_PREFER_NEITHER, "0");
        RET(ELEMENT_VALUE_PREFER_FIRST, "<-");
        RET(ELEMENT_VALUE_PREFER_LAST, "->");
    }

    return "";
}


char element_final_char(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(ELEMENT_VALUE_INVALID, 'd');
        //
        RET(ELEMENT_VALUE_NEGA, 'a');
        RET(ELEMENT_VALUE_VOT, 't');
        //
        RET(ELEMENT_VALUE_NULLARY, 'y');
        RET(ELEMENT_VALUE_UNARY, 'y');
            RET(ELEMENT_VALUE_UN, 'n');
            RET(ELEMENT_VALUE_HEN, 'n');
            RET(ELEMENT_VALUE_SNA, 'a');
        RET(ELEMENT_VALUE_BINARY, 'y');
            RET(ELEMENT_VALUE_BI, 'i');
        RET(ELEMENT_VALUE_TRINARY, 'y');
            RET(ELEMENT_VALUE_TRI, 'i');
        RET(ELEMENT_VALUE_QUATERNARY, 'y');
            RET(ELEMENT_VALUE_TETRA, 'a');
        RET(ELEMENT_VALUE_QUINARY, 'y');
            RET(ELEMENT_VALUE_PENTA, 'a');
        RET(ELEMENT_VALUE_SEXIMAL, 'l');
            RET(ELEMENT_VALUE_HEXA, 'a');
        RET(ELEMENT_VALUE_SEPTIMAL, 'l');
            RET(ELEMENT_VALUE_HEPTA, 'a');
        RET(ELEMENT_VALUE_OCTAL, 'l');
            RET(ELEMENT_VALUE_OCTO, 'o');
        RET(ELEMENT_VALUE_NONARY, 'y');
            RET(ELEMENT_VALUE_ENNA, 'a');
        RET(ELEMENT_VALUE_DECIMAL, 'l');
            RET(ELEMENT_VALUE_GESIMAL, 'l');
        RET(ELEMENT_VALUE_ELEVENARY, 'y');
            RET(ELEMENT_VALUE_LEVA, 'a');
        RET(ELEMENT_VALUE_DOZENAL, 'l');
            RET(ELEMENT_VALUE_DOZA, 'a');
        RET(ELEMENT_VALUE_BAKERS_DOZENAL, 'l');
            RET(ELEMENT_VALUE_KERS_DOZENAL, 'l');
        //
        RET(ELEMENT_VALUE_HEX, 'x');
            RET(ELEMENT_VALUE_TESSER, 'r');
        RET(ELEMENT_VALUE_SUBOPTIMAL, 'l');
            RET(ELEMENT_VALUE_MAL, 'l');
        //
        RET(ELEMENT_VALUE_VIGESIMAL, 'l');
            RET(ELEMENT_VALUE_ICOSI, 'i');
        //
        RET(ELEMENT_VALUE_NIFTIMAL, 'l');
            RET(ELEMENT_VALUE_FETA, 'a');
        //
        RET(ELEMENT_VALUE_CENTESIMAL, 'l');
            RET(ELEMENT_VALUE_HECTO, 'o');
        //
        RET(ELEMENT_VALUE_NARY, 'y');
            RET(ELEMENT_VALUE_ARY, 'y');
        RET(ELEMENT_VALUE_IMAL, 'l');
            RET(ELEMENT_VALUE_AL, 'l');
        //
        default: return '\0';
    }

    return '\0';
}


char element_begin_char(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(ELEMENT_VALUE_INVALID, 'i');
        //
        RET(ELEMENT_VALUE_NEGA, 'n');
        RET(ELEMENT_VALUE_VOT, 'v');
        //
        RET(ELEMENT_VALUE_NULLARY, 'n');
        RET(ELEMENT_VALUE_UNARY, 'u');
            RET(ELEMENT_VALUE_UN, 'u');
            RET(ELEMENT_VALUE_HEN, 'h');
            RET(ELEMENT_VALUE_SNA, 's');
        RET(ELEMENT_VALUE_BINARY, 'b');
            RET(ELEMENT_VALUE_BI, 'b');
        RET(ELEMENT_VALUE_TRINARY, 't');
            RET(ELEMENT_VALUE_TRI, 't');
        RET(ELEMENT_VALUE_QUATERNARY, 'q');
            RET(ELEMENT_VALUE_TETRA, 't');
        RET(ELEMENT_VALUE_QUINARY, 'q');
            RET(ELEMENT_VALUE_PENTA, 'p');
        RET(ELEMENT_VALUE_SEXIMAL, 's');
            RET(ELEMENT_VALUE_HEXA, 'h');
        RET(ELEMENT_VALUE_SEPTIMAL, 's');
            RET(ELEMENT_VALUE_HEPTA, 'h');
        RET(ELEMENT_VALUE_OCTAL, 'o');
            RET(ELEMENT_VALUE_OCTO, 'o');
        RET(ELEMENT_VALUE_NONARY, 'n');
            RET(ELEMENT_VALUE_ENNA, 'e');
        RET(ELEMENT_VALUE_DECIMAL, 'd');
            RET(ELEMENT_VALUE_GESIMAL, 'g');
        RET(ELEMENT_VALUE_ELEVENARY, 'e');
            RET(ELEMENT_VALUE_LEVA, 'l');
        RET(ELEMENT_VALUE_DOZENAL, 'd');
            RET(ELEMENT_VALUE_DOZA, 'd');
        RET(ELEMENT_VALUE_BAKERS_DOZENAL, 'b');
            RET(ELEMENT_VALUE_KERS_DOZENAL, 'k');
        //
        RET(ELEMENT_VALUE_HEX, 'h');
            RET(ELEMENT_VALUE_TESSER, 't');
        RET(ELEMENT_VALUE_SUBOPTIMAL, 's');
            RET(ELEMENT_VALUE_MAL, 'm');
        //
        RET(ELEMENT_VALUE_VIGESIMAL, 'v');
            RET(ELEMENT_VALUE_ICOSI, 'i');
        //
        RET(ELEMENT_VALUE_NIFTIMAL, 'n');
            RET(ELEMENT_VALUE_FETA, 'f');
        //
        RET(ELEMENT_VALUE_CENTESIMAL, 'c');
            RET(ELEMENT_VALUE_HECTO, 'h');
        //
        RET(ELEMENT_VALUE_NARY, 'n');
            RET(ELEMENT_VALUE_ARY, 'a');
        RET(ELEMENT_VALUE_IMAL, 'i');
            RET(ELEMENT_VALUE_AL, 'a');
        //
        default: return '\0';
    }

    return '\0';
}

#undef RET

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
    } else if (f == 'a' || f == 'o') {
        if (l == 'o' || l == 'e' || l == 'i' || l == 'u') {
            return ELEMENT_VALUE_PREFER_LAST;
        } else {
            return ELEMENT_VALUE_PREFER_NEITHER;
        }
    } else {
        return ELEMENT_VALUE_PREFER_NEITHER;
    }
}
