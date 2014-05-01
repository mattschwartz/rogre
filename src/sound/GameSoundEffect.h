#ifndef _GAME_SOUND_EFFECT_H_
#define _GAME_SOUND_EFFECT_H_

/**
 * Included files
 */
#include "SoundEffect.h"

class GameSoundEffect : public SoundEffect {
private:
public:
    static bool enabled;

    GameSoundEffect(const std::string filepath) :
        SoundEffect(filepath) {
    } // constructor
    
    void play();
    void pause();
    void resume();
    void stop();
    void loop(int loops);
};

#endif
