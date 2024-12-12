#include "_Scene.h"

_LightSetup** lightHierarchy = nullptr;     // Allows for multiple seperate lights
_Models** objectHierarchy = nullptr;        // Hierarchy of objects
_KbMs* sysControl = new _KbMs();            // Mouse and Key Control
_TerrainGenerator* terrain = new _TerrainGenerator();
_Camera* camera = new _Camera();
_Collision* hit = new _Collision();
_Skybox* sky = nullptr;
_Skybox* skyboxes = new _Skybox[3];
_Skybox* sky1 = new _Skybox();
_Skybox* sky2 = new _Skybox();
_Skybox* sky3 = new _Skybox();
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
_Particles particleSystem[4]; // One particle system for each duck

int active_duck = 0;
int bullets_left = 2;

int mouseClicks;
int objects;                            // # of objects in Scene
int lights;                            // # of lights in Scene

float fogDensity = 0.005;

bool shot = false;

GLfloat fogColor[4];

Scene::Scene()
{
    // Initalize Variables
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth =   GetSystemMetrics(SM_CXSCREEN);

    fogColor[0] = 1.0;
    fogColor[1] = 1.0;
    fogColor[2] = 1.0;
    fogColor[3] = 1.0;

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

    // added this
    landingPage = new LandingPage();
    currentState = LANDING_PAGE;

    // fonts
    font = new _Fonts();
    //font->makeRasterFont(); // init raster font

    // init HUD vars
    shotsLeft = 2; // testing
    pointsHit = 0;
    pointsMissed = 0;

    // HUD
    hud = new _HUD();
    minutes = 1; // timer
    seconds = 30;
    lastTime = 0.0f;

    // timer
    gameTimer = new _Timer();
    //gameTimer->start(); // start the game timer, move it to init if not working

    // set for now
    int minutes = getMinutes();
    int seconds = getSeconds();
}

