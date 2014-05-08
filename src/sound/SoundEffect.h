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
protected:
    int channel;
    Mix_Chunk *sound;

public:
    SoundEffect(const std::string filepath);
    ~SoundEffect();
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual void loop(int loops) = 0;
};

#endif
