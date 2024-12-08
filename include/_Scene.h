#ifndef SCENE_H
#define SCENE_H

// Internal Libraries
#include <vector>

// Custom Libraries
#include "_Scene.h"
#include "_LightSetup.h"
#include "_Models.h"
#include "_KbMs.h"
#include "_TerrainGenerator.h"
#include "_Common.h"
#include "_Collision.h"
#include "_Camera.h"
#include "_Projectile.h"
#include "_Skybox.h"
#include "_Sounds.h"

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        GLint initGL();
        GLint drawScene();
        GLvoid resizeScene(GLsizei, GLsizei);

        int winMsg(HWND, UINT, WPARAM, LPARAM);
        WPARAM wParam;

        // Game Engine Functions
        GLvoid initFog(float);

        GLvoid mouseMapping(int, int);
        GLvoid updateObjectRotation(vec3* object, vec3* target);

        GLvoid t_switch();

        GLvoid insertObject(char* tex_file, char* mdl_file); // Custom Models
        GLvoid insertObject(int);                           // Premade

        GLvoid Automatic_Launcher();
        GLvoid Launch_Duck(int, int);
        GLvoid Kill_Duck(int duck);

        GLvoid insertLight();

        // Game Engine Variables
        GLdouble mouseX, mouseY, mouseZ;
        float screenWidth, screenHeight;

        enum mode{ TRANSFORM, ROTATE, SCALE };   // Used to switch between what edit will happen to object
        mode transform_trigger;

        bool state_change;
        bool editmode;

        //boolean values used to determine levels
        bool doneLoading;
        bool liveLevel11;
        bool liveLevel12;
        bool liveLevel13;

    protected:

    private:
};

#endif // SCENE_H