Scene::~Scene()
{
    delete lightHierarchy;
    delete objectHierarchy;
    delete sysControl;
    delete terrain;
    delete camera;
    delete hit;
    delete sky;
    delete snds;
    delete duck_timer;
    delete rnd;
    delete landingPage;
    delete font;
    delete hud;
    delete gameTimer;
    // delete all pointers
}

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
            // sysControl->wParam = wParam; // added this
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

            // added this, landing page stuff
            if (currentState == LANDING_PAGE && wParam == VK_RETURN) { currentState = MENU_PAGE; }

            if (currentState == MENU_PAGE) {
                if (wParam == 'N') { currentState = GAME_PLAY; }
                else if (wParam == 'H') { currentState = HELP_PAGE; }
                else if (wParam == 'E') { PostQuitMessage(0); }
                else if (wParam == 'T')
                { currentState = TEST_HUD;
                    //std::cout << "Switched to TEST_HUD state" << std::endl; // for debugging
                } // test HUD
            }

            if (currentState == HELP_PAGE && wParam == VK_ESCAPE) {
                currentState = MENU_PAGE; // Return to menu page
                return 0; // Stop further processing of this message
            }

            if (currentState == GAME_PLAY)
            {
                if (wParam == VK_ESCAPE)
                {
                    if (isPaused) {
                        resumeGame(); // Resume the game
                    } else {
                        pauseGame(); // Pause the game
                    }
                }
                else if (isPaused && VK_RETURN)
                {
                    PostQuitMessage(0); // Quit the game if Enter is pressed during pause
                }
                //isPaused = !isPaused; // Toggle pause state
                return 0; // Stop further processing of this message
            }

            break; // WM_KEYDOWN ends

        // modified this
        case WM_KEYUP:
            sysControl->wParam = wParam;
            sysControl->keyUp(); // Call the keyUp method to handle key releases
            break;

        case WM_MOUSEWHEEL:

            break;
        case WM_LBUTTONDOWN:
            sysControl->wParam = wParam;
            bMouseX = static_cast<float>(LOWORD(lParam)); // getting X-coord pos
            bMouseY = static_cast<float>(HIWORD(lParam)); // getting Y-coord pos
            //sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam)); // Map mouse coordinates
            mouseMapping(bMouseX, bMouseY); // Map mouse coordinates

            //std::cout << "MouseX after mouseMapping: " << mouseX << std::endl;
            //std::cout << "MouseY after mouseMapping: " << mouseY << std::endl;

            // debugging
            /*if (isBtn1Clicked()) { std::cout << "Button 1 has been clicked!" << std::endl; }
            if (isBtn2Clicked()) { std::cout << "Button 2 has been clicked!" << std::endl; }
            if (isBtn3Clicked()) { std::cout << "Button 3 has been clicked!" << std::endl; }*/

            sysControl->mouseEventDown(mouseX, mouseY);

            // added this
            if (currentState == LANDING_PAGE)
            {
                currentState = MENU_PAGE;
            }
            else if (currentState == MENU_PAGE)
            {
                if      (isBtn1Clicked()) { goToGamePlay(); }
                else if (isBtn2Clicked()) { showHelpPage(); }
                else if (isBtn3Clicked()) { exitApplication(); }
            }

            shot = true;
            break;  // WM_LBUTTONDOWN ends
        case WM_RBUTTONDOWN:
            //sysControl->wParam = wParam;
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_MBUTTONDOWN:
            sysControl->mouseEventDown(LOWORD(lParam), HIWORD(lParam));
            break;
        // bullets handled here with mouseclicks (src & des)
        case WM_LBUTTONUP:
            sysControl->mouseEventUp();

            if (bullets_left > 0 && !objectHierarchy[0]->mdl->In_Animation)
            {
                objectHierarchy[0]->mdl->actionTrigger = objectHierarchy[0]->mdl->SHOOT;

                // Assuming objectHierarchy[0] is the gun model
                gunBarrelPosition = objectHierarchy[0]->position;

                // Offset for the barrel (adjust as needed)
                gunBarrelOffset = { 0.5f, 0.0f, 0.0f }; // Example offset

                // Calculate bullet initial position
                bullets[mouseClicks].src.x = 0;
                bullets[mouseClicks].src.y = 0;
                bullets[mouseClicks].src.z = 0;

                // Calculate direction vector for the bullet
                vec3 bulletDirection;
                bulletDirection.x = mouseX - bullets[mouseClicks].src.x;
                bulletDirection.y = mouseY - bullets[mouseClicks].src.y;
                bulletDirection.z = mouseZ - bullets[mouseClicks].src.z;

                // Normalize the direction vector
                float length = sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y + bulletDirection.z * bulletDirection.z);
                bulletDirection.x /= length;
                bulletDirection.y /= length;
                bulletDirection.z /= length;

                // Set bullet destination based on direction and a multiplier for distance
                float distanceMultiplier = 2000.0f;
                bullets[mouseClicks].des.x = bullets[mouseClicks].src.x + bulletDirection.x * -distanceMultiplier;
                bullets[mouseClicks].des.y = bullets[mouseClicks].src.y + bulletDirection.y * distanceMultiplier;
                bullets[mouseClicks].des.z = bullets[mouseClicks].src.z + bulletDirection.z * -distanceMultiplier;

                bullets[mouseClicks].t = 0;
                bullets[mouseClicks].actionTrigger = bullets[mouseClicks].SHOOT;
                bullets[mouseClicks].live = true;

                snds->playSound("sounds/Shoot.mp3");

                bullets_left--;

                mouseClicks = (mouseClicks + 1) % 20;
            }

            if (shot)
            {
                shot = false;
            }

            break;
        case WM_RBUTTONUP:
            sysControl->mouseEventUp();
            break;
        case WM_MBUTTONUP:
            sysControl->mouseEventUp();
            break;
        case WM_MOUSEMOVE:
            sysControl->mouseTranslation = true;
            sysControl->mouseRotation = true;
            sysControl->mouseMove(hud, LOWORD(lParam), HIWORD(lParam));
            mouseMapping(LOWORD(lParam), HIWORD(lParam));
            break;


    }
    return 0; // added this
}

// added this **************** Bullets initial
void Scene::initBullets() {
    for (int i = 0; i < 20; i++) {
        bullets[i].initProjectile(nullptr, nullptr);
        bullets[i].projectile_speed = 1;
        bullets[i].live = false;
        bullets[i].pos = gunBarrelPosition; // Initialize position
    }
}


