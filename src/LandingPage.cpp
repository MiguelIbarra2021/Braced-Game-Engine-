#include "LandingPage.h"

LandingPage::LandingPage() {
    landingBackgroundTexture = new _TextureLoader();
    menuBackgroundTexture = new _TextureLoader();
    helpBackgroundTexture = new _TextureLoader();
    pauseBackgroundTexture = new _TextureLoader();
    buttonTexture1 = new _TextureLoader();
    buttonTexture2 = new _TextureLoader();
    buttonTexture3 = new _TextureLoader();
}

LandingPage::~LandingPage() {
    delete landingBackgroundTexture;
    delete menuBackgroundTexture;
    delete helpBackgroundTexture;
    delete pauseBackgroundTexture;
    delete buttonTexture1;
    delete buttonTexture2;
    delete buttonTexture3;
}

// may use it for something else, in the future, but for this midterm
void LandingPage::setButtonPositions(float windowWidth, float windowHeight)
{
    float menuCenterX = windowWidth / 2;
    float menuCenterY = windowHeight / 2;

    buttonWidth1 = 200; buttonHeight1 = 50;
    buttonWidth2 = 200; buttonHeight2 = 50;

    buttonX1 = menuCenterX - buttonWidth1 / 2;
    buttonY1 = menuCenterY + 100;

    buttonX2 = menuCenterX - buttonWidth2 / 2;
    buttonY2 = menuCenterY;
}

void LandingPage::initPageTextures(char* landingBackground, char* menuBackground, char* helpBackground, char* pauseBackground,
                                   char* buttonFile1, char* buttonFile2, char* buttonFile3) {
    landingBackgroundTexture->loadTexture(landingBackground);
    menuBackgroundTexture->loadTexture(menuBackground);
    helpBackgroundTexture->loadTexture(helpBackground);
    pauseBackgroundTexture->loadTexture(pauseBackground);
    buttonTexture1->loadTexture(buttonFile1);
    buttonTexture2->loadTexture(buttonFile2);
    buttonTexture3->loadTexture(buttonFile3);
}

void LandingPage::drawLandingPage(float windowWidth, float windowHeight) {
    // Calculate the aspect ratios of the window and the image
    float windowAspectRatio = (float)windowWidth / windowHeight;
    float imageAspectRatio = (float)landingBackgroundTexture->width / landingBackgroundTexture->height;

    float scaleX = 1.8;
    float scaleY = 1.0;
    float zValue = -2.2;

    // adjust scaling factors based on aspect ratios
    if (windowAspectRatio > imageAspectRatio)
    {
        // window is wider than image, scale down height
        scaleX = (float)imageAspectRatio / windowAspectRatio;
    }
    else
    {
        // window is taller than the image, scale down height
        scaleY = (float)windowAspectRatio / imageAspectRatio;
    }

    landingBackgroundTexture->bindTexture();

    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-scaleX, scaleY, zValue);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX, scaleY, zValue);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX, -scaleY, zValue);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-scaleX, -scaleY, zValue);
    glEnd();

    glEnable(GL_LIGHTING);
    // Optionally draw buttons on the landing page
}

