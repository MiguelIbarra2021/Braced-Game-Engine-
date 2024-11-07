#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

#include <_Common.h>
#include <SOIL.h>

class _TextureLoader
{
    public:
        _TextureLoader();
        virtual ~_TextureLoader();

        GLuint tex;             // Image buffer id
        int width, height;   // Image dimensions
        unsigned char* image;   //

        void loadTexture(char* fileName);
        void bindTexture();

    protected:

    private:
};

#endif // _TEXTURELOADER_H
