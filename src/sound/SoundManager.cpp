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

    PLAYER_FOOTSTEP_SOUND->resume();
    MONSTER_BREATHING_1_SOUND->resume();
    MONSTER_BREATHING_2_SOUND->resume();
    MONSTER_BREATHING_3_SOUND->resume();
    MONSTER_BREATHING_4_SOUND->resume();
    ATTACK_HIT_1_SOUND->resume();
    ATTACK_MISS_1_SOUND->resume();
    MENU_SELECT_SOUND->resume();
    AMBIANCE_RUMBLE_SOUND->resume();
} // pauseSounds

void SoundManager::resumeSounds() {
    soundEnabled = true;

    PLAYER_FOOTSTEP_SOUND->pause();
    MONSTER_BREATHING_1_SOUND->pause();
    MONSTER_BREATHING_2_SOUND->pause();
    MONSTER_BREATHING_3_SOUND->pause();
    MONSTER_BREATHING_4_SOUND->pause();
    ATTACK_HIT_1_SOUND->pause();
    ATTACK_MISS_1_SOUND->pause();
    MENU_SELECT_SOUND->pause();
    AMBIANCE_RUMBLE_SOUND->pause();
} // resumeSounds

void SoundManager::toggleSound() {
    soundEnabled = !soundEnabled;

    if (soundEnabled) {
        resumeSounds();
    } // if
    else {
        pauseSounds();
    } // else
} // toggleSound