void LandingPage::drawMenuPage(float windowWidth, float windowHeight) {
    float windowAspectRatio = (float)windowWidth / windowHeight;
    float imageAspectRatio = (float)menuBackgroundTexture->width / menuBackgroundTexture->height;

    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float zValue = -2.2f;
    float adjX = 0.9f;
    float adjY = 0.1f;

    // Determine scaling factors based on aspect ratios
    if (windowAspectRatio > imageAspectRatio) {
        scaleX = imageAspectRatio / windowAspectRatio;
    } else {
        scaleY = windowAspectRatio / imageAspectRatio;
    }

    menuBackgroundTexture->bindTexture();

    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-scaleX - adjX, scaleY + adjY, zValue);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX + adjX, scaleY + adjY, zValue);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX + adjX, -scaleY - adjY, zValue);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-scaleX - adjX, -scaleY - adjY, zValue);
    glEnd();

    // Calculate button positions and sizes in normalized device coordinates
    float buttonRelativeWidth = 0.6f;  // 20% of the menu width
    float buttonRelativeHeight = 0.2f; // 10% of the menu height

    float buttonWidth = buttonRelativeWidth * scaleX;
    float buttonHeight = buttonRelativeHeight * scaleY;

    // Position buttons relative to the menu page
    float buttonX1 = -scaleX + 0.7f * scaleX; // 10% from left
    float buttonY1 = scaleY - 1.0f * scaleY;  // 20% from top

    float buttonX2 = buttonX1;
    float buttonY2 = buttonY1 - 0.21f * scaleY; // Adjust Y for the second button

    float buttonX3 = buttonX1;
    float buttonY3 = buttonY2 - 0.21f * scaleY; // Adjust Y for the third button

    // Draw buttons
    buttonTexture1->bindTexture();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(buttonX1, buttonY1, zValue);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(buttonX1 + buttonWidth, buttonY1, zValue);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(buttonX1 + buttonWidth, buttonY1 - buttonHeight, zValue);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(buttonX1, buttonY1 - buttonHeight, zValue);
    glEnd();

    buttonTexture2->bindTexture();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(buttonX2, buttonY2, zValue);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(buttonX2 + buttonWidth, buttonY2, zValue);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(buttonX2 + buttonWidth, buttonY2 - buttonHeight, zValue);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(buttonX2, buttonY2 - buttonHeight, zValue);
    glEnd();

    buttonTexture3->bindTexture();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(buttonX3, buttonY3, zValue);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(buttonX3 + buttonWidth, buttonY3, zValue);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(buttonX3 + buttonWidth, buttonY3 - buttonHeight, zValue);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(buttonX3, buttonY3 - buttonHeight, zValue);
    glEnd();

    glEnable(GL_LIGHTING);
}

void LandingPage::drawHelpPage(float windowWidth, float windowHeight) {
    float windowAspectRatio = (float)windowWidth / windowHeight;
    float imageAspectRatio = (float)helpBackgroundTexture->width / helpBackgroundTexture->height;

    float scaleX = 1.8;
    float scaleY = 1.0;
    float zValue = -2.2;

    float adjX = -0.1f;
    float adjY = 0.1f;

    if (windowAspectRatio > imageAspectRatio) {
        scaleX = imageAspectRatio / windowAspectRatio;
    } else {
        scaleY = windowAspectRatio / imageAspectRatio;
    }

    helpBackgroundTexture->bindTexture();

    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-scaleX - adjX, scaleY, zValue);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX + adjX, scaleY, zValue);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX + adjX, -scaleY, zValue);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-scaleX - adjX, -scaleY, zValue);
    glEnd();

    glEnable(GL_LIGHTING);
    // Optionally draw buttons or other elements
}

void LandingPage::drawPausePage(float windowWidth, float windowHeight) {
    // pause menu
    float windowAspectRatio = (float)windowWidth / windowHeight;
    float imageAspectRatio = (float)pauseBackgroundTexture->width / pauseBackgroundTexture->height;

    float scaleX = 1.8;
    float scaleY = 1.0;

    if (windowAspectRatio > imageAspectRatio) {
        scaleX = windowWidth;
        scaleY = windowWidth / imageAspectRatio;
    } else {
        scaleX = windowHeight * imageAspectRatio;
        scaleY = windowHeight;
    }

    // Bind the texture and draw the quad
    pauseBackgroundTexture->bindTexture();

    // Enable blending for transparency
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 1.0, 1.0, 1.0); // Adjust alpha value for transparency

    float adjX = 600;
    float adjY = 500;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f((windowWidth - scaleX + adjX) / 2, (windowHeight - scaleY + adjY) / 2); // Bottom-left corner
        glTexCoord2f(1.0f, 0.0f); glVertex2f((windowWidth + scaleX - adjX) / 2, (windowHeight - scaleY + adjY) / 2); // Bottom-right corner
        glTexCoord2f(1.0f, 1.0f); glVertex2f((windowWidth + scaleX - adjX) / 2, (windowHeight + scaleY - adjX) / 2); // Top-right corner
        glTexCoord2f(0.0f, 1.0f); glVertex2f((windowWidth - scaleX + adjX) / 2, (windowHeight + scaleY - adjX) / 2); // Top-left corner
    glEnd();

    // Disable blending and re-enable lighting
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

