/**
 * Included files
 */
#include "GoblinEntity.h"

GoblinEntity::GoblinEntity(int level, int monsterDifficulty, std::string name) :
    Entity(level, monsterDifficulty, name) {
} // constructor

void GoblinEntity::onSpawn() {
}

void GoblinEntity::onDeath() {
}

void GoblinEntity::onDamageDealt() {
}

void GoblinEntity::onDamageTaken() {
}
