#include "_Projectile.h"

_Projectile::_Projectile()
{
    //ctor
    color.r = 1.0;
    color.g = 1.0;
    color.b = 1.0;
}

_Projectile::~_Projectile()
{
    //dtor
}

void _Projectile::initProjectile(char* file, char* fileName)
{
    if(fileName != nullptr)
    {
        model_file = fileName;
        mdl->initModel(file, fileName);

        //cout << file << endl;
    }

    pos.x = 0; pos.y = 0; pos.z = 0;
    t = 0;
    des.x = 0; des.y = 20.0; des.z = -50.0;
    src.x = 0.0; src.y = 0.0; src.z = 0.0;
    live = false;
}

void _Projectile::drawProjectile(bool is_model)
{
    // Color
    glColor3f(color.r, color.g, color.b); // Custom rgb

    glPushMatrix();
        if(live)
        {
            glTranslatef(pos.x, pos.y, pos.z);
            glRotatef(rot.x, 1, 0, 0);
            glRotatef(rot.y, 0, 1, 0);
            glRotatef(rot.z, 0, 0, 1);

            if(is_model)
            {
                mdl->Draw();
                mdl->Actions();
            }
            else
                glutSolidSphere(0.5, 20, 20);
        }
    glPopMatrix();
}

void _Projectile::ProjectileAction()
{
    switch(actionTrigger)
    {
        case READY:
            pos.x=0.0; pos.y =0.0; pos.z=0.0;

            src.x = 0.0; src.y = 0.0; src.z = 0.0;
            live = false;
            t = 0;
            break;

        case DEAD:
            //live = 0; //false
            //t = 0;
            //actionTrigger = 0;
            mdl->actionTrigger = mdl->DEAD;

            des.x = pos.x;
            des.z = pos.z;
            des.y = pos.y - 100;

            if(clock() - myTime->startTime > 2)
                {
                    if(t < 1) t = 0.001; else actionTrigger = READY;
                    pos.x = src.x + t*(des.x - src.x);
                    pos.y = src.y + t*(des.y - src.y);
                    pos.z = src.z + t*(des.z - src.z);

                    src.x = pos.x; src.y = pos.y; src.z = pos.z;

                    myTime->startTime = clock();
                }

            break;

        case SHOOT:
            //live = true;
            if(live)
            {
                mdl->actionTrigger = mdl->FLY;

                if(clock() - myTime->startTime > projectile_speed)
                {
                    if(t < 1) t = 0.001; else actionTrigger = READY;
                    pos.x = src.x + t*(des.x - src.x);
                    pos.y = src.y + t*(des.y - src.y);
                    pos.z = src.z + t*(des.z - src.z);

                    src.x = pos.x; src.y = pos.y; src.z = pos.z;

                    myTime->startTime = clock();
                }
            }
            break;

        case HIT:
            //use this to show explosion or any other action
            break;
    }

}
