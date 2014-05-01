/**
 * Included files
 */
#include "GameSoundEffect.h"
#include "src/world/World.h"

void GameSoundEffect::play() {
    if (enabled) {
        this->channel = Mix_PlayChannel(-1, this->sound, 0);
    } // if
} // play

void GameSoundEffect::pause() {
    if (channel >= 0) {
        Mix_Pause(channel);
    } // if
} // pause

void GameSoundEffect::resume() {
    if (!World::getInstance().isGamePaused() && enabled) {
        if (channel >= 0) {
            Mix_Resume(channel);
        } // if
    } // if
} // resume

void GameSoundEffect::stop() {
    if (channel >= 0) {
        Mix_HaltChannel(channel);
    } // if
} // stop

void GameSoundEffect::loop(int loops) {
    if (!World::getInstance().isGamePaused() && enabled) {
        channel = Mix_PlayChannel(-1, sound, loops);
    } // if
} // loop
