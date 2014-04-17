#ifndef _SOUND_EFFECT_H_
#define _SOUND_EFFECT_H_

/**
 * Included files
 */
#include <string>
#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_mixer.h>
#else
    #include "SDL/SDL.h"
    #include "SDL/SDL_mixer.h"
#endif

class SoundEffect {
private:
    int channel;
    Mix_Chunk *sound;

public:
    SoundEffect(const std::string filepath);
    ~SoundEffect();
    void play();
    void pause();
    void resume();
    void stop();
    void loop(int loops);
};

#endif
