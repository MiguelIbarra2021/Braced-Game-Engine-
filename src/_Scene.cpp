#include "_Scene.h"

_LightSetup** lightHierarchy = nullptr;     // Allows for multiple seperate lights
_Models** objectHierarchy = nullptr;        // Hierarchy of objects
_KbMs* sysControl = new _KbMs();            // Mouse and Key Control
_TerrainGenerator* terrain = new _TerrainGenerator();
_Camera* camera = new _Camera();
_Collision* hit = new _Collision();
_Skybox* sky = new _Skybox();
_Sounds *snds = new _Sounds();
_Timer* duck_timer = new _Timer();
_RandomNumber* rnd = new _RandomNumber();

// Shotgun
_Projectile bullets[20];

// Target Ducks
vec3 desPos[4];   // Destination
vec3 lanPos[4];   // Launch Position
vec3 lanRot[4];   // Launch Rotation
vec3 downPos;
_Projectile ducks[4];

int active_duck = 0;
int bullets_left = 2;

int mouseClicks;
int objects;                            // # of objects in Scene
int lights;                            // # of lights in Scene

bool shot = false;

GLfloat fogColor[4];

Scene::Scene()
{
    // Initalize Variables
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth =   GetSystemMetrics(SM_CXSCREEN);

    mouseClicks = 0;
    objects = 0;
    lights = 0;
    editmode = false;

    state_change = false;
    transform_trigger = TRANSFORM;

    initDuck();

    doneLoading = false;
    liveLevel11 = true;
    liveLevel12 = false;
    liveLevel13 = false;
}

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

            sysControl->keyPress(camera);
            sysControl->keyPress(&state_change);

            ////////////////////////////////////////////////////////////////////////
            if(editmode)    // On Activation You Can Edit Objects In Scene & Save It
            {
                switch(transform_trigger)
                {
                    case TRANSFORM:
                        sysControl->keyPress(&objectHierarchy[0]->position);
                        break;
                    case ROTATE:
                        sysControl->keyPress(&objectHierarchy[0]->rotation);
                        break;
                    case SCALE:
                        sysControl->keyPress(&objectHierarchy[0]->scale);
                        break;
                }
            }

            // keyboard cases to switch levels
            switch (wParam)
            {
            case 0x31: // Key '1'
                liveLevel11 = true;
                liveLevel12 = false;
                liveLevel13 = false;
                break;
            case 0x32: // Key '2'
                liveLevel11 = false;
                liveLevel12 = true;
                liveLevel13 = false;
                break;
            case 0x33: // Key '3'
                liveLevel11 = false;
                liveLevel12 = false;
                liveLevel13 = true;
                break;
            }

            ////////////////////////////////////////////////////////////////////////

            break;
        case WM_KEYUP:

            break;
        case WM_MOUSEWHEEL:

            break;
        case WM_LBUTTONDOWN:
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));

            shot = true;
            break;
        case WM_RBUTTONDOWN:
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_MBUTTONDOWN:
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_LBUTTONUP:
            sysControl->mouseEventUp();

            if(bullets_left > 0 && !objectHierarchy[0]->mdl->In_Animation)
            {
                objectHierarchy[0]->mdl->actionTrigger = objectHierarchy[0]->mdl->SHOOT;

                bullets[mouseClicks].src.x = objectHierarchy[0]->position.x;
                bullets[mouseClicks].src.y = objectHierarchy[0]->position.y;
                bullets[mouseClicks].src.z = objectHierarchy[0]->position.z;

                bullets[mouseClicks].des.x = mouseX;
                bullets[mouseClicks].des.y = mouseY;
                bullets[mouseClicks].des.z = mouseZ;

                bullets[mouseClicks].t = 0;
                bullets[mouseClicks].actionTrigger = bullets[mouseClicks].SHOOT;
                bullets[mouseClicks].live = true;
                mouseClicks = (mouseClicks+1)%20;

                snds->playSound("sounds/Shoot.mp3");

                bullets_left--;
            }

            if(shot)
                shot = false;
            break;
        case WM_RBUTTONUP:
            sysControl->mouseEventUp();
            break;
        case WM_MBUTTONUP:
            sysControl->mouseEventUp();
            break;
        case WM_MOUSEMOVE:
            mouseMapping(LOWORD(lParam), HIWORD(lParam));
            break;


    }
}

