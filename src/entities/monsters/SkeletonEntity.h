#ifndef _SKELETON_ENTITY_H_
#define _SKELETON_ENTITY_H_

/**
 * Included files
 */
#include "src/entities/Entity.h"

class SkeletonEntity : public Entity {
public:
    SkeletonEntity(int level, int monsterDifficulty, std::string name) : Entity(level, monsterDifficulty, name) {}
    ~SkeletonEntity() {}
    void onSpawn();
    void onDeath();
    void onDamageDealt();
    void onDamageTaken();
};

#endif
