#ifndef _MODELS_H
#define _MODELS_H

#include <_Common.h>
#include <_TextureLoader.h>

class _Models
{
    public:
        // Constructor
        _Models();
        virtual ~_Models();

        // Functions
        GLvoid initModel(char* fileName);
        GLvoid drawModel(int);  // Added model selection & rgb values

        // Transforms
        vec3 position;
        vec3 rotation;
        vec3 scale;

        rgb color;

        // Sub Classes
        _TextureLoader* myTex = new _TextureLoader();


    protected:

    private:
};

#endif // _MODELS_H
