/**
 * Included files
 */
#include "MenuSoundEffect.h"
#include "src/world/World.h"

void MenuSoundEffect::play() {
    if (enabled) {
        this->channel = Mix_PlayChannel(-1, this->sound, 0);
    } // if
} // play

void MenuSoundEffect::pause() {
    if (channel >= 0) {
        Mix_Pause(channel);
    } // if
} // pause

void MenuSoundEffect::resume() {
    if (!World::getInstance().isGamePaused() && enabled) {
        if (channel >= 0) {
            Mix_Resume(channel);
        } // if
    } // if
} // resume

void MenuSoundEffect::stop() {
    if (channel >= 0) {
        Mix_HaltChannel(channel);
    } // if
} // stop

void MenuSoundEffect::loop(int loops) {
    if (!World::getInstance().isGamePaused() && enabled) {
        channel = Mix_PlayChannel(-1, sound, loops);
    } // if
} // loop