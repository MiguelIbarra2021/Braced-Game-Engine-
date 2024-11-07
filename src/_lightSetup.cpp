#include "_LightSetup.h"

_LightSetup::_LightSetup()
{
    //ctor
    dir = false;
}

_LightSetup::~_LightSetup()
{
    //dtor
}
GLvoid _LightSetup::setLight(GLenum light)
{
    glEnable(light);
    glEnable(GL_LIGHTING);

        light_ambient[0] = 0;       // Environment
        light_ambient[1] = 0;       // Environment
        light_ambient[2] = 0;       // Environment
        light_ambient[3] = 1;       // Environment

        light_diffuse[0] = 1;       // For Shade
        light_diffuse[1] = 1;       // For Shade
        light_diffuse[2] = 1;       // For Shade
        light_diffuse[3] = 1;       // For Shade

        light_specular[0] = 1;      // For Shine
        light_specular[1] = 1;      // For Shine
        light_specular[2] = 1;      // For Shine
        light_specular[3] = 1;      // For Shine

        light_position[0] = 2;      // Light Position
        light_position[1] = 5;      // Light Position
        light_position[2] = 5;      // Light Position
        light_position[3] = 1;      // Light Position

        mat_ambient[0] = 0.7;         // Material Value
        mat_ambient[1] = 0.7;         // Material Value
        mat_ambient[2] = 0.7;         // Material Value
        mat_ambient[3] = 1.0;         // Material Value

        mat_diffuse[0] = 0.8;         //
        mat_diffuse[1] = 0.8;         //
        mat_diffuse[2] = 0.8;         //
        mat_diffuse[3] = 1.0;         //

        mat_specular[0] = 1;        //
        mat_specular[1] = 1;        //
        mat_specular[2] = 1;        //
        mat_specular[3] = 1;        //

        high_shininess[1] = 100.0;      //
}

GLvoid _LightSetup::movingLight(GLenum light, double x, double y)
{
    /*if(!dir)
        if(spin < 10)
            spin += 0.05f;
        else
            dir = true;
    else if(dir)
        if(spin >= -10)
            spin -= 0.05f;
        else
            dir = false;*/

    //spin += 0.05;                 // Spinning My Light

    glPushMatrix();         // Start Grouping
        glTranslated(x/100, -y/100 , 0);    // Follow mouse around x & y
        glLightfv(light, GL_POSITION, light_position);  // Change Light Position
    glPopMatrix();  // End grouping
}