GLint Scene::initGL()   // Initalize Scene
{
    glShadeModel(GL_FLAT);                // Smooth Rendering
    glClearColor(0, 0, 0, 1.0);             // added this
    // glClearColor(0, 0, 0, 0);               // BG Color, original
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

    skyboxes[0].skyBoxInit("images/forestMorning.jfif");
    skyboxes[1].skyBoxInit("images/forestEvening.jfif");
    skyboxes[2].skyBoxInit("images/forestNight.jfif");

    sky = &skyboxes[0];

     // added this, menu and button textures
    landingPage->initPageTextures
    (
        (char*)"images/LPage.png",
        (char*)"images/MPage.png",
        (char*)"images/HPage.png",
        (char*)"images/PMenu.png",
        (char*)"images/New_Button.png",
        (char*)"images/Help_Button.png",
        (char*)"images/Exit_Button.png"
    );

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

    }
    else if (liveLevel13)
    {
        fogColor[0] = 0.0f;
        fogColor[1] = 0.0f;
        fogColor[2] = 0.0f;
        fogColor[3] = 0.5f;

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

    /* turned this off
    // Bullets ************************
    for(int i = 0; i < 20; i++)
    {
        bullets[i].initProjectile(nullptr, nullptr);
        bullets[i].projectile_speed = 1;
        bullets[i].live = false; // Ensure bullets are not live initially
    }
    */

    initBullets();

    // Ducks ****************************
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

    // init timers, can modify: original was => duck_timer->startTimer;
    duck_timer->initTimer();
    duck_timer->startTime = clock();

    font->makeRasterFont(); // init raster font
    hud->initFonts(); // init HUD fonts
    gameTimer->initTimer(); // start the game timer, move it to init if not working

    return true;
}

