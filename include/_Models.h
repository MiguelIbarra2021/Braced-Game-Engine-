#ifndef _MODELS_H
#define _MODELS_H

#include <_Common.h>
#include <_TextureLoader.h>

class _Models
{
    public:
        _Models();
        virtual ~_Models();

        GLfloat rotateX;
        GLfloat rotateY;
        GLfloat rotateZ;

        GLfloat positionX;
        GLfloat positionY;
        GLfloat positionZ;

        _TextureLoader* myTex = new _TextureLoader();
        GLvoid initModel(char* fileName);
        GLvoid drawModel(int, double, double, double);  // Added model selection & rgb values

    protected:

    private:
};

#endif // _MODELS_H
