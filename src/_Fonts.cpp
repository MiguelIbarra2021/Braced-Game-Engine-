#include "_Fonts.h"

void printBitmap(const GLubyte* bitmap) {
    for (int i = 0; i < 13; ++i) {
        for (int j = 7; j >= 0; --j) {
            std::cout << ((bitmap[i] & (1 << j)) ? '1' : '0');
        }
        std::cout << std::endl;
    }
}

GLubyte* flipBitmapVertical(const GLubyte* bitmap) {
    static GLubyte flipped[13];
    for (int i = 0; i < 13; ++i) {
        flipped[12 - i] = bitmap[i];
    }
    return flipped;
}

GLubyte* flipBitmapHorizontal(const GLubyte* bitmap) {
    static GLubyte flipped[13];
    for (int i = 0; i < 13; ++i) {
        flipped[i] = 0;
        for (int j = 0; j < 8; ++j) {
            if (bitmap[i] & (1 << j)) {
                flipped[i] |= (1 << (7 - j));
            }
        }
    }
    return flipped;
}

_Fonts::_Fonts()
{
    //ctor
}

_Fonts::~_Fonts()
{
    //dtor
}

void _Fonts::printString(char* str) {
    // std::cout << "printString called with: " << str << std::endl;
    // std::cout << "Using fontOffset: " << fontOffset << std::endl;
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists((GLsizei)strlen(str), GL_UNSIGNED_BYTE, (GLubyte*)str);
    glPopAttrib();
}

void _Fonts::makeRasterFont() {
    // std::cout << "makeRasterFont called" << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    fontOffset = glGenLists(128);
    // std::cout << "Font offset: " << fontOffset << std::endl;

    // Helper function to flip the bitmap vertically
    auto flipBitmapVertical = [](const GLubyte* bitmap) {
        static GLubyte flipped[13];
        for (int i = 0; i < 13; ++i) {
            flipped[12 - i] = bitmap[i];
        }
        return flipped;
    };

    // Generate lists for uppercase letters 'A' to 'Z'
    for (int i = 'A'; i <= 'Z'; i++) {
        // std::cout << "Creating list for character: " << char(i) << std::endl;
        glNewList(fontOffset + i, GL_COMPILE);
            glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i - 'A']);
        glEndList();
    }

    // Generate lists for digits '0' to '9'
    for (int i = '0'; i <= '9'; i++) {
        // std::cout << "Creating list for digit: " << char(i) << std::endl;
        const GLubyte* digitBitmap;
        switch (i) {
            case '0': digitBitmap = flipBitmapVertical(digit0); break;
            case '1': digitBitmap = flipBitmapVertical(digit1); break;
            case '2': digitBitmap = flipBitmapVertical(digit2); break;
            case '3': digitBitmap = flipBitmapVertical(digit3); break;
            case '4': digitBitmap = flipBitmapVertical(digit4); break;
            case '5': digitBitmap = flipBitmapVertical(digit5); break;
            case '6': digitBitmap = flipBitmapVertical(digit6); break;
            case '7': digitBitmap = flipBitmapVertical(digit7); break;
            case '8': digitBitmap = flipBitmapVertical(digit8); break;
            case '9': digitBitmap = flipBitmapVertical(digit9); break;
        }

        glNewList(fontOffset + i, GL_COMPILE);
            glBitmap(8, 13, 0.0, 2.0, 11.0, 0.0, digitBitmap);
        glEndList(); // Adjust the yorig if needed
    }

    // Generate lists for special symbols ':' and '.'
    glNewList(fontOffset + ':', GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, colon); // Corrected colon bitmap
    glEndList();

    glNewList(fontOffset + '.', GL_COMPILE);
        glBitmap(8, 13, 0.0, 11.0, 10.0, 0.0, period); // Updated period bitmap
    glEndList();

    // Include the space character (' ')
    glNewList(fontOffset + ' ', GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
    glEndList();

   // std::cout << "makeRasterFont completed" << std::endl;
}


void _Fonts::glutFonts(int x, int y, void* font, char* str) {
    // std::cout << "glutFonts called with text: " << str << std::endl;
    char* c;
    glRasterPos2i(x, y); // Use 2D coordinates for raster position
    for (c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

/*
glBitmap(
    GLsizei width,   // Width of the bitmap in pixels
    GLsizei height,  // Height of the bitmap in pixels
    GLfloat xorig,   // X-coordinate of the origin (alignment point) of the bitmap
    GLfloat yorig,   // Y-coordinate of the origin (alignment point) of the bitmap
    GLfloat xmove,   // X-offset to advance the current raster position after the bitmap is drawn
    GLfloat ymove,   // Y-offset to advance the current raster position after the bitmap is drawn
    const GLubyte* bitmap  // Pointer to the bitmap data array
);

glNewList(fontOffset + 'A', GL_COMPILE);
    // Create a new display list for the character 'A'
    glBitmap(
        8,  // Width: The bitmap is 8 pixels wide
        13, // Height: The bitmap is 13 pixels tall
        0.0,  // xorig: Origin point horizontally (typically 0 for alignment)
        2.0,  // yorig: Origin point vertically (adjusted for vertical alignment)
        10.0, // xmove: Move the raster position 10 pixels to the right after drawing
        0.0,  // ymove: No vertical movement needed for horizontal text
        letters['A' - 'A']  // Bitmap data for the character 'A'
    );
glEndList();
*/
