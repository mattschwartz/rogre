/**
 * Included files
 */
#include "SoundEffect.h"
#include "SoundManager.h"
#include "src/world/World.h"

SoundEffect::SoundEffect(const std::string filepath) {
    this->channel = -1;
    sound = Mix_LoadWAV(filepath.c_str());
} // constructor

SoundEffect::~SoundEffect() {
    Mix_FreeChunk(this->sound);
} // destructor

void SoundEffect::play() {
    if (!World::getInstance().isGamePaused() && SoundManager::getInstance().isGameSoundEnabled()) {
        this->channel = Mix_PlayChannel(-1, this->sound, 0);
    } // if
} // play

void SoundEffect::pause() {
    if (this->channel >= 0) {
        Mix_Pause(this->channel);
    } // if
} // pause

void SoundEffect::resume() {
    if (!World::getInstance().isGamePaused() && SoundManager::getInstance().isGameSoundEnabled()) {
        if (this->channel >= 0) {
            Mix_Resume(this->channel);
        } // if
    } // if
} // resume

void SoundEffect::stop() {
    if (this->channel >= 0) {
        Mix_HaltChannel(this->channel);
    } // if
} // stop

void SoundEffect::loop(int loops) {
    if (!World::getInstance().isGamePaused() && SoundManager::getInstance().isGameSoundEnabled()) {
        this->channel = Mix_PlayChannel(-1, this->sound, loops);
    } // if
} // loop
