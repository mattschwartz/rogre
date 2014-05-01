#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

/**
 * Included files
 */
#include <vector>

class SoundEffect;

class SoundManager {
private:
    SoundManager() {}
    SoundManager(SoundManager const&);
    void operator=(SoundManager const&);

public:
    SoundEffect *PLAYER_FOOTSTEP_SOUND;
    SoundEffect *MONSTER_BREATHING_1_SOUND;
    SoundEffect *MONSTER_BREATHING_2_SOUND;
    SoundEffect *MONSTER_BREATHING_3_SOUND;
    SoundEffect *MONSTER_BREATHING_4_SOUND;
    SoundEffect *ATTACK_HIT_1_SOUND;
    SoundEffect *ATTACK_MISS_1_SOUND;
    SoundEffect *MENU_SELECT_SOUND;
    SoundEffect *AMBIANCE_RUMBLE_SOUND;
    std::vector<SoundEffect*> gameSoundEffects;
    std::vector<SoundEffect*> menuSoundEffects;

    static SoundManager &getInstance() {
        static SoundManager instance;
        return instance;
    } // getInstance

    void init();
    bool isMenuSoundEnabled();
    bool isGameSoundEnabled();
    void resetSound();
    void volumeControl(int newVolume);
    void setGameSoundEnabled(bool enabled);
    void setMenuSoundEnabled(bool enabled);
};

#endif
