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
