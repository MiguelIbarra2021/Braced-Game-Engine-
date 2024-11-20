#include "_Camera.h"

_Camera::_Camera()
{
    //ctor
    radius = 100.0f; // Initial radius (distance from the target)
    angleX = 0.0f;   // Initial angle around the Y-axis
    angleY = 0.0f;   // Initial vertical angle

    mode = true;
}

_Camera::~_Camera()
{
    //dtor
}

GLvoid _Camera::camInit()
{
    // Initalize Camera
    eye.x = eye.y = eye.z = 0;
    des.x = 0; des.y = 0; des.z = 0;
    upVec.x = upVec.z = 0; upVec.y = 1;
}

GLvoid _Camera::setUpCam()
{
    eye.x = des.x + radius * cos(angleY) * sin(angleX);  // Calculate X
    eye.y = des.y + radius * sin(angleY);                // Calculate Y
    eye.z = des.z + radius * cos(angleY) * cos(angleX);  // Calculate Z

    // Set camera with values
    gluLookAt(eye.x, eye.y, eye.z,
              des.x, des.y, des.z,
              upVec.x, upVec.y, upVec.z);
}

GLvoid _Camera::orbitCamera(float deltaX, float deltaY)
{
    // Update angles based on input
    angleX += deltaX * 0.005f;
    angleY += deltaY * 0.005f;

    if (angleY > 1.5f) angleY = 1.5f;
    if (angleY < -1.5f) angleY = -1.5f;
}

void _Camera::updateViewDirection()
{
    float forwardX = cos(angleY) * sin(angleX);  // X component based on yaw and pitch
    float forwardY = sin(angleY);                 // Y component based only on pitch (up/down)
    float forwardZ = cos(angleY) * cos(angleX);  // Z component based on yaw and pitch

    // Set the eye position relative to the forward direction
    eye.x = forwardX;
    eye.y = forwardY;
    eye.z = forwardZ;

    // Set up the camera
    gluLookAt(eye.x, eye.y, eye.z,
              eye.x + forwardX, eye.y + forwardY, eye.z + forwardZ,  // Target point
              upVec.x, upVec.y, upVec.z); // Up vector
}
