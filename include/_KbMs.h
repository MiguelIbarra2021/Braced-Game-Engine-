#ifndef _KBMS_H
#define _KBMS_H

#include <_Common.h>
#include <_Models.h>
#include <_Camera.h>

class _KbMs
{
    public:
        _KbMs();
        virtual ~_KbMs();

        WPARAM wParam;

        void keyPress(_Models *);

        // Special Key
        void keyPress(_Camera* cam);
        void keyPress(vec3* m_transform);
        void keyPress(bool* state);
        void keyPress();

        void keyUp();

        void mouseEventDown(double, double);
        void mouseEventUp();

        void mouseWheel(_Models *, double);
        void mouseMove(_Models *, double, double);

        double prev_MouseX;
        double prev_MouseY;

        double cPrev_MouseX;
        double cPrev_MouseY;

        bool mouseTranslation;
        bool mouseRotation;
        bool zRotation;

        double returnMouseX();
        double returnMouseY();

        POINT p;

    protected:

    private:
};

#endif // _KBMS_H
