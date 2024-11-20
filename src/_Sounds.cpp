#include "_Sounds.h"

_Sounds::_Sounds()
{
    //ctor
}

_Sounds::~_Sounds()
{
    //dtor
    engine->drop();
}

int _Sounds::initSounds()
{
    if(!engine)
    {
        cout << "ERROR: ***The sound Engine could not start*** \n";
        return 0; //if no good, quits game if no music
                    //fix in case if you want to play w/o music
    }
    return 1; //if all good

}

void _Sounds::playMusic(char *Filename)
{
    wav = engine->addSoundSourceFromFile(Filename);
    wav->setDefaultVolume(0.2f);
    //engine->setSoundVolume(0.02); //worked, but changed volume for all sounds... which makes sense from the name...
    engine->play2D(Filename, true); //file will repeat


}

void _Sounds::playSound(char *Filename)
{
    //if(!engine->isCurrentlyPlaying(Filename)){
        engine->play2D(Filename, false, false); //file will only play it once
    //}
}

void _Sounds::pauseSound(char *Filename)
{
    engine->play2D(Filename, true, false); //?
}

