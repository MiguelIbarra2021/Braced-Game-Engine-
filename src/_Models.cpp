#include "_Models.h"

_Models::_Models()
{
    //ctor

    rotateX = 0.0;
    rotateY = 0.0;
    rotateZ = 0.0;

    positionX = 0.0;
    positionY = 0.0;
    positionZ = -8.0;
}

_Models::~_Models()
{
    //dtor
}

GLvoid _Models::initModel(char* fileName)
{
    myTex->loadTexture(fileName);
}

GLvoid _Models::drawModel(int sel, double r, double g, double b)
{
    // glColor3f(0.55, 0.30, 0.10); // Old brown rgb
    glColor3f(r, g, b); // Custom rgb

    // Translation goes first
    glTranslated(positionX, positionY, positionZ);

    // Rotate on all 3 axis
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);
    glRotatef(rotateZ, 0, 0, 1);

    switch(sel)  // Select type of model selected
    {
    case 1:
        glutSolidTorus(0.5, 1.5, 40, 40);
        break;
    case 2:
        myTex->bindTexture();
        glutSolidTeapot(2.5);
        break;
    }
}
