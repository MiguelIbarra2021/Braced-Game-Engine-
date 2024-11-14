#ifndef _SHOTGUN_H
#define _SHOTGUN_H

#include "_Common.h"
#include "_Models.h"

class _Shotgun
{
    public:
        _Shotgun();
        virtual ~_Shotgun();

        GLvoid pointTowardsMouse(_Models* model, vec3* rotation);

    protected:

    private:
};

#endif // _SHOTGUN_H
