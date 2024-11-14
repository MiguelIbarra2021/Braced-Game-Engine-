#ifndef _MODELS_H
#define _MODELS_H

#include <_Common.h>
#include <_TextureLoader.h>
#include <_ModelLoaderMD2.h>

class _Models
{
    public:
        // Constructor
        _Models();
        virtual ~_Models();

        // Functions
        GLvoid initModel(char* texture);
        GLvoid initModel(char* texture, char* model);
        GLvoid drawModel();  // Added model selection & rgb values
        GLvoid drawModel(int);  // Added model selection & rgb values

        // Transforms
        vec3 position;
        vec3 rotation;
        vec3 scale;

        rgb color;

        // Variables
        char* file_name;

        // Sub Classes
        _TextureLoader* tex = new _TextureLoader();
        _ModelLoaderMD2* mdl = new _ModelLoaderMD2();


    protected:

    private:
};

#endif // _MODELS_H
