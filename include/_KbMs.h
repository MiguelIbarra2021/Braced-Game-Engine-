#ifndef _KBMS_H
#define _KBMS_H

#include <_Common.h>
#include <_Models.h>

class _KbMs
{
    public:
        _KbMs();
        virtual ~_KbMs();

        WPARAM wParam;

        void keyPress(_Models *);
        void keyPress(vec3* position);
        void keyUp();

        void mouseEventDown(double, double);
        void mouseEventUp();

        void mouseWheel(_Models *, double);
        void mouseMove(_Models *, double, double);

        double prev_MouseX;
        double prev_MouseY;

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
