#ifndef _COLLISION_H
#define _COLLISION_H

#include <_Common.h>

class _Collision
{
    public:
        _Collision();
        virtual ~_Collision();

        bool isLinearCollision(vec2, vec2);
        bool isRadialCollision(vec3, vec3, float, float, float);
        bool isHitPlane(vec2, vec2);

        bool isCubicCollision(vec3, vec3);
        bool isSphereCollision(vec3, vec3, float, float, float);
        bool isHitPlane3D(vec3, vec3);

    protected:

    private:
};

#endif // _COLLISION_H
