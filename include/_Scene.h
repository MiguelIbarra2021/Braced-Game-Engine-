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
#include "_RandomNumber.h"
#include "_Particles.h"

// Added This
#include "_TextureLoader.h"
#include "LandingPage.h"

#include "_Timer.h"
#include "_Fonts.h"
#include "_HUD.h"

enum GameState {
    LANDING_PAGE,
    MENU_PAGE,
    GAME_PLAY,
    HELP_PAGE,
    // PAUSE_MENU,
    TEST_HUD // state for testing HUD
};

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        GLint initGL();
        void enableCelShading();
        GLint drawScene();
        GLvoid resizeScene(GLsizei, GLsizei);

        int winMsg(HWND, UINT, WPARAM, LPARAM);
        WPARAM wParam;

        // Game Engine Functions
        GLvoid initFog();
        GLvoid initFoliage();
        GLvoid drawFoliage();

        GLvoid initShotgun();
        GLvoid initDuck();

        GLvoid updateSkybox();

        GLvoid mouseMapping(int, int);
        GLvoid rotateTowards(vec3* object, vec3* target);
        GLvoid rotateDuck(vec3* duck, vec3 target); // added this

        GLvoid t_switch();

        GLvoid insertObject(char* tex_file, char* mdl_file); // Custom Models
        GLvoid insertObject(int);                           // Premade

        GLvoid Automatic_Launcher();
        GLvoid Launch_Duck(int);
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

        // added this
        bool wireFrame = false;

        // for landing Page
        LandingPage* landingPage;
        GameState currentState;
        void GamePlay();

        // button 1 area
        GLdouble btn1Xmin = -0.2164;
        GLdouble btn1Xmax = 0.2135;
        GLdouble btn1Ymin = -0.0484;
        GLdouble btn1Ymax = -0.1623;

        // button 2 area
        GLdouble btn2Xmin = -0.2164;
        GLdouble btn2Xmax = 0.2135;
        GLdouble btn2Ymin = -0.256;
        GLdouble btn2Ymax = -0.3730;

        // button 3 area
        GLdouble btn3Xmin = -0.2164;
        GLdouble btn3Xmax = 0.2135;
        GLdouble btn3Ymin = -0.4669;
        GLdouble btn3Ymax = -0.5837;

        // mapping
        GLdouble bMouseX;
        GLdouble bMouseY;

        // button clicked
        GLboolean isBtn1Clicked();
        GLboolean isBtn2Clicked();
        GLboolean isBtn3Clicked();

        // added this for buttons click future stuff
        void goToGamePlay();
        void showHelpPage();
        void exitApplication();

        _Timer* gameTimer;

        // Font member pointer
        _Fonts* font;

        // HUD variables
        int shotsLeft;
        int pointsHit;
        int pointsMissed;

        // For the HUD
        int GetShotsLeft();
        int GetPointsHit();
        int GetPointsMissed();

        // HUD stuff
        // added for HUD rendering
        void updateTimer();
        void RenderHUD();
        int getAmmo() const;
        int getScore() const;
        int getMinutes() const;
        int getSeconds() const;
        const char* getNotification() const;
        _HUD* hud;

        int minutes;
        int seconds;
        float lastTime;

        // pause menu stuff
        bool isPaused = false;

        // Variables to save the game paused state
        float savedViewDirectionX, savedViewDirectionY, savedViewDirectionZ;
        double savedStartTime;
        int savedMinutes, savedSeconds;

        // Variables to save ducks state
        vec3 savedDuckPositions[4];
        vec3 savedDuckRotations[4];
        int savedDuckActions[4];

        // variables to save gun state
        vec3 savedGunPosition; vec3 savedGunRotation;

        // Variables to save bullets state
        vec3 savedBulletPositions[20];
        bool savedBulletLiveState[20];

        // Variables to save timer states and flags
        clock_t savedDuckTimer;
        bool wasDuckTimerRunning;
        clock_t savedGameTimer;
        bool wasGameTimerRunning;

        void pauseGame();
        void resumeGame();

        // added this
        bool duckDebug = false; // flag to control duck debugging

        // gunBarrel & offsets for bullets adj
        void initBullets();
        vec3 gunBarrelPosition; vec3 gunBarrelOffset;

    protected:

    private:
};

#endif // SCENE_H
