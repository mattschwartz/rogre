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
    ATTACK_MISS_1_SOUND = new SoundEffect("media/sound/attackMiss1.wav");
    MENU_SELECT_SOUND = new SoundEffect("media/sound/menuSelect.wav");
    AMBIANCE_RUMBLE_SOUND = new SoundEffect("media/sound/ambianceRumble.wav");
    
    menuSoundsEnabled = true;
    gameSoundsEnabled = true;
} // init

bool SoundManager::isMenuSoundEnabled() {
    return menuSoundsEnabled;
} // isMenuSoundEnabled

bool SoundManager::isGameSoundEnabled() {
    return gameSoundsEnabled;
} // isGameSoundEnabled

void SoundManager::pauseSounds() {
    gameSoundsEnabled = false;
    Mix_Pause(-1);
} // pauseSounds

void SoundManager::resumeSounds() {
    gameSoundsEnabled = true;
    Mix_Resume(-1);
} // resumeSounds

void SoundManager::resetSound() {
    Mix_HaltChannel(-1);
    gameSoundsEnabled = true;
    menuSoundsEnabled = true;
} // resetSound

void SoundManager::setGameSoundEnabled(bool enabled) {
    gameSoundsEnabled = enabled;

    if (gameSoundsEnabled) {
        Mix_Resume(-1);
    } // if
    else {
        Mix_Pause(-1);
    } // else
} // setGameSoundEnabled

void SoundManager::setMenuSoundEnabled(bool enabled) {
    menuSoundsEnabled = enabled;
} // setMenuSoundEnabled

void SoundManager::toggleGameSound() {
    gameSoundsEnabled = !gameSoundsEnabled;

    if (gameSoundsEnabled) {
        Mix_Resume(-1);
    } // if
    else {
        Mix_Pause(-1);
    } // else
} // toggleGameSound