// modified this
// **************   DUCKS ********************
GLvoid Scene::initDuck()
{
    for(int i = 0; i < 4; i++)
    {
        ducks[i].projectile_speed = 15;
        ducks[i].actionTrigger = ducks[i].READY;
    }

    // Initialize Duck Launcher: Launch Position
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

    // Initialize Duck Launcher: Launch Rotation
    // Adjusted rotations to face forward
    lanRot[0].x = 0; // No tilt up or down
    lanRot[0].y = 0; // Face forward
    lanRot[0].z = 0; // No roll
    // Old values: lanRot[0].x = -20; lanRot[0].y = -10; lanRot[0].z = 20;

    lanRot[1].x = 0;
    lanRot[1].y = 0;
    lanRot[1].z = 0;
    // Old values: lanRot[1].x = -5; lanRot[1].y = -10; lanRot[1].z = 20;

    lanRot[2].x = 0;
    lanRot[2].y = 0;
    lanRot[2].z = 0;
    // Old values: lanRot[2].x = 5; lanRot[2].y = -10; lanRot[2].z = 20;

    lanRot[3].x = 0;
    lanRot[3].y = 0;
    lanRot[3].z = 0;
    // Old values: lanRot[3].x = 20; lanRot[3].y = -10; lanRot[3].z = 20;

    // Initialize Duck Launcher: Destination Position
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

// **********  Gun Position ***************
// also modified
GLvoid Scene::initShotgun() {
    insertObject("models/gun_color.png", "models/shotgun.md2");

    objectHierarchy[0]->mdl->actionTrigger = objectHierarchy[0]->mdl->IDLE;
    objectHierarchy[0]->mdl->In_Animation = false;

    objectHierarchy[0]->scale.x = 1;
    objectHierarchy[0]->scale.y = 1;
    objectHierarchy[0]->scale.z = 1;

    objectHierarchy[0]->position.z = 7;
    objectHierarchy[0]->position.y = -4;

    // Initial rotation to ensure the gun points towards the horizon
    objectHierarchy[0]->rotation.x = 0.0f; // No tilt up or down
    objectHierarchy[0]->rotation.y = 0.0f; // Rotate 180 degrees around Y-axis to point forward
    objectHierarchy[0]->rotation.z = 0.0f; // No roll
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

// Modified drawScene
GLint Scene::drawScene() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Ensure the alpha is set to 0 for transparency (Pause Menu)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();           // Clear Matrices

    wireFrame ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // added this

    // Lighting
    enableCelShading();

    // Edit Mode State //
    if(state_change)
    {
        t_switch();
    }

    glPushMatrix();
    switch (currentState) {
        case LANDING_PAGE:
            landingPage->drawLandingPage(screenWidth, screenHeight);
            break;

        case MENU_PAGE:
            glDisable(GL_LIGHTING); // Disable for text rendering
            glColor3f(1.0, 1.0, 1.0); // Keep original color
            landingPage->drawMenuPage(screenWidth, screenHeight);
            glEnable(GL_LIGHTING); // Re-enable after text rendering
            break;

        case HELP_PAGE:
            landingPage->drawHelpPage(screenWidth, screenHeight);
            break;

        case GAME_PLAY:
            sysControl->hideMouseCursor(); // hide mouse cursor

            camera->updateViewDirection(); // Camera

            if (!isPaused)
                GamePlay();

            // Always render the game scene
            GamePlay(); // Only this should render, not update logic

            glDisable(GL_FOG);

            if (isPaused)
            {
                //camera->updateViewDirection(); // Camera
                // Switch to orthogonal projection for the pause menu
                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                    glLoadIdentity();
                    gluOrtho2D(0, screenWidth, screenHeight, 0);

                    glMatrixMode(GL_MODELVIEW);

                    glPushMatrix();
                        glLoadIdentity();
                        // Enable blending for transparency
                        glEnable(GL_BLEND);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                        // Render the pause menu overlay
                        landingPage->drawPausePage(screenWidth, screenHeight);

                        // Restore the original projection
                        glDisable(GL_BLEND);
                        glMatrixMode(GL_PROJECTION);
                    glPopMatrix();

                    glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
            }

            RenderHUD(); // Draw the HUD
            glEnable(GL_FOG);

            break;
        case TEST_HUD: // state for testing HUD
            RenderHUD();
            break;

        default: // Exits
            break;
    }
    glPopMatrix();

    return true;
}

void Scene::GamePlay() {
    // Update and draw the gun model
    rotateTowards(&objectHierarchy[0]->rotation, nullptr);
    objectHierarchy[0]->mdl->Actions();
    objectHierarchy[0]->drawModel();

    // Get the updated gun barrel position after rotation
    gunBarrelPosition = objectHierarchy[0]->position;

    // Update and draw duck models
    for (int i = 0; i < 4; i++)
        if(ducks[i].actionTrigger == ducks[i].SHOOT)
            rotateDuck(&ducks[i].rot, desPos[i]);

    //cout << bullets[0].pos.x << " " << bullets[0].pos.y << " " << bullets[0].pos.z << endl;

    // Temp Reload
    if(bullets_left <= 0 && !objectHierarchy[0]->mdl->In_Animation)
    {
        objectHierarchy[0]->mdl->actionTrigger = objectHierarchy[0]->mdl->RELOAD;
        bullets_left = 2;
    }

    // Update projectiles
    for (int i = 0; i < 20; i++)
    {
        bullets[i].ProjectileAction(isPaused);
        //bullets[i].drawProjectile(false);
    }

    // World Generating
    terrain->drawTerrain();
    drawFoliage();

    // Update skybox if level has changed
    updateSkybox();

    // Draw the skybox
    sky->skyBoxDraw();

    // Update and draw particles for each duck
    for (int i = 0; i < 4; ++i)
    {
        particleSystem[i].update(0.016f); // Assuming 60 FPS
        particleSystem[i].draw();
    }

    // Test for duck collision
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(ducks[j].actionTrigger != ducks[j].DEAD && hit->isSphereCollision(bullets[i].pos, ducks[j].pos, 0.6, 1.4, 0.4))
            {
                Kill_Duck(j);
            }
        }
    }

    // Launch Ducks
    Automatic_Launcher();
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

    winZ = 1.0f; // Default depth (far plane)

    // Initialize mouse coordinates in world space
    mouseX = (GLfloat)(x - screenWidth / 2.0) / scale;
    mouseY = (GLfloat)(screenHeight / 2.0 - y) / scale;
    mouseZ = -100.0f;

    // Perform unprojection to get world coordinates
    gluUnProject(winX, winY, winZ, modelViewM, projectionM, viewPort, &mouseX, &mouseY, &mouseZ);
}

///////////////////////////
// Game Engine Functions //
///////////////////////////

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

