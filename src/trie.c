#include <stddef.h>
#include <ctype.h>

#include "trie.h"
#include "element.h"
#include "elist.h"

char upper(char ch) {
    if (islower(ch)) {
        return ch - 0x20;
    }

    return ch;
}

char get_next_c(const char *string, int *index) {
    for (;;) {
        char ch = upper(string[(*index)++]);
        switch (ch) {
            case '\0':
                (*index)--; // adjust so that string[index] == '\0'
                return '\0';
            case 'A':
            case 'E':
            case 'O':
            case 'U':
                break;
            case 'I':
                if (*index > 1 && string[*index - 2] == 'b') {
                    return ch;
                }
                break;
            default:
                return ch;
        }
    }
}

char peek_next_c(const char *string, int *index) {
    char c = get_next_c(string, index);
    (*index)--;
    return c;
}

#define consume(x, y) get_next_c(x, y)

int expect(const char *string, int *index, char expected) {
    char c = get_next_c(string, index);
    return c == expected;
}

#define POP() get_next_c(string, index)
#define PEEK() peek_next_c(string, index)
#define EXPECT(c) expect(string, index, c)
#define ACCEPT(v) return ELEMENT_VALUE_ ## v
#define PACCEPT(v) POP(); ACCEPT(v)
#define ERROR() ACCEPT(INVALID)
#define ECHAIN_NP(e, a) if (e) {ACCEPT(a);} else {ERROR();}
#define ECHAIN(e, a) POP(); ECHAIN_NP(e, a)

