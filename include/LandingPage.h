#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include "_TextureLoader.h"
#include <_Common.h>
#include <iostream>

//class _Scene; // Forward declaration


class LandingPage {
public:
    LandingPage();
    ~LandingPage();

    void initPageTextures(char* landingBackground, char* menuBackground, char* helpBackground, char* pauseBackground,
                          char* buttonFile1, char* buttonFile2, char* buttonFile3);  // Use const char*
    void drawLandingPage(float screenWidth, float screenHeight);
    void drawMenuPage(float screenWidth, float screenHeight);
    void drawHelpPage(float screenWidth, float screenHeight);
    void drawPausePage(float screenWidth, float screenHeight);
    //void handleButtonEvent(float, float, float, bool, _Scene*); // for button click
    void setButtonPositions(float windowWidth, float windowHeight);

private:
    _TextureLoader* landingBackgroundTexture;
    _TextureLoader* menuBackgroundTexture;
    _TextureLoader* helpBackgroundTexture;
    _TextureLoader* pauseBackgroundTexture;
    _TextureLoader* buttonTexture1;
    _TextureLoader* buttonTexture2;
    _TextureLoader* buttonTexture3;
    float buttonX1, buttonY1, buttonWidth1, buttonHeight1;
    float buttonX2, buttonY2, buttonWidth2, buttonHeight2;
    float buttonX3, buttonY3, buttonWidth3, buttonHeight3;
};

#endif // LANDINGPAGE_H