GLint Scene::initGL()   // Initalize Scene
{
    glShadeModel(GL_FLAT);                // Smooth Rendering
    glClearColor(0, 0, 0, 0);               // BG Color
    glClearDepth(2.0f);                     // Test Depth Layer
    glEnable(GL_DEPTH_TEST);                // Activate Depth Test
    glDepthFunc(GL_LEQUAL);                 // LEqual -> <=; Depth Function Type

    glEnable(GL_COLOR_MATERIAL);

    // Textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);   // PNG alpha

    glEnable(GL_TEXTURE_2D);  //enable textures

    // World
    initFog();

    terrain->initTerrain("images/grass_base.jpg");   // Water?
    terrain->scale.x = 200;
    terrain->scale.y = 1;
    terrain->scale.z = 200;
    terrain->position.z = 40;
    terrain->position.y = -6;

    // Shotgun Model
    initShotgun();

    // Initialize the appropriate skybox texture
    if (liveLevel11)
    {
        fogColor[0] = 1.0f;
        fogColor[1] = 1.0f;
        fogColor[2] = 1.0f;
        fogColor[3] = 0.5f;
        sky->skyBoxInit("images/forestMorning.jfif");
        sky->scale.x = 1000;
        sky->scale.y = 1000;
        sky->scale.z = 1000;

    }
    else if (liveLevel12)
    {
        fogColor[0] = 0.8f;
        fogColor[1] = 0.5f;
        fogColor[2] = 0.5f;
        fogColor[3] = 0.5f;
        sky->skyBoxInit("images/forestEvening.jfif");
    }
    else if (liveLevel13)
    {
        fogColor[0] = 0.0f;
        fogColor[1] = 0.0f;
        fogColor[2] = 0.0f;
        fogColor[3] = 0.5f;
        sky->skyBoxInit("images/forestNight.jfif");
    }

    // Duck Model
    insertObject("models/duck/Duck.png", "models/duck/d.md2");

    // Foliage
    //insertObject("C:\Github\Braced-Game-Engine-\models\bushes\texture_gradient.png", "models/bushes/forest_nature_set_all_in.md2");
    insertObject("models/bushes/texture_gradient.png.002.jpg", "models/bushes/ah.md2");
    insertObject("models/bushes/texture_gradient.png.002.jpg", "models/bushes/ah.md2");

    insertObject("models/bushes/texture_gradient.png.002.jpg", "models/trees/tris.md2");
    insertObject("models/bushes/texture_gradient.png.002.jpg", "models/trees/tris.md2");

    initFoliage();

    // Bullets
    for(int i = 0; i < 20; i++)
    {
        bullets[i].initProjectile(nullptr, nullptr);
        bullets[i].projectile_speed = 1;
    }

    // Ducks

    rnd->initializeNumbers(0, 4);

    for(int i = 0; i < 4; i++)
    {
        ducks[i].initProjectile("models/duck/Duck.png", "models/duck/d.md2");
        ducks[i].mdl->actionTrigger = ducks[i].mdl->FLY;
        ducks[i].mdl->Actions();
    }

    // Initalize Lights
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

    // Camera
    camera->camInit();

    snds->initSounds();
    //snds->playMusic("C:/Users/user/Desktop/CSCI 191/Braced-Game-Engine-/sounds/Sonic Riders Zero Gravity Main Menu Theme.mp3");
    snds->playMusic("sounds/Super Smash Bros. 4 For Wii U OST - Duck Hunt Medley.mp3");

    return true;
}

