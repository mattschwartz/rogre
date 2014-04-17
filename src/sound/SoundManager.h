#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

class SoundEffect;

class SoundManager {
private:
    bool soundEnabled;
    SoundManager() {}
    SoundManager(SoundManager const&);
    void operator=(SoundManager const&);

public:
    SoundEffect *PLAYER_FOOTSTEP_SOUND;
    SoundEffect *ATTACK_HIT_1_SOUND;
    SoundEffect *ATTACK_MISS_1_SOUND;
    SoundEffect *MENU_SELECT_SOUND;
    SoundEffect *AMBIANCE_RUMBLE_SOUND;

    static SoundManager &getInstance() {
        static SoundManager instance;
        return instance;
    } // getInstance

    void init();
    bool isSoundEnabled();
    void toggleSound();
};

#endif
