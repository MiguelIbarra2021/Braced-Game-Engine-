#ifndef _SOUNDS_H
#define _SOUNDS_H

#include "SNDS/irrKlang.h"
#include "_Common.h"

using namespace irrklang;

class _Sounds
{
    public:
        _Sounds();
        virtual ~_Sounds();

        ISoundEngine *engine = createIrrKlangDevice();
        ISound* snd;

        void playMusic(char *);
        void playSound(char *);
        void pauseSound(char *);
        int initSounds();

    protected:

    private:
};

#endif // _SOUNDS_H
