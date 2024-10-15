#ifndef _LIGHTSETUP_H
#define _LIGHTSETUP_H

#include <_Common.h>

class _lightSetup
{
    public:
        _lightSetup();
        virtual ~_lightSetup();

        GLfloat light_ambient[4];       // Environment
        GLfloat light_diffuse[4];       // For Shade
        GLfloat light_specular[4];      // For Shine
        GLfloat light_position[4];      // Light Position

        GLfloat mat_ambient[4];         // Material Value
        GLfloat mat_diffuse[4];         //
        GLfloat mat_specular[4];        //
        GLfloat high_shininess[1];      //

        GLvoid setLight(GLenum);
        GLvoid movingLight(GLenum, double, double);

        float spin = 0.0f;              // Value For Light Spin
        bool dir;

    protected:

    private:
};

#endif // _LIGHTSETUP_H
