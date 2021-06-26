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
#define TRIPLE(n, bare, medial, final) case (n): return (is_bare) ? (bare) : ((is_final) ? (final) : (medial))

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
        TRIPLE(10,  ELEMENT_VALUE_DECIMAL,      ELEMENT_VALUE_DECA, ELEMENT_VALUE_GESIMAL);
        OPTION(11,  ELEMENT_VALUE_ELEVENARY,    ELEMENT_VALUE_LEVA);
        OPTION(12,  ELEMENT_VALUE_DOZENAL,      ELEMENT_VALUE_DOZA);
        TRIPLE(13,  ELEMENT_VALUE_BAKERS_DOZENAL, ELEMENT_VALUE_BAKER, ELEMENT_VALUE_KERS_DOZENAL);
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
#undef TRIPLE


#define RET(match, value) case (ELEMENT_VALUE_ ## match): return (value)

const char *element_as_string(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(INVALID, "invalid");
        //
        RET(NEGA, "nega");
        RET(VOT, "vot");
        //
        RET(NULLARY, "nullary");
        RET(UNARY, "unary");
            RET(UN, "un");
            RET(HEN, "hen");
            RET(SNA, "sna");
        RET(BINARY, "binary");
            RET(BI, "bi");
        RET(TRINARY, "trinary");
            RET(TRI, "tri");
        RET(QUATERNARY, "quaternary");
            RET(TETRA, "tetra");
        RET(QUINARY, "quinary");
            RET(PENTA, "penta");
        RET(SEXIMAL, "seximal");
            RET(HEXA, "hexa");
        RET(SEPTIMAL, "septimal");
            RET(HEPTA, "hepta");
        RET(OCTAL, "octal");
            RET(OCTO, "octo");
        RET(NONARY, "nonary");
            RET(ENNA, "enna");
        RET(DECIMAL, "decimal");
            RET(DECA, "deca");
            RET(GESIMAL, "gesimal");
        RET(ELEVENARY, "elevenary");
            RET(LEVA, "leva");
        RET(DOZENAL, "dozenal");
            RET(DOZA, "doza");
        RET(BAKERS_DOZENAL, "baker's dozenal");
            RET(BAKER, "baker");
            RET(KERS_DOZENAL, "ker's dozenal");
        //
        RET(HEX, "hex");
            RET(TESSER, "tesser");
        RET(SUBOPTIMAL, "suboptimal");
            RET(MAL, "mal");
        //
        RET(VIGESIMAL, "vigesimal");
            RET(ICOSI, "icosi");
        //
        RET(NIFTIMAL, "niftimal");
            RET(FETA, "feta");
        //
        RET(CENTESIMAL, "centesimal");
            RET(HECTO, "hecto");
        //
        RET(NARY, "nary");
            RET(ARY, "ary");
        RET(IMAL, "imal");
            RET(AL, "al");
        //
        RET(PREFER_NEITHER, "0");
        RET(PREFER_FIRST, "<-");
        RET(PREFER_LAST, "->");
    }

    return "";
}


char element_final_char(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(INVALID, 'd');
        //
        RET(NEGA, 'a');
        RET(VOT, 't');
        //
        RET(NULLARY, 'y');
        RET(UNARY, 'y');        RET(UN, 'n');
            RET(HEN, 'n');
            RET(SNA, 'a');
        RET(BINARY, 'y');       RET(BI, 'i');
        RET(TRINARY, 'y');      RET(TRI, 'i');
        RET(QUATERNARY, 'y');   RET(TETRA, 'a');
        RET(QUINARY, 'y');      RET(PENTA, 'a');
        RET(SEXIMAL, 'l');      RET(HEXA, 'a');
        RET(SEPTIMAL, 'l');     RET(HEPTA, 'a');
        RET(OCTAL, 'l');        RET(OCTO, 'o');
        RET(NONARY, 'y');       RET(ENNA, 'a');
        RET(DECIMAL, 'l');
            RET(DECA, 'a');
            RET(GESIMAL, 'l');
        RET(ELEVENARY, 'y');    RET(LEVA, 'a');
        RET(DOZENAL, 'l');      RET(DOZA, 'a');
        RET(BAKERS_DOZENAL, 'l');
            RET(BAKER, 'r');
            RET(KERS_DOZENAL, 'l');
        //
        RET(HEX, 'x');          RET(TESSER, 'r');
        RET(SUBOPTIMAL, 'l');   RET(MAL, 'l');
        //
        RET(VIGESIMAL, 'l');    RET(ICOSI, 'i');
        //
        RET(NIFTIMAL, 'l');     RET(FETA, 'a');
        //
        RET(CENTESIMAL, 'l');   RET(HECTO, 'o');
        //
        RET(NARY, 'y');         RET(ARY, 'y');
        RET(IMAL, 'l');         RET(AL, 'l');
        //
        default: return '\0';
    }

    return '\0';
}