GLvoid Scene::initDuck()
{
    // Initalize Duck Launcher: Launch Position
    lanPos[0].x = 20;
    lanPos[0].y = -20;
    lanPos[0].z = 40;

    lanPos[1].x = 10;
    lanPos[1].y = -20;
    lanPos[1].z = 40;

    lanPos[2].x = -10;
    lanPos[2].y = -20;
    lanPos[2].z = 40;

    lanPos[3].x = -20;
    lanPos[3].y = -20;
    lanPos[3].z = 40;

    // Initalize Duck Launcher: Launch Rotation
    lanRot[0].x = -20;
    lanRot[0].y = -10;
    lanRot[0].z = 20;

    lanRot[1].x = -5;
    lanRot[1].y = -10;
    lanRot[1].z = 20;

    lanRot[2].x = 5;
    lanRot[2].y = -10;
    lanRot[2].z = 20;

    lanRot[3].x = 20;
    lanRot[3].y = -10;
    lanRot[3].z = 20;

    // Initalize Duck Launcher: Destination Position
    desPos[0].x = 15;
    desPos[0].y = 100;
    desPos[0].z = 100;

    desPos[1].x = 5;
    desPos[1].y = 100;
    desPos[1].z = 100;

    desPos[2].x = -5;
    desPos[2].y = 100;
    desPos[2].z = 100;

    desPos[3].x = -15;
    desPos[3].y = 100;
    desPos[3].z = 100;
}


GLvoid Scene::initShotgun()
{
    insertObject("models/gun_color.png", "models/shotgun.md2");
    objectHierarchy[0]->mdl->actionTrigger = objectHierarchy[0]->mdl->IDLE;

    objectHierarchy[0]->scale.x = 1;
    objectHierarchy[0]->scale.y = 1;
    objectHierarchy[0]->scale.z = 1;

    objectHierarchy[0]->position.z = 7;
    objectHierarchy[0]->position.y = -4;
}

void Scene::enableCelShading() {
    // Setup lighting for cel shading
    GLfloat lightPos[] = { 0.0f, 1.0f, 1.0f, 0.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    // Set material properties
    GLfloat materialColor[] = { 1.0f, 0.5f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
}

GLint Scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();           // Clear Matrices

    // Lighting
    enableCelShading();

    // Edit Mode State //
    if(state_change)
        t_switch();

    // Camera
    camera->updateViewDirection();

    // Scene
    rotateTowards(&objectHierarchy[0]->rotation, nullptr);
    objectHierarchy[0]->mdl->Actions();
    objectHierarchy[0]->drawModel();

    // Temp Reload
    if(bullets_left <= 0 && !objectHierarchy[0]->mdl->In_Animation)
    {
        objectHierarchy[0]->mdl->actionTrigger = objectHierarchy[0]->mdl->RELOAD;
        bullets_left = 2;
    }

    // Duck Debug
    objectHierarchy[1]->mdl->actionTrigger = objectHierarchy[1]->mdl->FLY;
    objectHierarchy[1]->mdl->Actions();
    objectHierarchy[1]->drawModel();

    // World Generating
    terrain->drawTerrain();
    drawFoliage();

    // Update skybox if level has changed
    updateSkybox();

    // Draw the skybox
    sky->skyBoxDraw();

    // Test for duck collision
    for(int i=0; i < 20; i++)
    {
        for(int j = 0; j < 4; j++)
            if(hit->isSphereCollision(bullets[i].pos, ducks[j].pos, 0.6, 1.4, 0.4))
                Kill_Duck(j);

        bullets[i].drawProjectile(false);
        bullets[i].ProjectileAction();
    }

    // Launch Ducks
    Automatic_Launcher();

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

// Temp Positon
GLvoid Scene::mouseMapping(int x, int y) // x & y are mouse coords
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);

    GLint viewPort[4];
    GLdouble modelViewM[16];
    GLdouble projectionM[16];
    GLfloat winX, winY, winZ;

    float scale = 60 * (screenWidth / screenHeight); // Adjust for screen aspect ratio

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewM); // Get ModelView matrix
    glGetDoublev(GL_PROJECTION_MATRIX, projectionM); // Get Projection matrix
    glGetIntegerv(GL_VIEWPORT, viewPort); // Get Viewport dimensions

    winX = (GLfloat)x;
    winY = (GLfloat)(viewPort[3] - y);

    // Read depth value at the current mouse position
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    // Depth thresholding to ignore unintended objects
    if (winZ < 0.01f || winZ > 0.99f) {
        // Ignore out-of-range depth values
        winZ = 1.0f; // Default depth (far plane)
    }

    // Initialize mouse coordinates in world space
    mouseX = (GLfloat)(x - screenWidth / 2.0) / scale;
    mouseY = (GLfloat)(screenHeight / 2.0 - y) / scale;
    mouseZ = -100.0f;

    // Perform unprojection to get world coordinates
    gluUnProject(winX, winY, winZ, modelViewM, projectionM, viewPort, &mouseX, &mouseY, &mouseZ);
}


