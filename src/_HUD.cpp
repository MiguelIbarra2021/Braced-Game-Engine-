#include "_HUD.h"

_HUD::_HUD()
{
    //ctor

    font = new _Fonts();
    // Initialize screen width and height
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

_HUD::~_HUD()
{
    //dtor
    delete font;
}

void _HUD::initFonts()
{
    font->makeRasterFont(); // Initialize raster font
}

// +++++++++++ added ++++++++++++++++++++
void _HUD::initHUD()
{
    mouseX = (GetSystemMetrics(SM_CYSCREEN)) / 2;
    mouseY = (GetSystemMetrics(SM_CXSCREEN)) / 2;
    rotationX = 0;
    rotationY = 0;
}
// +++++++++++ added ++++++++++++++++++++

void _HUD::update() // not needed
{
}

void _HUD::draw(int ammo, int score, int minutes, int seconds, const char* notification) {
    drawCrosshair();
    drawAmmoCount(ammo);
    drawScore(score);
    drawTimer(minutes, seconds);
    drawNotification(notification);
}

// +++++ modified ++++++++++++++++++++++++++++++++
void _HUD::drawCrosshair()
{
    glColor3f(1.0, 1.0, 1.0); // White color
    glBegin(GL_LINES);
        // Draw the horizontal line of the crosshair at mouse position
        glVertex2f(mouseX - 10, mouseY);
        glVertex2f(mouseX + 10, mouseY);
        // Draw the vertical line of the crosshair at mouse position
        glVertex2f(mouseX, mouseY - 10);
        glVertex2f(mouseX, mouseY + 10);
    glEnd();

    // Debug output for crosshair position
    std::cout << "Crosshair Position - X: " << mouseX << ", Y: " << mouseY << std::endl;
}

/* original drawCrosshair method
void _HUD::drawCrosshair()
{
    glColor3f(1.0, 1.0, 1.0); // White color
    glBegin(GL_LINES);
        // Draw the horizontal line of the crosshair
        glVertex2f(screenWidth / 2.0f - 10, screenHeight / 2.0f);
        glVertex2f(screenWidth / 2.0f + 10, screenHeight / 2.0f);
        // Draw the vertical line of the crosshair
        glVertex2f(screenWidth / 2.0f, screenHeight / 2.0f - 10);
        glVertex2f(screenWidth / 2.0f, screenHeight / 2.0f + 10);
    glEnd();
}
*/

void _HUD::drawAmmoCount(int ammo) {
    char ammoStr[10];
    sprintf(ammoStr, "AMMO: %d", ammo); // Uppercase "AMMO"
    glRasterPos2f(100, 50); // Position in top-left corner with some padding
    font->printString("AMMO: "); // Render "AMMO: "

    char digitStr[10];
    sprintf(digitStr, "%d", ammo);
    glRasterPos2f(100 + 50, 49); // Adjust position for digits next to "AMMO: "
    font->printString(digitStr);
}

void _HUD::drawScore(int score) {
    char scoreStr[10];
    sprintf(scoreStr, "SCORE: %d", score);
    glRasterPos2f(600, 50); // Position in top-right corner
    font->printString("SCORE: ");

    char digitStr[10];
    sprintf(digitStr, "%d", score);
    glRasterPos2f(600 + 60, 48.5); // Adjust position for digits next to "AMMO: "
    font->printString(digitStr);
}
void _HUD::drawTimer(int minutes, int seconds) {
    char timerStr[10];
    sprintf(timerStr, "%02d:%02d", minutes, seconds); // Format the timer as MM:SS
    glRasterPos2f(1100.0, 50); // Position it at the top center
    font->printString(timerStr);
}

void _HUD::drawNotification(const char* notification) {
    glColor3f(1.0, 1.0, 1.0); // White color
    glRasterPos2f(575, 200); // Position at the bottom center
    font->printString(const_cast<char*>(notification));
}
