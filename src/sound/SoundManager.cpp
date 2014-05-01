/**
 * Included files
 */
#include "SoundManager.h"
#include "SoundEffect.h"
#include "GameSoundEffect.h"
#include "MenuSoundEffect.h"

bool GameSoundEffect::enabled = true;
bool MenuSoundEffect::enabled = true;

void SoundManager::init() {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Volume(-1, MIX_MAX_VOLUME);

    PLAYER_FOOTSTEP_SOUND = new GameSoundEffect("media/sound/footstep.wav");
    MONSTER_BREATHING_1_SOUND = new GameSoundEffect("media/sound/monsterBreath1.wav");
    MONSTER_BREATHING_2_SOUND = new GameSoundEffect("media/sound/monsterBreath2.wav");
    MONSTER_BREATHING_3_SOUND = new GameSoundEffect("media/sound/monsterBreath3.wav");
    MONSTER_BREATHING_4_SOUND = new GameSoundEffect("media/sound/monsterBreath4.wav");
    ATTACK_HIT_1_SOUND = new GameSoundEffect("media/sound/attackHit1.wav");
    ATTACK_MISS_1_SOUND = new GameSoundEffect("media/sound/attackMiss1.wav");
    MENU_SELECT_SOUND = new MenuSoundEffect("media/sound/menuSelect.wav");
    AMBIANCE_RUMBLE_SOUND = new GameSoundEffect("media/sound/ambianceRumble.wav");
    
    gameSoundEffects.push_back(PLAYER_FOOTSTEP_SOUND);
    gameSoundEffects.push_back(MONSTER_BREATHING_1_SOUND);
    gameSoundEffects.push_back(MONSTER_BREATHING_2_SOUND);
    gameSoundEffects.push_back(MONSTER_BREATHING_3_SOUND);
    gameSoundEffects.push_back(MONSTER_BREATHING_4_SOUND);
    gameSoundEffects.push_back(ATTACK_HIT_1_SOUND);
    gameSoundEffects.push_back(ATTACK_MISS_1_SOUND);
    gameSoundEffects.push_back(AMBIANCE_RUMBLE_SOUND);
    menuSoundEffects.push_back(MENU_SELECT_SOUND);
} // init

bool SoundManager::isMenuSoundEnabled() {
    return MenuSoundEffect::enabled;
} // isMenuSoundEnabled

bool SoundManager::isGameSoundEnabled() {
    return GameSoundEffect::enabled;
} // isGameSoundEnabled

void SoundManager::resetSound() {
    Mix_HaltChannel(-1);
    GameSoundEffect::enabled = true;
    MenuSoundEffect::enabled = true;
} // resetSound

void SoundManager::setGameSoundEnabled(bool enabled) {
    GameSoundEffect::enabled = enabled;

    if (enabled) {
        for (SoundEffect *fx : gameSoundEffects) {
            fx->resume();
        } // for
    } // if
    else {
        for (SoundEffect *fx : gameSoundEffects) {
            fx->pause();
        } // for
    } // else
} // setGameSoundEnabled

void SoundManager::setMenuSoundEnabled(bool enabled) {
    MenuSoundEffect::enabled = enabled;

    if (enabled) {
        for (SoundEffect *fx : menuSoundEffects) {
            fx->resume();
        } // for
    } // if
    else {
        for (SoundEffect *fx : menuSoundEffects) {
            fx->pause();
        } // for
    } // else
} // setMenuSoundEnabled