// Game Engine Functions

GLvoid Scene::insertObject(char* tex_file, char* mdl_file)             // Inserts selected object into the scene; Tempory
{
    if(objects == 0)                            // If Hierarchy is empty create a new one
    {
        objectHierarchy = new _Models*[1];      // Create new hierarchy with one object in it
        objectHierarchy[0] = new _Models();     // New Model at first hierarchy

        objectHierarchy[0]->initModel(tex_file, mdl_file);
    }
    else                                        // If hierarchy is established increase it by one
    {
        _Models** temp = new _Models*[objects];

        for(int i = 0; i < objects; i++)        // Transfer objects to temp
            temp[i] = objectHierarchy[i];

        delete[] objectHierarchy;
        objectHierarchy = new _Models*[objects + 1];

        for(int i = 0; i < objects; i++)        // Transfer objects back to hierarchy
            objectHierarchy[i] = temp[i];

        delete[] temp;

        objectHierarchy[objects] = new _Models();

        objectHierarchy[objects]->initModel(tex_file, mdl_file);
    }

    objects++;                                 // Objects in scene increased by one
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

GLvoid Scene::t_switch()
{
    transform_trigger = static_cast<mode>((transform_trigger + 1) % (SCALE + 1));
    state_change = false;
}

GLvoid Scene::rotateTowards(vec3* object, vec3* target)
{
    float directionX = 0;
    float directionY = 0;
    float directionZ = 0;

    if(target == nullptr)
    {
        // Calculate the direction vector
        directionX = mouseX - object->x;
        directionY = mouseY - object->y;
        directionZ = mouseZ - object->z;
    }
    else
    {
        // Calculate the direction vector
        directionX = target->x - object->x;
        directionY = target->y - object->y;
        directionZ = target->z - object->z;
    }

    // Normalize the direction vector
    float length = sqrt(directionX * directionX + directionY * directionY + directionZ * directionZ);

    if (length == 0)
        return; // Avoid division by zero

    directionX /= length;
    directionY /= length;
    directionZ /= length;

    // Assume default forward vector is (0, 0, -1)
    vec3 forward = { 0.0f, 0.0f, 1.0f };

    // Calculate rotation axis using cross product
    vec3 axis = {forward.y * directionZ - forward.z * directionY,
                 forward.z * directionX - forward.x * directionZ,
                 forward.x * directionY - forward.y * directionX};

    // Normalize axis
    float axisLength = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);

    if (axisLength != 0)
    {
        axis.x /= axisLength;
        axis.y /= axisLength;
        axis.z /= axisLength;
    }

    // Calculate rotation angle using dot product
    float dot = std::max(-1.0f, std::min(1.0f, forward.x * directionX + forward.y * directionY + forward.z * directionZ));
    float angle = acos(dot) * (180.0f / 3.1415926); // Convert to degrees

    // Update object's rotation (assuming object has a rotation field)
    object->x = axis.x * angle;
    object->y = axis.y * angle;
    object->z = axis.z * angle;
}

GLvoid Scene::initFog()
{
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP2); // Choose a fog mode (e.g., GL_EXP, GL_EXP2, or GL_LINEAR)
    glFogfv(GL_FOG_COLOR, fogColor); // Use the fogColor with alpha
    glFogf(GL_FOG_DENSITY, 0.005f);    // Adjust density for desired thickness
    glHint(GL_FOG_HINT, GL_NICEST);  // Nicest quality
    glFogf(GL_FOG_START, 1.0f);      // Start distance (for GL_LINEAR)
    glFogf(GL_FOG_END, 100.0f);      // End distance (for GL_LINEAR)
}

GLvoid Scene::Automatic_Launcher()
{
    if(clock() - duck_timer->startTime > 1000)
    {
        int i = rnd->pickNumber();

        if(ducks[i].pos.y < -20)
            ducks[i].actionTrigger = ducks[i].READY;

        if(ducks[i].pos.z > desPos[i].z - 30 || ducks[i].actionTrigger == ducks[i].READY)
            Launch_Duck(i);

        duck_timer->startTime = clock();
    }

    for(int i=0; i < 4; i++)
    {
        ducks[i].drawProjectile(true);
        ducks[i].ProjectileAction();
    }
}

