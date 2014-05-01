#ifndef _MENU_SOUND_EFFECT_H_
#define _MENU_SOUND_EFFECT_H_

/**
 * Included files
 */
#include "SoundEffect.h"

class MenuSoundEffect : public SoundEffect {
public:
    static bool enabled;

    MenuSoundEffect(std::string filepath) : 
        SoundEffect(filepath) {
    } // constructor
    
    void play();
    void pause();
    void resume();
    void stop();
    void loop(int loops);
};

#endif