/* original pause page
void LandingPage::drawPausePage(float windowWidth, float windowHeight) {
    // pause menue
    float windowAspectRatio = (float)windowWidth / windowHeight;
    float imageAspectRatio = (float)pauseBackgroundTexture->width / pauseBackgroundTexture->height;

    float scaleX = 1.8;
    float scaleY = 1.0;
    float zValue = 3.0; // -2.2 , 3.0 works

    float adjX = 0.0f;
    float adjY = -0.5f;

    if (windowAspectRatio > imageAspectRatio) {
        scaleX = imageAspectRatio / windowAspectRatio;
    } else {
        scaleY = windowAspectRatio / imageAspectRatio;
    }

    // make sure to use a .png format texture and has an alpha channel that supports transparency (RGBA) usually
    pauseBackgroundTexture->bindTexture();

    // for transparency
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 1.0, 1.0, 1.0); // Adjust alpha value for transparency

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-scaleX - adjX, scaleY + adjY, zValue); // top left
        glTexCoord2f(-1.0f, 0.0f); glVertex3f(scaleX + adjX, scaleY + adjY, zValue); // bot left
        glTexCoord2f(-1.0f, 1.0f); glVertex3f(scaleX + adjX, -scaleY - adjY, zValue); // bot right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-scaleX - adjX, -scaleY - adjY, zValue); // top right
    glEnd();

    // original from my code, but needed to modify because it's mirrored in our game version
    // glBegin(GL_QUADS);
      //  glTexCoord2f(0.0f, 0.0f); glVertex3f(-scaleX - adjX, scaleY + adjY, zValue); // top left
      //  glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX + adjX, scaleY + adjY, zValue); // bot left
      //  glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX + adjX, -scaleY - adjY, zValue); // bot right
      //  glTexCoord2f(0.0f, 1.0f); glVertex3f(-scaleX - adjX, -scaleY - adjY, zValue); // top right
    // glEnd();
    //

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
*/

/*
// added this for button functionality may use in the future
void LandingPage::handleButtonEvent(float mouseX, float mouseY, float mouseZ, bool mousePressed, _Scene* scene) {
    float zPlane = -2.2f; // The Z-plane where buttons are assumed to be

    if (mousePressed && mouseZ == zPlane) {
        std::cout << "Mouse pressed at (" << mouseX << ", " << mouseY << ", " << mouseZ << ")" << std::endl;

        if (mouseX >= buttonX1 && mouseX <= buttonX1 + buttonWidth1 &&
            mouseY >= buttonY1 && mouseY <= buttonY1 + buttonHeight1) {
            std::cout << "Button 1 clicked." << std::endl;
            scene->goToGamePlay();
        } else if (mouseX >= buttonX2 && mouseX <= buttonX2 + buttonWidth2 &&
                   mouseY >= buttonY2 && mouseY <= buttonY2 + buttonHeight2) {
            std::cout << "Button 2 clicked." << std::endl;
            scene->showHelpPage();
        } else if (mouseX >= buttonX3 && mouseX <= buttonX3 + buttonWidth3 &&
                   mouseY >= buttonY3 && mouseY <= buttonY3 + buttonHeight3) {
            std::cout << "Button 3 clicked." << std::endl;
            scene->exitApplication();
        } else {
            std::cout << "No button clicked." << std::endl;
        }
    }
}
*/
