#include "_Models.h"

_Models::_Models()
{
    color.r = 1.0;
    color.g = 1.0;
    color.b = 1.0;

    position.z = -8.0;
}

_Models::~_Models()
{}

GLvoid _Models::initModel(char* fileName)
{ myTex->loadTexture(fileName); }

GLvoid _Models::drawModel(int sel)
{
    // Color
    glColor3f(color.r, color.g, color.b); // Custom rgb

    // Translation goes first
    glTranslated(position.x, position.y, position.z);

    // Rotate on all 3 axis
    glRotatef(rotation.x, 1, 0, 0);
    glRotatef(rotation.y, 0, 1, 0);
    glRotatef(rotation.z, 0, 0, 1);

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
