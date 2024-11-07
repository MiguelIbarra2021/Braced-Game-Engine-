#ifndef _TERRAINGENERATOR_H
#define _TERRAINGENERATOR_H

#include <_Common.h>
#include <_TextureLoader.h>

class _TerrainGenerator
{
    public:
        // Constructors
        _TerrainGenerator();
        virtual ~_TerrainGenerator();

        // Functions
        GLvoid initTerrain(char* file);
        GLvoid drawTerrain();

        // Sub Classes
        _TextureLoader* tex = new _TextureLoader();

        // Variables
        vec3 position;
        vec3 rotation;
        vec3 scale;

        rgb color_offset;

        vec2 t_max, t_min;


    protected:

    private:
};

#endif // _TERRAINGENERATOR_H