GLvoid Scene::Launch_Duck(int current_duck)
{
    rotateTowards(&lanRot[current_duck], &desPos[current_duck]);

    ducks[current_duck].src.x = lanPos[current_duck].x;
    ducks[current_duck].src.y = lanPos[current_duck].y;
    ducks[current_duck].src.z = lanPos[current_duck].z;

    ducks[current_duck].rot.x = lanRot[current_duck].x;
    ducks[current_duck].rot.y = lanRot[current_duck].y;
    ducks[current_duck].rot.z = lanRot[current_duck].z;

    ducks[current_duck].des.x = desPos[current_duck].x;
    ducks[current_duck].des.y = desPos[current_duck].y;
    ducks[current_duck].des.z = desPos[current_duck].z;

    ducks[current_duck].t = 0;

    ducks[current_duck].actionTrigger = ducks[current_duck].SHOOT;

    ducks[current_duck].live = true;

    snds->playSound("sounds/Duck_Quack.mp3");
}

GLvoid Scene::Kill_Duck(int duck)
{
    ducks[duck].actionTrigger = ducks[active_duck].DEAD;
    ducks[duck].rot.x = 90;

    snds->playSound("sounds/duck_dying.mp3");
}

GLvoid Scene::initFoliage()
{
    /////////////////////////////////////////////////
    // Bushes
    /////////////////////////////////////////////////
    objectHierarchy[2]->position.x = -15;
    objectHierarchy[2]->position.y = -5;
    objectHierarchy[2]->position.z = 0;

    objectHierarchy[2]->scale.x = 1;
    objectHierarchy[2]->scale.y = 1;
    objectHierarchy[2]->scale.z = 1;

    objectHierarchy[3]->position.x = -25;
    objectHierarchy[3]->position.y = -5;
    objectHierarchy[3]->position.z = 0;

    objectHierarchy[3]->scale.x = 1;
    objectHierarchy[3]->scale.y = 1;
    objectHierarchy[3]->scale.z = 1;
    /////////////////////////////////////////////////
    // Trees
    /////////////////////////////////////////////////
    objectHierarchy[4]->position.x = -90;
    objectHierarchy[4]->position.y = -5;
    objectHierarchy[4]->position.z =100;

    objectHierarchy[4]->scale.x = 2;
    objectHierarchy[4]->scale.y = 2;
    objectHierarchy[4]->scale.z = 2;

    objectHierarchy[5]->position.x = 10;
    objectHierarchy[5]->position.y = -5;
    objectHierarchy[5]->position.z = 100;

    objectHierarchy[5]->scale.x = 2;
    objectHierarchy[5]->scale.y = 2;
    objectHierarchy[5]->scale.z = 2;
    /////////////////////////////////////////////////
}

GLvoid Scene::drawFoliage()
{
    /////////////////////////////////////////////////
    // Bushes
    /////////////////////////////////////////////////
    objectHierarchy[2]->drawModel();
    objectHierarchy[3]->drawModel();

    /////////////////////////////////////////////////
    // Trees
    /////////////////////////////////////////////////
    objectHierarchy[4]->drawModel();
    objectHierarchy[5]->drawModel();
}

GLvoid Scene::updateSkybox()
{
    if (liveLevel11)
    {
        initFog();

        fogColor[0] = 0.33f;
        fogColor[1] = 0.33f;
        fogColor[2] = 0.53f;
        fogColor[3] = 1.0f;
        sky->skyBoxInit("images/forestMorning.jfif");

    }
    else if (liveLevel12)
    {
        initFog();

        fogColor[0] = 0.8f;
        fogColor[1] = 0.5f;
        fogColor[2] = 0.5f;
        fogColor[3] = 0.5f;
        sky->skyBoxInit("images/forestEvening.jfif");
    }
    else if (liveLevel13)
    {
        initFog();

        fogColor[0] = 0.0f;
        fogColor[1] = 0.0f;
        fogColor[2] = 0.0f;
        fogColor[3] = 0.5f;
        sky->skyBoxInit("images/forestNight.jfif");
    }
}
