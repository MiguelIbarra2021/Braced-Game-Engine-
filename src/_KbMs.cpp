#include "_KbMs.h"

_KbMs::_KbMs()
{
    // Initalize Variables

    // Mouse's previous position
    prev_MouseX = 0;
    prev_MouseY = 0;

    cPrev_MouseX = 0;
    cPrev_MouseY = 0;

    // Did mouse move
    mouseTranslation = false;
    mouseRotation = false;
    zRotation = false;
}

_KbMs::~_KbMs()
{
    //dtor
}

void _KbMs::keyPress(_Camera* cam)
{
    switch(wParam)
    {
        // Orbital Camera
        case VK_UP:  // Up Arrow
            cam->mode = false;
            cam->angleY += 0.05;
            break;
        case VK_DOWN:  // Down Arrow
            cam->mode = false;
            cam->angleY -= 0.05;
            break;
        case VK_LEFT:  // Left Arrow
            cam->mode = false;
            cam->angleX -= 0.05;
            break;
        case VK_RIGHT:  // Right Arrow
            cam->mode = false;
            cam->angleX += 0.05;
            break;
        // FPS Camera
        case 0x57:  // W
            cam->mode = true;
            cam->angleY += 0.05;
            break;
        case 0x53:  // S
            cam->mode = true;
            cam->angleY -= 0.05;
            break;
        case 0x44:  // D
            cam->mode = true;
            cam->angleX -= 0.05;
            break;
        case 0x41:  // A
            cam->mode = true;
            cam->angleX += 0.05;
            break;
    }

    if(!cam->mode)
        cam->orbitCamera(0, 0);
}

void _KbMs::keyPress(_Models* model)
{
    switch(wParam)
    {
    case VK_UP:
        model->rotation.x += 1.0;
        break;
    case VK_DOWN:
        model->rotation.x -= 1.0;
        break;
    case VK_LEFT:
        model->rotation.y += 1.0;
        break;
    case VK_RIGHT:
        model->rotation.y -= 1.0;
        break;
    case VK_NUMPAD1:
        model->position.z += 1.0;
        break;
    case VK_NUMPAD2:
        model->position.z -= 1.0;
        break;
    case 0x57:  // W
        model->rotation.x += 1.0;
        break;
    case 0x53:  // S
        model->rotation.x -= 1.0;
        break;
    case 0x44:  // D
        model->rotation.y += 1.0;
        break;
    case 0x41:  // A
        model->rotation.y -= 1.0;
        break;
    case 0x51:  // Q Rotate +z
        model->rotation.z += 1.0;
        break;
    case 0x45:  // E Rotate -z
        model->rotation.z -= 1.0;
        break;
    }
}

void _KbMs::keyPress(bool* state)
{
    switch(wParam)
    {
        case VK_DECIMAL:
            *state = true;
            break;
    }
}

void _KbMs::keyPress(vec3* m_transform)
{
    switch(wParam)
    {
        case VK_UP:
            m_transform->y += 1.0;
            break;
        case VK_DOWN:
            m_transform->y -= 1.0;
            break;
        case VK_LEFT:
            m_transform->x -= 1.0;
            break;
        case VK_RIGHT:
            m_transform->x += 1.0;
            break;
    }
}

// Modified this
void _KbMs::keyUp() {
    // Reset states or handle specific key releases
    // Example: If a specific key is released, we can reset the state
    switch (wParam) {
        case VK_UP:
        case VK_DOWN:
        case VK_LEFT:
        case VK_RIGHT:
        case 0x57: // W
        case 0x53: // S
        case 0x44: // D
        case 0x41: // A
        case 0x51: // Q
        case 0x45: // E
            // Reset the state or stop the corresponding action
            // This could be custom logic based on your application needs
            // Example: Stop rotation or movement
            // You can add specific logic here
            break;
    }
}

void _KbMs::mouseEventDown(double x, double y)
{
    prev_MouseX = x;
    prev_MouseY = y;

    switch(wParam)
    {
    case MK_LBUTTON:
        mouseTranslation = true;
        break;
    case MK_RBUTTON:
        mouseRotation = true;
        break;
    case MK_MBUTTON:
        zRotation = true;
        break;
    }
}

void _KbMs::mouseEventUp()
{
    mouseTranslation = false;
    mouseRotation = false;
    zRotation = false;
}

void _KbMs::mouseWheel(_Models* model, double delta)
{
    model->position.z += delta/100;
}
/*
void _KbMs::mouseMove(_HUD* hud, double x, double y)
{
    if (mouseTranslation) {
        hud->mouseX += (x - prev_MouseX) / 100.0;
        hud->mouseY -= (y - prev_MouseY) / 100.0;
    } else if (mouseRotation) {
        hud->rotationY += (x - prev_MouseX);
        hud->rotationX += (y - prev_MouseY);
    }

    prev_MouseX = x;
    prev_MouseY = y;

    // Debug output for mouse position
    std::cout << "Mouse Move - X: " << x << ", Y: " << y << std::endl;
    std::cout << "HUD Mouse Position - X: " << hud->mouseX << ", Y: " << hud->mouseY << std::endl;
}
*/

// +++++++++++ added +++++++++++++++++++++++++++
void _KbMs::mouseMove(_HUD* hud, double x, double y)
{
    hud->mouseX = x;
    hud->mouseY = y;

    prev_MouseX = x;
    prev_MouseY = y;

    // Debug output for mouse position
    //std::cout << "Mouse Move - X: " << x << ", Y: " << y << std::endl;
    //std::cout << "HUD Mouse Position - X: " << hud->mouseX << ", Y: " << hud->mouseY << std::endl;
}
// +++++++++++++++++++ added ++++++++++++++++++++++++++

void _KbMs::mouseMove(_Models* model, double x, double y)
{
    if(mouseTranslation)
    {
        model->position.x += (x - prev_MouseX)/100.0;
        model->position.y -= (y - prev_MouseY)/100.0;
    }
    else if(mouseRotation)
    {
        model->rotation.y += (x - prev_MouseX);
        model->rotation.x += (y - prev_MouseY);
    }
    else if(zRotation)
    {
        model->rotation.z += (x - prev_MouseX);
    }

    prev_MouseX = x;
    prev_MouseY = y;
}

double _KbMs::returnMouseX()
{ return prev_MouseX; }

double _KbMs::returnMouseY()
{ return prev_MouseY; }

// added this for HUD
/*
POINT _KbMs::getMousePosition()
{
    GetCursorPos(&p); // Get the cursor position in screen coordinates
    ScreenToClient(GetActiveWindow(), &p); // Convert to window coordinates
    return p;
}
*/

// +++++++++++ added +++++++++++++++++++++++++++++++++++
void _KbMs::hideMouseCursor()
{
    ShowCursor(FALSE); // hide the default mouse cursor
}

void _KbMs::showMouseCursor()
{
    ShowCursor(TRUE); // Show the default mouse cursor
}
// +++++++++++++ added +++++++++++++++++++++++++++++++
