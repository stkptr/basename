#ifndef ELEMENT_H
#define ELEMENT_H

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

    // Vowel preferences
    ELEMENT_VALUE_PREFER_NEITHER = 50,
    ELEMENT_VALUE_PREFER_FIRST = 51,
    ELEMENT_VALUE_PREFER_LAST = 52
};

// Returns 1 if the value is an inter-element vowel preference
int element_value_is_preference(enum ELEMENT_VALUE ev);

// Returns the constant value for a base case
//  n is the base case base
//  is_final denotes if it is the final element of the name
//  is_bare denotes if it has no prefixes or suffixes
enum ELEMENT_VALUE base_as_element(int n, int is_final, int is_bare);

// Returns the string value for an element value
const char *element_as_string(enum ELEMENT_VALUE ev);

// Returns the last character in the string representation of ev
char element_final_char(enum ELEMENT_VALUE ev);

// Returns the first character in the string representation of ev
char element_begin_char(enum ELEMENT_VALUE ev);

// Returns the favor direction between first and last
// For example
// pair_favor(ELEMENT_VALUE_OCTO, ELEMENT_VALUE_ICOSI) -> ELEMENT_VALUE_PREFER_LAST
enum ELEMENT_VALUE pair_favor(enum ELEMENT_VALUE first, enum ELEMENT_VALUE last);

#endif
