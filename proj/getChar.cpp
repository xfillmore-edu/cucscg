#include "twobjects.hpp"

// condtiional ternary operator usage
// (cond) ? true : false

unsigned char getChar(bool figkey, bool capkey, unsigned int id)
{
    if (id == 0x00001f) return 2; // CAP key
    if (id == 0x000020) return 1; // FIG key

    unsigned char selChar = 0; // selected character
    // figkey ? topsym : (capkey ? upper : lower);

    switch (id)
    {
        case 0x000001: // a, A, at
            selChar = figkey ? 64 : ( capkey ? 65 : 97 );
            break;
        case 0x000002: // b, B, double quote
            selChar = figkey ? 34 : ( capkey ? 66 : 98 );
            break;
        case 0x000003: // c, C, tilde
            selChar = figkey ? 126 : ( capkey ? 67 : 99 );
            break;
        case 0x000004: // d, D, percent
            selChar = figkey ? 37 : ( capkey ? 68 : 100 );
            break;
        case 0x000005: // e, E, 3
            selChar = figkey ? 51 : ( capkey ? 69 : 101 );
            break;
        case 0x000006: // f, F, ampersand
            selChar = figkey ? 38 : ( capkey ? 70 : 102 );
            break;
        case 0x000007: // g, G, underscore
            selChar = figkey ? 95 : ( capkey ? 71 : 103 );
            break;
        case 0x000008: // h, H, asterisk
            selChar = figkey ? 42 : ( capkey ? 72 : 104 );
            break;
        case 0x000009: // i, I, 8
            selChar = figkey ? 56 : ( capkey ? 73 : 105 );
            break;
        case 0x00000a: // j, J, forward slash
            selChar = figkey ? 47 : ( capkey ? 74 : 106 );
            break;
        case 0x00000b: // k, K, equals
            selChar = figkey ? 61 : ( capkey ? 75 : 107 );
            break;
        case 0x00000c: // l, L, pound
            selChar = figkey ? 35 : ( capkey ? 76 : 108 );
            break;
        case 0x00000d: // m, M, semicolon
            selChar = figkey ? 59 : ( capkey ? 77 : 109 );
            break;
        case 0x00000e: // n, N, colon
            selChar = figkey ? 58 : ( capkey ? 78 : 110 );
            break;
        case 0x00000f: // o, O, 9
            selChar = figkey ? 57 : ( capkey ? 79 : 111 );
            break;
        case 0x000010: // p, P, 0
            selChar = figkey ? 48 : ( capkey ? 80 : 112 );
            break;
        case 0x000011: // q, Q, 1
            selChar = figkey ? 49 : ( capkey ? 81 : 113 );
            break;
        case 0x000012: // r, R, 4
            selChar = figkey ? 52 : ( capkey ? 82 : 114 );
            break;
        case 0x000013: // s, S, dollar
            selChar = figkey ? 36 : ( capkey ? 83 : 115 );
            break;
        case 0x000014: // t, T, 5
            selChar = figkey ? 53 : ( capkey ? 84 : 116 );
            break;
        case 0x000015: // u, U, 7
            selChar = figkey ? 55 : ( capkey ? 85 : 117 );
            break;
        case 0x000016: // v, V, single quote
            selChar = figkey ? 39 : ( capkey ? 86 : 118 );
            break;
        case 0x000017: // w, W, 2
            selChar = figkey ? 50 : ( capkey ? 87 : 119 );
            break;
        case 0x000018: // x, X, close parenthesis
            selChar = figkey ? 41 : ( capkey ? 88 : 120 );
            break;
        case 0x000019: // y, Y, 6
            selChar = figkey ? 54 : ( capkey ? 89 : 121 );
            break;
        case 0x00001a: // z, Z, open parenthesis
            selChar = figkey ? 40 : ( capkey ? 90 : 122 );
            break;
        case 0x00001b: // question mark, back slash
            selChar = figkey ? 92 : 63;
            break;
        case 0x00001c: // comma, left angle bracket
            selChar = figkey ? 60 : 44;
            break;
        case 0x00001d: // period, right angle bracket
            selChar = figkey ? 62 : 46;
            break;
        case 0x00001e: // minus, plus
            selChar = figkey ? 43 : 45;
            break;
        case 0x000021: // SPACE
            selChar = 32;
            break;
    }
    return selChar; // returns 0 if id doesn't match
}