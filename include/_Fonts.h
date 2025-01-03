#ifndef _FONTS_H
#define _FONTS_H

#include <_Common.h>

static GLubyte space[] ={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static GLubyte letters[][13] = {
// UPPER CASE LETTERS
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18}, // A
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, // B
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, // C
{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc}, // D
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff}, // E
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff}, // F
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, // G
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // H
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e}, // I
{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06}, // J
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3}, // K
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0}, // L
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3}, // M
{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3}, // N
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e}, // O
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, // P
{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c}, // Q
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, // R
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e}, // S
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff}, // T
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // U
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // V
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // W
{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, // X
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, // Y
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff} // Z
};

// Symbols: colon (:)
static GLubyte colon[] = {
    0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00
};

// Symbols: period (.)
static GLubyte period[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00
};

/*
static GLubyte digit0[] = {
    0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x00
}; // 0

static GLubyte digit1[] = {
    0x00, 0x00, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x18, 0x7e
}; // 1

static GLubyte digit2[] = {
    0x00, 0x00, 0x7f, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xff, 0x00, 0x00
}; // 2

static GLubyte digit3[] = {
    0x00, 0x00, 0x7e, 0x03, 0x03, 0x3e, 0x03, 0x03, 0x03, 0x03, 0x7e, 0x00, 0x00
}; // 3

static GLubyte digit4[] = {
    0x00, 0x00, 0x0f, 0x0f, 0x1b, 0x1b, 0x33, 0x33, 0x63, 0xff, 0x03, 0x03, 0x03
}; // 4

static GLubyte digit5[] = {
    0x00, 0x00, 0xfe, 0xc0, 0xc0, 0xfe, 0x03, 0x03, 0x03, 0x03, 0xfe, 0x00, 0x00
}; // 5

static GLubyte digit6[] = {
    0x00, 0x00, 0x7e, 0xe0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00
}; // 6

static GLubyte digit7[] = {
    0x00, 0x00, 0xff, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00
}; // 7

static GLubyte digit8[] = {
    0x00, 0x00, 0x7e, 0xc3, 0xc3, 0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00
}; // 8

static GLubyte digit9[] = {
    0x00, 0x00, 0x7e, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x7e, 0x00, 0x00
}; // 9
*/

static GLubyte digit0[] = {
    0x00, 0x00, 0x3C, 0x66, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x66, 0x3C, 0x00
}; // 0

static GLubyte digit1[] = {
    0x00, 0x00, 0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00
}; // 1

static GLubyte digit2[] = {
    0x00, 0x00, 0x7E, 0xC3, 0x03, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xFF, 0x00
}; // 2

static GLubyte digit3[] = {
    0x00, 0x00, 0x7E, 0xC3, 0x03, 0x03, 0x3E, 0x03, 0x03, 0x03, 0xC3, 0x7E, 0x00
}; // 3

static GLubyte digit4[] = {
    0x00, 0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFF, 0x0C, 0x0C, 0x0C, 0x1E, 0x00
}; // 4

static GLubyte digit5[] = {
    0x00, 0x00, 0xFF, 0xC0, 0xC0, 0xFC, 0xC6, 0x03, 0x03, 0x03, 0xC3, 0x7E, 0x00
}; // 5

static GLubyte digit6[] = {
    0x00, 0x00, 0x3E, 0x60, 0xC0, 0xFC, 0xE6, 0xC3, 0xC3, 0xC3, 0x66, 0x3C, 0x00
}; // 6

static GLubyte digit7[] = {
    0x00, 0x00, 0xFF, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0xC0, 0xC0, 0x00
}; // 7

static GLubyte digit8[] = {
    0x00, 0x00, 0x7E, 0xC3, 0xC3, 0x7E, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x7E, 0x00
}; // 8

static GLubyte digit9[] = {
    0x00, 0x00, 0x7E, 0xC3, 0xC3, 0xC3, 0x7F, 0x03, 0x03, 0x06, 0x0C, 0x78, 0x00
}; // 9


class _Fonts
{
    public:
        _Fonts();
        virtual ~_Fonts();

        GLuint fontOffset;

        void printString(char* str);
        void makeRasterFont();
        void glutFonts(int x, int y, void* font, char* str);
        //void glutFonts(float x, float y, void* font, char* str);

    protected:

    private:
};

#endif // _FONTS_H
