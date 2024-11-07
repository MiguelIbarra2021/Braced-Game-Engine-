#ifndef _COMMON_H
#define _COMMON_H

// Commonly Used Libraries
#include<string.h>
#include <cmath>
#include<GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>	// Header File For Windows
#include <gl/gl.h>
#include <time.h>

// Color
typedef struct
{ float r = 0.0, g = 0.0, b = 0.0; }rgb;

// 2D/3D/4D vectors
typedef struct
{ float x = 0.0, y = 0.0; }vec2;

typedef struct
{ float x = 0.0, y = 0.0, z = 0.0; }vec3;

typedef struct
{ float x = 0.0, y = 0.0, z = 0.0, w = 0.0; }vec4;

// Commonly Used Namespaces
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
