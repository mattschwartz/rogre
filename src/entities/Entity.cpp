/**
 * Included files
 */
#include "Entity.h"
#include "items/Item.h"

/**
 * Defines
 */

/**
 * Data
 */
Entity::Entity(int level, std::string name) {
    this->level = level;
    this->name = name;

    attributes[strength] = 50.0;
    attributes[hitpoints] = 100.0;
    attributes[armor] = 25.0;

    currentHitpoints = attributes[hitpoints];
} // constructor