// The hardcoded trie
enum ELEMENT_VALUE parse_element(const char *string, int *index) {
    switch (POP()) {
    // B, binary, bi, baker's dozenal, baker
    case 'B':
        switch (PEEK()) {
        case 'I':
            POP(); // consume peeked
            switch (PEEK()) {
            case 'N': // BINRY
                ECHAIN(EXPECT('R') && EXPECT('Y'),
                    BINARY);
            default: // BI
                ACCEPT(BI);
            }
        case 'K':
            POP();
            if (EXPECT('R')) {
                switch (PEEK()) {
                case 'S':
                    ECHAIN(EXPECT('D') && EXPECT('Z')
                           && EXPECT('N') && EXPECT('L'),
                        BAKERS_DOZENAL);
                default:
                    ACCEPT(BAKER);
                }
            } else {
                ERROR();
            }
        default:
            ACCEPT(BI);
        }
    // C, octal, octo, icosi, centesimal
    case 'C':
        switch (POP()) {
        case 'T':
            switch(PEEK()) {
            case 'L':
                PACCEPT(OCTAL);
            default:
                ACCEPT(OCTO);
            }
        case 'S':
            ACCEPT(ICOSI);
        case 'N':
            ECHAIN_NP(EXPECT('T') && EXPECT('S')
                      && EXPECT('M') && EXPECT('L'),
                CENTESIMAL)
        }
    // D, decimal, deca, dozenal, doza
    case 'D':
        switch (POP()) {
        case 'C':
            switch (PEEK()) {
            case 'M':
                ECHAIN(EXPECT('L'), DECIMAL);
            default:
                ACCEPT(DECA);
            }
        case 'Z':
            switch (PEEK()) {
            case 'N':
                ECHAIN(EXPECT('L'), DOZENAL);
            default:
                ACCEPT(DOZA);
            }
        default:
            ERROR();
        }
    // F, feta
    case 'F':
        ECHAIN_NP(EXPECT('T'), FETA);
    // G, gesimal
    case 'G':
        ECHAIN_NP(EXPECT('S') && EXPECT('M')
                  && EXPECT('L'),
            GESIMAL);
    // H, hecto, hen, hepta, hex/hexa
    case 'H':
        switch (POP()) {
        case 'C':
            ECHAIN_NP(EXPECT('T'), HECTO);
        case 'N':
            ACCEPT(HEN);
        case 'P':
            ECHAIN_NP(EXPECT('T'), HEPTA);
        case 'X':
            if (PEEK() == '\0') // final
                ACCEPT(HEX);
            else
                ACCEPT(HEXA);
        default:
            ERROR();
        }
    // K, ker's dozenal
    case 'K':
        ECHAIN_NP(EXPECT('R') && EXPECT('S')
                  && EXPECT('D') && EXPECT('Z')
                  && EXPECT('N') && EXPECT('L'),
            KERS_DOZENAL);
    // L, elevenary, leva
    case 'L':
        if (POP() == 'V') {
            switch (PEEK()) {
            case 'N':
                ECHAIN(EXPECT('R'), ELEVENARY);
            default:
                ACCEPT(LEVA);
            }
        } else {
            ERROR();
        }
    // M, mal
    case 'M':
        ECHAIN_NP(EXPECT('L'), MAL);
    // N, niftimal, nega, nullary, nonary, enna, unary, un
    case 'N':
        switch (PEEK()) {
        case 'F':
            ECHAIN(EXPECT('T') && EXPECT('M')
                   && EXPECT('L'),
                NIFTIMAL);
        case 'G':
            // check if at beginning
            // 0 is true beginning, after it is checked it is 1
            // so N in nega would be 1
            // the G would then be 2
            // since we are at G, check if 2
            if (*index == 2)
                PACCEPT(NEGA);
        case 'L':
            ECHAIN(EXPECT('L') && EXPECT('R')
                   && EXPECT('Y'),
                NULLARY);
        case 'N':
            POP();
            switch (PEEK()) {
            case 'R':
                ECHAIN(EXPECT('Y'), NONARY);
            default:
                ACCEPT(ENNA);
            }
        case 'R':
            ECHAIN(EXPECT('Y'), UNARY);
        default:
            ACCEPT(UN);
        }
    // P, penta
    case 'P':
        ECHAIN_NP(EXPECT('N') && EXPECT('T'), PENTA);
    // Q, quinary, quaternary
    case 'Q':
        switch (POP()) {
        case 'N':
            ECHAIN_NP(EXPECT('R') && EXPECT('Y'), QUINARY);
        case 'T':
            ECHAIN_NP(EXPECT('R') && EXPECT('N')
                      && EXPECT('R') && EXPECT('Y'),
                QUATERNARY);
        default:
            ERROR();
        }
    // R, er's dozenal
    case 'R':
        ECHAIN_NP(EXPECT('S') && EXPECT('D')
                  && EXPECT('Z') && EXPECT('N')
                  && EXPECT('L'),
            KERS_DOZENAL);
    // S, suboptimal, sna, septimal, seximal, sex
    case 'S':
        switch (POP()) {
        case 'B':
            ECHAIN_NP(EXPECT('P') && EXPECT('T')
                      && EXPECT('M') && EXPECT('L'),
                SUBOPTIMAL);
        case 'N':
            ACCEPT(SNA);
        case 'P':
            ECHAIN_NP(EXPECT('T') && EXPECT('M')
                      && EXPECT('L'),
                SEPTIMAL);
        case 'X':
            switch (PEEK()) {
            case 'M':
                ECHAIN(EXPECT('L'), SEXIMAL);
            default:
                ACCEPT(HEXA);
            }
        default:
            ERROR();
        }
    // T, trinary, tri, tesser, tetra
    case 'T':
        switch (POP()) {
        case 'R':
            switch (PEEK()) {
            case 'N':
                ECHAIN(EXPECT('R') && EXPECT('Y'), TRINARY);
            default:
                ACCEPT(TRI);
            }
        case 'S':
            ECHAIN_NP(EXPECT('S') && EXPECT('R'), TESSER);
        case 'T':
            ECHAIN_NP(EXPECT('R'), TETRA);
        default:
            ERROR();
        }
    // V, vigesimal, vot
    case 'V':
        switch (POP()) {
        case 'G':
            ECHAIN_NP(EXPECT('S') && EXPECT('M')
                      && EXPECT('L'),
                VIGESIMAL);
        case 'T':
            ACCEPT(VOT);
        default:
            ERROR();
        }
    default:
        ERROR();
    }
}


struct element_list_s *elist_from_base_name(const char *name) {
    int index = 0;
    struct element_list_s *el = elist_new();
    enum ELEMENT_VALUE ev;

    while ((ev = parse_element(name, &index)) != ELEMENT_VALUE_INVALID) {
        elist_append(el, ev);
    }

    // still stuff left to parse, the string must have been nonconformant
    if (name[index] != '\0') {
        elist_free(el);
        return NULL;
    }

    return el;
}
