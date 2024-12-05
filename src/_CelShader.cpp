#include "_Common.h"
#include <cmath>

class CelShading {
public:
    void apply() {
        setupLight();
    }

    void setupLight() {
        GLfloat lightPos[] = { 0.0f, 1.0f, 1.0f, 0.0f };
        GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    }

    void enableCelShading() {
        glShadeModel(GL_FLAT);
        GLfloat materialColor[] = { 1.0f, 0.5f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
    }
};
