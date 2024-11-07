#include "_TextureLoader.h"

_TextureLoader::_TextureLoader()
{
    //ctor

}

_TextureLoader::~_TextureLoader()
{
    //dtor
}

void _TextureLoader::loadTexture(char* fileName)
{
    glGenTextures(1, &tex);             // Generate handler
    glBindTexture(GL_TEXTURE_2D, tex);   // Point image to handler

    image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

    // Load image file

    // Check errors
    if(!image)
        cout <<"Image: " << fileName << " not found" << endl;

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image);

    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void _TextureLoader::bindTexture()
{ glBindTexture(GL_TEXTURE_2D, tex); }   // Point image to handler
