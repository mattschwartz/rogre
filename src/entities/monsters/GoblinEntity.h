#ifndef _GOBLIN_ENTITY_H_
#define _GOBLIN_ENTITY_H_

/**
 * Included files
 */
#include "src/entities/Entity.h"

class GoblinEntity : public Entity {
public:
    GoblinEntity(int level, std::string name);
    ~GoblinEntity() {}
    void onSpawn();
    void onDeath();
    void onDamageDealt();
    void onDamageTaken();
};

#endif
