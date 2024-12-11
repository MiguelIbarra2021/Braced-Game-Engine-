#ifndef _HUD_H
#define _HUD_H

#include <_Common.h>
#include "_Fonts.h"
//#include <windows.h>

class _HUD
{
    public:
        _HUD();
        virtual ~_HUD();

    //void RenderHUD();
    void initFonts();
    void initHUD(); // ++++++++++++ added ++++++++++++++++
    void draw(int ammo, int score, int minutes, int seconds, const char* notification);
    void drawCrosshair();
    void drawAmmoCount(int ammo);
    void drawScore(int score);
    void drawTimer(int minutes, int seconds);
    void drawNotification(const char* notification);

    _Fonts* font;
    int screenWidth;
    int screenHeight;
    // POINT mousePos;

    int shotsL;
    int pointsL;
    int pointsM;

    // ++++++++ added +++++++++
    double mouseX, mouseY, rotationX, rotationY;
    void update(); // update position
    // ++++++++ added +++++++++

    protected:

    private:
};

#endif // _HUD_H
