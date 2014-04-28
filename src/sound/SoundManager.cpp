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
    MONSTER_BREATHING_1_SOUND = new SoundEffect("media/sound/monsterBreath1.wav");
    MONSTER_BREATHING_2_SOUND = new SoundEffect("media/sound/monsterBreath2.wav");
    MONSTER_BREATHING_3_SOUND = new SoundEffect("media/sound/monsterBreath3.wav");
    MONSTER_BREATHING_4_SOUND = new SoundEffect("media/sound/monsterBreath4.wav");
    ATTACK_HIT_1_SOUND = new SoundEffect("media/sound/attackHit1.wav");
    ATTACK_MISS_1_SOUND = new SoundEffect("media/sound/attackMiss.wav");
    MENU_SELECT_SOUND = new SoundEffect("media/sound/menuSelect.wav");
    AMBIANCE_RUMBLE_SOUND = new SoundEffect("media/sound/ambianceRumble.wav");
    
    soundEnabled = true;
} // init

bool SoundManager::isSoundEnabled() {
    return soundEnabled;
} // isSoundEnabled

void SoundManager::pauseSounds() {
    soundEnabled = false;
    Mix_Pause(-1);
} // pauseSounds

void SoundManager::resumeSounds() {
    soundEnabled = true;
    Mix_Resume(-1);
} // resumeSounds

void SoundManager::toggleSound() {
    soundEnabled = !soundEnabled;

    if (soundEnabled) {
        Mix_Resume(-1);
    } // if
    else {
        Mix_Pause(-1);
    } // else
} // toggleSound
