/**
 * Included files
 */
#include "SoundEffect.h"

SoundEffect::SoundEffect(const std::string filepath) {
    this->channel = -1;
    sound = Mix_LoadWAV(filepath.c_str());
} // constructor

SoundEffect::~SoundEffect() {
    Mix_FreeChunk(this->sound);
} // destructor
