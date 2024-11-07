#ifndef _SKYBOX_H
#define _SKYBOX_H


#include "_Common.h"
#include "_TextureLoader.h"
#include "_Timer.h"

class _Skybox
{
    public:
        _Skybox();
        virtual ~_Skybox();

        void skyBoxInit(char *);
        void skyBoxDraw();

        vec2 tMax;
        vec2 tMin;
        vec3 scale; //scaler value
        vec3 trans; //Translation
        vec3 rot; //Rotations

        _TextureLoader *tex = new _TextureLoader();



    protected:

    private:
};

#endif // _SKYBOX_H
