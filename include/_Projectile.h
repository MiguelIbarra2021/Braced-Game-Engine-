#ifndef _Projectile_H
#define _Projectile_H

#include "_Common.h"
#include "_TextureLoader.h"
#include "_ModelLoaderMD2.h"
#include "_Timer.h"


class _Projectile
{
    public:
        _Projectile();
        virtual ~_Projectile();

     _TextureLoader *tex = new _TextureLoader();
     _ModelLoaderMD2* mdl = new _ModelLoaderMD2();
     _Timer *myTime = new _Timer();

     rgb color;
     vec3 rot;
     vec3 pos;
     vec3 des;
     vec3 src; //source
     vec3 scale;

     char* model_file = nullptr;

     float t = 0.0; //parameter for the Projectile path
     int projectile_speed = 10;
     bool live = true;

     enum{READY, //ready to shoot
            DEAD, //Out of bounds or already hit
            SHOOT,
            HIT};

     void initProjectile(char*, char *);
     void drawProjectile(bool is_model);
     void ProjectileAction();

     int actionTrigger = READY;

    protected:

    private:
};

#endif // _Projectile_H
