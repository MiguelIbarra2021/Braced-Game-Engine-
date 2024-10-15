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
        model->rotateX += 1.0;
        break;
    case VK_DOWN:
        model->rotateX -= 1.0;
        break;
    case VK_LEFT:
        model->rotateY += 1.0;
        break;
    case VK_RIGHT:
        model->rotateY -= 1.0;
        break;
    case VK_NUMPAD1:
        model->positionZ += 1.0;
        break;
    case VK_NUMPAD2:
        model->positionZ -= 1.0;
        break;
    case 0x57:  // W
        model->rotateX += 1.0;
        break;
    case 0x53:  // S
        model->rotateX -= 1.0;
        break;
    case 0x44:  // D
        model->rotateY += 1.0;
        break;
    case 0x41:  // A
        model->rotateY -= 1.0;
        break;
    case 0x51:  // Q Rotate +z
        model->rotateZ += 1.0;
        break;
    case 0x45:  // E Rotate -z
        model->rotateZ -= 1.0;
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
    model->positionZ += delta/100;
}

void _KbMs::mouseMove(_Models* model, double x, double y)
{
    if(mouseTranslation)
    {
        model->positionX += (x - prev_MouseX)/100.0;
        model->positionY -= (y - prev_MouseY)/100.0;
    }
    else if(mouseRotation)
    {
        model->rotateY += (x - prev_MouseX);
        model->rotateX += (y - prev_MouseY);
    }
    else if(zRotation)
    {
        model->rotateZ += (x - prev_MouseX);
    }

    prev_MouseX = x;
    prev_MouseY = y;
}

double _KbMs::returnMouseX()
{ return prev_MouseX; }

double _KbMs::returnMouseY()
{ return prev_MouseY; }
