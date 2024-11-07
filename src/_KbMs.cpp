#include "_KbMs.h"

_KbMs::_KbMs()
{
    //ctor

    // Mouse's previous position
    prev_MouseX = 0;
    prev_MouseY = 0;

    // Did mouse move
    mouseTranslation = false;
    mouseRotation = false;
    zRotation = false;
}

_KbMs::~_KbMs()
{
    //dtor
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

void _KbMs::keyPress(vec3* position)
{
    switch(wParam)
    {
        case VK_UP:
            position->y += 1.0;
            break;
        case VK_DOWN:
            position->y -= 1.0;
            break;
        case VK_LEFT:
            position->x += 1.0;
            break;
        case VK_RIGHT:
            position->x -= 1.0;
            break;
    }
}

void _KbMs::keyUp()
{
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
