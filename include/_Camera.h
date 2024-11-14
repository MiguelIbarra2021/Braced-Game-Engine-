#ifndef _CAMERA_H
#define _CAMERA_H

#include <_Common.h>
#include <cmath>

class _Camera
{
    public:
        _Camera();
        virtual ~_Camera();

        vec3 eye;
        vec3 des;
        vec3 upVec;

        bool mode = false;

        GLvoid camInit();
        GLvoid setUpCam();
        GLvoid orbitCamera(float, float);

        // New
        GLvoid updateViewDirection();

        float radius = 100.0f;   // Distance from the target
        float angleX = 0.0f;     // Horizontal angle
        float angleY = 0.0f;     // Vertical angle

    protected:

    private:
};

#endif // _CAMERA_H
