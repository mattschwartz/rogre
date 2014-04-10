#ifndef _ENTITY_H_
#define _ENTITY_H_

/**
 * Included files
 */
#include <time.h>

/**
 * Defines
 */
#define NUM_ATTRIBUTES 3
#define EQUIPMENT_SLOTS 5

typedef enum {
    strength = 0,
    hitpoints = 1,
    armor = 2
} attribute_t;

typedef enum {
    helmet,
    chest,
    gloves,
    boots
} equipmentSlot_t;

/**
 * Data
 */
class Entity {
protected:
    int level;
    double currentHitpoints;
    double attributes[NUM_ATTRIBUTES];
    std::string name;
    // Position position;

public:
    Entity(int level, std::string name);
    ~Entity();
};
#endif
