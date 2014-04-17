/**
 * Included files
 */
#include "SoundManager.h"
#include "SoundEffect.h"

void SoundManager::init() {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Volume(-1, MIX_MAX_VOLUME);

    PLAYER_FOOTSTEP_SOUND = new SoundEffect("media/sound/footstep.wav");
    ATTACK_HIT_1_SOUND = new SoundEffect("media/sound/attackHit1.wav");
    ATTACK_MISS_1_SOUND = new SoundEffect("media/sound/attackMiss.wav");
    MENU_SELECT_SOUND = new SoundEffect("media/sound/menuSelect.wav");
    AMBIANCE_RUMBLE_SOUND = new SoundEffect("media/sound/ambianceRumble.wav");
    
    soundEnabled = true;
} // init

bool SoundManager::isSoundEnabled() {
    return soundEnabled;
} // isSoundEnabled

void SoundManager::toggleSound() {
    soundEnabled = !soundEnabled;

    if (soundEnabled) {
        PLAYER_FOOTSTEP_SOUND->resume();
        ATTACK_HIT_1_SOUND->resume();
        ATTACK_MISS_1_SOUND->resume();
        MENU_SELECT_SOUND->resume();
        AMBIANCE_RUMBLE_SOUND->resume();
    } // if
    else {
        PLAYER_FOOTSTEP_SOUND->pause();
        ATTACK_HIT_1_SOUND->pause();
        ATTACK_MISS_1_SOUND->pause();
        MENU_SELECT_SOUND->pause();
        AMBIANCE_RUMBLE_SOUND->pause();
    } // else
} // toggleSound
