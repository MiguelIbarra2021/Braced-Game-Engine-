#ifndef _COMMON_H
#define _COMMON_H

#include<string.h>
#include <cmath>
#include<GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>	// Header File For Windows
#include <gl/gl.h>
#include <time.h>

typedef struct{

    float r, g, b;
}rgb;

typedef struct{

    float x, y, z;
}vec3;

typedef struct{

    float x, y, z, w;
}vec4;

typedef struct{

    float x, y;
}vec2;

using namespace std;
class _Common
{
    public:
        _Common();
        virtual ~_Common();

    protected:

    private:
};

#endif // _COMMON_H
