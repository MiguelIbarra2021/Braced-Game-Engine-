#include "_Scene.h"

_LightSetup** lightHierarchy = nullptr;     // Allows for multiple seperate lights
_LightSetup* myLight = new _LightSetup();   // Original Light
_Models** objectHierarchy = nullptr;        // Hierarchy of objects
_KbMs* sysControl = new _KbMs();            // Mouse and Key Control

int objects = 0;                            // # of objects in Scene
int lights = 0;                            // # of lights in Scene

Scene::Scene()
{}

Scene::~Scene()
{}

int Scene::winMsg(HWND	hWnd,			    // Handle For This Window
                  UINT	uMsg,			    // Message For This Window
                  WPARAM wParam,		    // Additional Message Information
                  LPARAM lParam)		    // Additional Message Information)
{
    sysControl->wParam = wParam;

    switch(uMsg)
    {
        sysControl->wParam = wParam;

        case WM_KEYDOWN:
            sysControl->keyPress(objectHierarchy[0]);
            break;
        case WM_KEYUP:
            sysControl->keyUp();
            break;
        case WM_MOUSEWHEEL:
            sysControl->mouseWheel(objectHierarchy[0], (double)GET_WHEEL_DELTA_WPARAM(wParam));
            break;
        case WM_LBUTTONDOWN:
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_RBUTTONDOWN:
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_MBUTTONDOWN:
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_LBUTTONUP:
            sysControl->mouseEventUp();
            break;
        case WM_RBUTTONUP:
            sysControl->mouseEventUp();
            break;
        case WM_MBUTTONUP:
            sysControl->mouseEventUp();
            break;
        case WM_MOUSEMOVE:
            sysControl->mouseMove(objectHierarchy[0], LOWORD(lParam), HIWORD(lParam));
            break;
    }
}

GLint Scene::initGL()   // Initalize Scene
{
    glShadeModel(GL_SMOOTH);                // Smooth Rendering
    glClearColor(0, 0, 0, 0);               // BG Color
    glClearDepth(2.0f);                     // Test Depth Layer
    glEnable(GL_DEPTH_TEST);                // Activate Depth Test
    glDepthFunc(GL_LEQUAL);                 // LEqual -> <=; Depth Function Type

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);                // Enables textures in the scene

    insertObject(1);

    insertLight();

    for(int i = 0; i < lights; i++)
    {
        switch(i + 1)
        {
            case 1:
                lightHierarchy[i]->setLight(GL_LIGHT0);  // One Light
                break;
            case 2:
                lightHierarchy[i]->setLight(GL_LIGHT1);  // Two
                break;
            case 3:
                lightHierarchy[i]->setLight(GL_LIGHT2);  // Three
                break;
            case 4:
                lightHierarchy[i]->setLight(GL_LIGHT3);  // Four
                break;
            case 5:
                lightHierarchy[i]->setLight(GL_LIGHT4); // Five
                break;
            case 6:
                lightHierarchy[i]->setLight(GL_LIGHT5); // Six
                break;
            case 7:
                lightHierarchy[i]->setLight(GL_LIGHT6); // Seven
                break;
            case 8:
                lightHierarchy[i]->setLight(GL_LIGHT7); // Eight
                break;
        }
    }

    return true;
}

GLint Scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();           // Clear Matrices

    objectHierarchy[0]->drawModel(1, 1, 1, 1);

    return true;

}

GLvoid Scene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width / height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspectRatio, 0.1, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Game Engine Functions

GLvoid Scene::insertObject(int sel)             // Inserts selected object into the scene; Tempory
{
    if(objects == 0)                            // If Hierarchy is empty create a new one
    {
        objectHierarchy = new _Models*[1];      // Create new hierarchy with one object in it
        objectHierarchy[0] = new _Models();     // New Model at first hierarchy
    }
    else                                        // If hierarchy is established increase it by one
    {
        _Models** temp = new _Models*[objects];

        for(int i = 0; i < objects; i++)        // Transfer objects to temp
            temp[i] = objectHierarchy[i];

        delete[] objectHierarchy;
        _Models** objectHierarchy = new _Models*[objects + 1];

        for(int i = 0; i < objects; i++)        // Transfer objects back to hierarchy
            objectHierarchy[i] = temp[i];

        delete[] temp;

        objectHierarchy[objects] = new _Models();
    }

    objects++;                                 // Objects in scene increased by one
}

GLvoid Scene::insertLight()             // Inserts selected object into the scene; Tempory
{
    if(lights == 0)                            // If Hierarchy is empty create a new one
    {
        lightHierarchy = new _LightSetup*[1];      // Create new hierarchy with one object in it
        lightHierarchy[0] = new _LightSetup();     // New Model at first hierarchy
    }
    else if(lights < 8)                                       // If hierarchy is established increase it by one; Less than 8
    {
        _LightSetup** temp = new _LightSetup*[lights];

        for(int i = 0; i < lights; i++)        // Transfer objects to temp
            temp[i] = lightHierarchy[i];

        delete[] lightHierarchy;
        _LightSetup** lightHierarchy = new _LightSetup*[lights + 1];

        for(int i = 0; i < lights; i++)        // Transfer objects back to hierarchy
            lightHierarchy[i] = temp[i];

        delete[] temp;

        lightHierarchy[lights] = new _LightSetup();
    }
    else
    {
        cout << "You can place no more lights! 8 Max" << endl;
    }

    lights++;                                 // Objects in scene increased by one
}