// modified this
GLvoid Scene::rotateTowards(vec3* object, vec3* target)
{
    if (isPaused)
        return;

    float directionX = 0;
    float directionY = 0;
    float directionZ = 0;

    if (target == nullptr)
    {
        // Calculate the direction vector
        directionX = mouseX - object->x;
        directionY = object->y - mouseY; // Adjust to correct inversion
        //directionY = -(mouseY - object->y); // Invert the Y-axis
        directionZ = mouseZ - object->z;
    }
    else
    {
        // Calculate the direction vector
        directionX = target->x - object->x;
        directionY = object->y - target->y; // Adjust to correct inversion
        //directionY = -(target->y - object->y); // Invert the Y-axis
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
    vec3 forward = { 0.0f, 0.0f, -1.0f };

    // Calculate rotation axis using cross product
    vec3 axis =
    {
        forward.y * directionZ - forward.z * directionY,
        forward.z * directionX - forward.x * directionZ,
        forward.x * directionY - forward.y * directionX
    };

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

// added for duck rotation adjustment
GLvoid Scene::rotateDuck(vec3* duck, vec3 target)
{
    if (isPaused)
        return; // Skip updating rotation if the game is paused

    // Calculate the direction vector to follow their destination
    float directionX = target.x - duck->x;
    float directionY = target.y - duck->y;
    float directionZ = target.z - duck->z;

    // Normalize the direction vector
    float length = sqrt(directionX * directionX + directionY * directionY + directionZ * directionZ);
    if (length == 0) {
        return; // Avoid division by zero
    }
    directionX /= length;
    directionY /= length;
    directionZ /= length;

    // Assume default forward vector is (0, 0, 1) pointing forward
    vec3 forward = {0.0f, 0.0f, 1.0f};

    // Calculate rotation axis using cross product
    vec3 axis = {
        forward.y * directionZ - forward.z * directionY,
        forward.z * directionX - forward.x * directionZ,
        forward.x * directionY - forward.y * directionX
    };

    // Normalize axis
    float axisLength = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (axisLength != 0) {
        axis.x /= axisLength;
        axis.y /= axisLength;
        axis.z /= axisLength;
    }

    // Calculate rotation angle using dot product
    float dot = std::max(-1.0f, std::min(1.0f, forward.x * directionX + forward.y * directionY + forward.z * directionZ));
    float angle = acos(dot) * (180.0f / 3.1415926); // Convert to degrees

    // Update duck's rotation with a smooth transition
    duck->x = duck->x * 0.5f + axis.x * angle * 0.1f; // Adjust smoothing factor (0.9 and 0.1) as needed
    duck->y = duck->y * 0.9f + axis.y * angle * 0.1f;
    duck->z = duck->z * 0.9f + axis.z * angle * 0.1f;
}

GLvoid Scene::initFog()
{
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP2); // Choose a fog mode (e.g., GL_EXP, GL_EXP2, or GL_LINEAR)
    glFogfv(GL_FOG_COLOR, fogColor); // Use the fogColor with alpha
    glFogf(GL_FOG_DENSITY, fogDensity);    // Adjust density for desired thickness
    glHint(GL_FOG_HINT, GL_NICEST);  // Nicest quality
    glFogf(GL_FOG_START, 1.0f);      // Start distance (for GL_LINEAR)
    glFogf(GL_FOG_END, 100.0f);      // End distance (for GL_LINEAR)
}

GLvoid Scene::Automatic_Launcher()
{
    // if(clock() - duck_timer->startTime > 1000)
    if(clock() - duck_timer->startTime > 1000)
    {
        int i = rnd->pickNumber();

        cout << "spawned " << i << endl;

        if(ducks[i].pos.y < -20)
            ducks[i].actionTrigger = ducks[i].READY;

        if(ducks[i].pos.z > desPos[i].z - 30 || ducks[i].actionTrigger == ducks[i].READY)
            Launch_Duck(i);

        duck_timer->startTime = clock();
    }

    for(int i=0; i < 4; i++)
    {
        ducks[i].drawProjectile(true);
        ducks[i].ProjectileAction(isPaused);
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
    if(ducks[duck].actionTrigger != ducks[duck].DEAD)
    {
        cout << "killed " << duck << endl;

        ducks[duck].actionTrigger = ducks[duck].DEAD;
        ducks[duck].rot.x = 90;

        particleSystem[duck].init(ducks[duck].pos, "images/feathers.png");
        snds->playSound("sounds/duck_dying.mp3");

        pointsHit = pointsHit + 10;
    }
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
    if (pointsHit < 90)
    {
        fogColor[0] = 0.33f;
        fogColor[1] = 0.33f;
        fogColor[2] = 0.53f;
        fogColor[3] = 1.0f;

        fogDensity = 0.005;

        if(sky != &skyboxes[0])
        {
            initFog();
            sky = &skyboxes[0];
        }

        for(int i = 0; i < 4; i++)
            ducks[i].projectile_speed = 15;

    }
    else if (pointsHit < 150)
    {
        fogColor[0] = 0.8f;
        fogColor[1] = 0.5f;
        fogColor[2] = 0.5f;
        fogColor[3] = 0.5f;

        fogDensity = 0.01;

        if(sky != &skyboxes[1])
        {
            initFog();
            sky = &skyboxes[1];
        }

        for(int i = 0; i < 4; i++)
            ducks[i].projectile_speed = 10;
    }
    else if (pointsHit >= 190)
    {
        fogColor[0] = 0.0f;
        fogColor[1] = 0.0f;
        fogColor[2] = 0.0f;
        fogColor[3] = 0.5f;

        fogDensity = 0.02;

        if(sky != &skyboxes[2])
        {
            initFog();
            sky = &skyboxes[2];
        }

        for(int i = 0; i < 4; i++)
            ducks[i].projectile_speed = 5;
    }
}

// added this
// added this for button clicks:
GLboolean Scene::isBtn1Clicked()
{
    return ((mouseX >= btn1Xmin && mouseX <= btn1Xmax) && (mouseY <= btn1Ymin && mouseY >= btn1Ymax)) ? GL_TRUE : GL_FALSE;
}

GLboolean Scene::isBtn2Clicked()
{
    return ((mouseX >= btn2Xmin && mouseX <= btn2Xmax) && (mouseY <= btn2Ymin && mouseY >= btn2Ymax)) ? GL_TRUE : GL_FALSE;
}

GLboolean Scene::isBtn3Clicked()
{
    return ((mouseX >= btn3Xmin && mouseX <= btn3Xmax) && (mouseY <= btn3Ymin && mouseY >= btn3Ymax)) ? GL_TRUE : GL_FALSE;
}

// added all 3 methods for buttons functionality
void Scene::goToGamePlay()
{
    currentState = GAME_PLAY;
    std::cout << "Transitioning to Game Play state..." << std::endl;
}

void Scene::showHelpPage()
{
    currentState = HELP_PAGE;
    std::cout << "Transitioning to Help Page..." << std::endl;
}

void Scene::exitApplication()
{
    PostQuitMessage(0); // Exit the application
    std::cout << "Exiting application..." << std::endl;
}

void Scene::updateTimer()
{
    // may turn it off
    //gameTimer->stop(); // Update the timer by stopping it briefly

    double elapsedTime = gameTimer->getElapsedTime(); // Get the elapsed time in seconds
    //std::cout << "Elapsed time: " << elapsedTime << std::endl; // Debug output

    if (elapsedTime - lastTime >= 1.0f) // If a second has passed
    {
        lastTime = elapsedTime;
        if (seconds > 0)
        {
            seconds--;
        }
        else if (minutes > 0)
        {
            minutes--;
            seconds = 59;
        }
        else
        {
            currentState = LANDING_PAGE;

            minutes = 1;
            seconds = 30;
            bullets_left = 2;
            pointsHit = 0;

            initShotgun();
            initDuck();
            initBullets();
        }
        //std::cout << "Timer updated: " << minutes << ":" << seconds << std::endl; // Debug output
    }
    gameTimer->start(); // Restart the timer after updating
}

void Scene::RenderHUD() // use as template to work with drawHUD()
{
    // Save the current matrix mode and projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Set up an orthogonal projection
    gluOrtho2D(0, screenWidth, screenHeight, 0); // left, right, bottom, top
    glMatrixMode(GL_MODELVIEW); // Switch to modelview matrix

    glPushMatrix();
        glLoadIdentity();

        // Disable lighting and textures to avoid conflicts
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0, 0.0, 0.0); // Set text color to red for visibility

        // Update the timer
        updateTimer();

        // Get HUD-related data
        int ammo = getAmmo();
        int score = getScore();
        const char* notification = getNotification();

        // Render the HUD
        hud->draw(ammo, score, minutes, seconds, notification);

        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);

    // Restore the original modelview matrix
    glPopMatrix();

    // Restore the original projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

// getter methods
int Scene::GetShotsLeft()
{
    return shotsLeft;
}

int Scene::GetPointsHit()
{
    return pointsHit;
}

int Scene::GetPointsMissed()
{
    return pointsMissed;
}

int Scene::getAmmo() const { return bullets_left; } // Implement the logic to retrieve the ammo value
int Scene::getScore() const { return pointsHit; } // Implement the logic to retrieve the score value
int Scene::getMinutes() const { return 5; } // Implement the logic to retrieve the minutes value, can be used for start up
int Scene::getSeconds() const { return 30; } // Implement the logic to retrieve the seconds value, this can be use for start up
const char* Scene::getNotification() const { return "READY TO SHOOT!"; } // Implement the logic to retrieve the notification message

void Scene::pauseGame() {
     if (!isPaused) {
        // Save camera state
        savedViewDirectionX = camera->eye.x;
        savedViewDirectionY = camera->eye.y;
        savedViewDirectionZ = camera->eye.z;

        // Save game timer state
        savedStartTime = gameTimer->startTime;
        savedMinutes = minutes;
        savedSeconds = seconds;

        // Save gun state
        savedGunPosition = objectHierarchy[0]->position;
        savedGunRotation = objectHierarchy[0]->rotation;
        objectHierarchy[0]->mdl->actionTrigger = objectHierarchy[0]->mdl->IDLE;

        // Save ducks timer state
        savedDuckTimer = duck_timer->startTime;
        wasDuckTimerRunning = duck_timer->running;

        // Pause other game mechanics
        // Save state of ducks
        for (int i = 0; i < 4; i++) {
            savedDuckPositions[i] = ducks[i].pos;
            savedDuckRotations[i] = ducks[i].rot;
            savedDuckActions[i] = ducks[i].actionTrigger;
        }

        // Save state of bullets
        for (int i = 0; i < 20; i++) {
            savedBulletPositions[i] = bullets[i].pos;
            savedBulletLiveState[i] = bullets[i].live;
        }

        // Pause game timers
        savedGameTimer = clock();
        wasGameTimerRunning = gameTimer->running;

        if (gameTimer->running) { gameTimer->stop(); }

        if (duck_timer->running) { duck_timer->stop(); }

        // Pause any other relevant game mechanics, timers, etc.

        isPaused = true;
    }
}

void Scene::resumeGame() {
    if (isPaused) {
        // Restore camera state
        camera->eye.x = savedViewDirectionX;
        camera->eye.y = savedViewDirectionY;
        camera->eye.z = savedViewDirectionZ;

        // Restore gun state
        objectHierarchy[0]->position = savedGunPosition;
        objectHierarchy[0]->rotation = savedGunRotation;

        // Restore game timer state
        gameTimer->startTime = savedStartTime;
        minutes = savedMinutes;
        seconds = savedSeconds;

        // Restore ducks timer state
        duck_timer->startTime = savedDuckTimer;

        // Restore state of ducks
        for (int i = 0; i < 4; i++) {
            ducks[i].pos = savedDuckPositions[i];
            ducks[i].rot = savedDuckRotations[i];
            ducks[i].actionTrigger = savedDuckActions[i];
        }

        // Restore state of bullets
        for (int i = 0; i < 20; i++) {
            bullets[i].pos = savedBulletPositions[i];
            bullets[i].live = savedBulletLiveState[i];
        }

        // Resume game timers
        clock_t currentTime = clock();
        double elapsedPauseTime = (currentTime - savedGameTimer) / (double)CLOCKS_PER_SEC;

        gameTimer->startTime += elapsedPauseTime * CLOCKS_PER_SEC;
        duck_timer->startTime += elapsedPauseTime * CLOCKS_PER_SEC;

        if (wasGameTimerRunning) { gameTimer->start(); }
        if (wasDuckTimerRunning) { duck_timer->start(); }

        // Resume any other relevant game mechanics, timers, etc.

        isPaused = false;
    }
}
