#include "twobjects.hpp"

// condtiional ternary operator usage
// (cond) ? true : false

unsigned char getChar(bool figkey, bool capkey, unsigned int id)
{
    if (id == 0x00bbbb) return 2; // CAP key
    if (id == 0xbb00bb) return 1; // FIG key

    unsigned char selChar = 0; // selected character
    // figkey ? topsym : (capkey ? upper : lower);

    switch (id)
    {
        case 0xff0000: // a, A, at
            selChar = figkey ? 64 : ( capkey ? 65 : 97 );
            break;
        case 0x00ff00: // b, B, double quote
            selChar = figkey ? 34 : ( capkey ? 66 : 98 );
            break;
        case 0x0000ff: // c, C, tilde
            selChar = figkey ? 126 : ( capkey ? 67 : 99 );
            break;
        case 0xf0f0f0: // d, D, percent
            selChar = figkey ? 37 : ( capkey ? 68 : 100 );
            break;
        case 0x0f0f0f: // e, E, 3
            selChar = figkey ? 51 : ( capkey ? 69 : 101 );
            break;
        case 0xffff00: // f, F, ampersand
            selChar = figkey ? 38 : ( capkey ? 70 : 102 );
            break;
        case 0x00ffff: // g, G, underscore
            selChar = figkey ? 95 : ( capkey ? 71 : 103 );
            break;
        case 0xff00ff: // h, H, asterisk
            selChar = figkey ? 42 : ( capkey ? 72 : 104 );
            break;
        case 0x990000: // i, I, 8
            selChar = figkey ? 56 : ( capkey ? 73 : 105 );
            break;
        case 0x009900: // j, J, forward slash
            selChar = figkey ? 47 : ( capkey ? 74 : 106 );
            break;
        case 0x000099: // k, K, equals
            selChar = figkey ? 61 : ( capkey ? 75 : 107 );
            break;
        case 0x909090: // l, L, pound
            selChar = figkey ? 35 : ( capkey ? 76 : 108 );
            break;
        case 0x090909: // m, M, semicolon
            selChar = figkey ? 59 : ( capkey ? 77 : 109 );
            break;
        case 0x999900: // n, N, colon
            selChar = figkey ? 58 : ( capkey ? 78 : 110 );
            break;
        case 0x009999: // o, O, 9
            selChar = figkey ? 57 : ( capkey ? 79 : 111 );
            break;
        case 0x990099: // p, P, 0
            selChar = figkey ? 48 : ( capkey ? 80 : 112 );
            break;
        case 0x550000: // q, Q, 1
            selChar = figkey ? 49 : ( capkey ? 81 : 113 );
            break;
        case 0x005500: // r, R, 4
            selChar = figkey ? 52 : ( capkey ? 82 : 114 );
            break;
        case 0x000055: // s, S, dollar
            selChar = figkey ? 36 : ( capkey ? 83 : 115 );
            break;
        case 0x505050: // t, T, 5
            selChar = figkey ? 53 : ( capkey ? 84 : 116 );
            break;
        case 0x050505: // u, U, 7
            selChar = figkey ? 55 : ( capkey ? 85 : 117 );
            break;
        case 0x555500: // v, V, single quote
            selChar = figkey ? 39 : ( capkey ? 86 : 118 );
            break;
        case 0x005555: // w, W, 2
            selChar = figkey ? 50 : ( capkey ? 87 : 119 );
            break;
        case 0x550055: // x, X, close parenthesis
            selChar = figkey ? 41 : ( capkey ? 88 : 120 );
            break;
        case 0xbb0000: // y, Y, 6
            selChar = figkey ? 54 : ( capkey ? 89 : 121 );
            break;
        case 0x00bb00: // z, Z, open parenthesis
            selChar = figkey ? 40 : ( capkey ? 90 : 122 );
            break;
        case 0x0000bb: // question mark, back slash
            selChar = figkey ? 92 : 63;
            break;
        case 0xb0b0b0: // comma, left angle bracket
            selChar = figkey ? 60 : 44;
            break;
        case 0x0b0b0b: // period, right angle bracket
            selChar = figkey ? 62 : 46;
            break;
        case 0xbbbb00: // minus, plus
            selChar = figkey ? 43 : 45;
            break;
        case 0xffffff: // SPACE
            selChar = 32;
            break;
    }
    return selChar; // returns 0 if id doesn't match
}