#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

// Custom Libraries
#include "_Common.h"

// External Libraries
#include <SOIL.h>

class _TextureLoader
{
    public:
        // Constructors
        _TextureLoader();
        virtual ~_TextureLoader();

        // Functions
        void loadTexture(char* file);
        void bindTexture();

        // Variables
        GLuint tex;             // Image buffer id
        int width, height;      // Image dimensions
        unsigned char* image;   // Image location

    protected:

    private:
};

#endif // _TEXTURELOADER_H