char element_begin_char(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(INVALID, 'i');
        //
        RET(NEGA, 'n');
        RET(VOT, 'v');
        //
        RET(NULLARY, 'n');
        RET(UNARY, 'u');        RET(UN, 'u');
            RET(HEN, 'h');
            RET(SNA, 's');
        RET(BINARY, 'b');       RET(BI, 'b');
        RET(TRINARY, 't');      RET(TRI, 't');
        RET(QUATERNARY, 'q');   RET(TETRA, 't');
        RET(QUINARY, 'q');      RET(PENTA, 'p');
        RET(SEXIMAL, 's');      RET(HEXA, 'h');
        RET(SEPTIMAL, 's');     RET(HEPTA, 'h');
        RET(OCTAL, 'o');        RET(OCTO, 'o');
        RET(NONARY, 'n');       RET(ENNA, 'e');
        RET(DECIMAL, 'd');
            RET(DECA, 'a');
            RET(GESIMAL, 'g');
        RET(ELEVENARY, 'e');    RET(LEVA, 'l');
        RET(DOZENAL, 'd');      RET(DOZA, 'd');
        RET(BAKERS_DOZENAL, 'b');
            RET(BAKER, 'b');
            RET(KERS_DOZENAL, 'k');
        //
        RET(HEX, 'h');          RET(TESSER, 't');
        RET(SUBOPTIMAL, 's');   RET(MAL, 'm');
        //
        RET(VIGESIMAL, 'v');    RET(ICOSI, 'i');
        //
        RET(NIFTIMAL, 'n');     RET(FETA, 'f');
        //
        RET(CENTESIMAL, 'c');   RET(HECTO, 'h');
        //
        RET(NARY, 'n');         RET(ARY, 'a');
        RET(IMAL, 'i');         RET(AL, 'a');
        //
        default: return '\0';
    }

    return '\0';
}

int element_length(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(INVALID, 7);
        //
        RET(NEGA, 4);
        RET(VOT, 3);
        //
        RET(NULLARY, 7);
        RET(UNARY, 5);          RET(UN, 2);
            RET(HEN, 3);
            RET(SNA, 3);
        RET(BINARY, 6);         RET(BI, 2);
        RET(TRINARY, 7);        RET(TRI, 3);
        RET(QUATERNARY, 10);    RET(TETRA, 5);
        RET(QUINARY, 7);        RET(PENTA, 5);
        RET(SEXIMAL, 7);        RET(HEXA, 4);
        RET(SEPTIMAL, 8);       RET(HEPTA, 5);
        RET(OCTAL, 5);          RET(OCTO, 4);
        RET(NONARY, 6);         RET(ENNA, 4);
        RET(DECIMAL, 7);
            RET(DECA, 4);
            RET(GESIMAL, 7);
        RET(ELEVENARY, 9);      RET(LEVA, 4);
        RET(DOZENAL, 7);        RET(DOZA, 4);
        RET(BAKERS_DOZENAL, 15);
            RET(BAKER, 5);
            RET(KERS_DOZENAL, 13);
        //
        RET(HEX, 3);            RET(TESSER, 6);
        RET(SUBOPTIMAL, 10);    RET(MAL, 3);
        //
        RET(VIGESIMAL, 9);      RET(ICOSI, 5);
        //
        RET(NIFTIMAL, 8);       RET(FETA, 4);
        //
        RET(CENTESIMAL, 10);    RET(HECTO, 5);
        //
        RET(NARY, 4);           RET(ARY, 3);
        RET(IMAL, 4);           RET(AL, 2);
        //
        default: return '\0';
    }

    return '\0';
}

char short_code(enum ELEMENT_VALUE ev) {
    switch (ev) {
        RET(NEGA, '-');
        RET(VOT, '/');
        //
        RET(NULLARY, '0');
        RET(UNARY, '1');        RET(UN, '+');
            RET(HEN, '(');
            RET(SNA, ')');
        RET(BINARY, 'b');       RET(BI, '2');
        RET(TRINARY, 't');      RET(TRI, '3');
        RET(QUATERNARY, 'q');   RET(TETRA, '4');
        RET(QUINARY, 'Q');      RET(PENTA, '5');
        RET(SEXIMAL, 's');      RET(HEXA, '6');
        RET(SEPTIMAL, 'S');     RET(HEPTA, '7');
        RET(OCTAL, 'o');        RET(OCTO, '8');
        RET(NONARY, 'n');       RET(ENNA, '9');
        RET(DECIMAL, 'd');      RET(DECA, 'A');
            RET(GESIMAL, 'g');
        RET(ELEVENARY, 'e');    RET(LEVA, 'B');
        RET(DOZENAL, 'z');      RET(DOZA, 'C');
        RET(BAKERS_DOZENAL, 'k'); RET(BAKER, 'D');
            RET(KERS_DOZENAL, 'Z');
        //
        RET(HEX, 'h');          RET(TESSER, 'F');
        RET(SUBOPTIMAL, 'm');   RET(MAL, 'M');
        //
        RET(VIGESIMAL, 'v');    RET(ICOSI, 'I');
        //
        RET(NIFTIMAL, 'f');     RET(FETA, 'T');
        //
        RET(CENTESIMAL, 'c');   RET(HECTO, 'Y');
        default: return '\0';
    }
}

#undef RET

enum ELEMENT_VALUE pair_favor(enum ELEMENT_VALUE first, enum ELEMENT_VALUE last) {
    // io = io, ie = ie, ii = i, iu = i
    // ao = o,  ae = e,  ai = i, au = u
    // oo = o,  oe = e,  oi = i, ou = u
    char f = element_final_char(first);
    char l = element_begin_char(last);

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
