/**
 * Included files
 */
#include "Room.h"
#include "Zone.h"
#include "src/entities/Entity.h"
#include "src/doodad/Doodad.h"
#include "src/gameobjects/EntityObject.h"

/**
 * Data
 */
Room::Room(int monsterLevel, float x, float z, float width, float depth) {
    this->x = x;
    this->z = z;
    this->monsterLevel = monsterLevel;
    this->width = width;
    this->depth = depth;
} // constructor

void Room::addMonster(Entity *monster, float x, float z) {
    EntityObject *entityObject = new EntityObject(monster, x, 0, z);

    this->monsters.push_back(entityObject);
} // addMonster

void Room::addLoot(Item *item, float x, float z) {
} // addLoot

void Room::addDoodad(Doodad *doodad, float x, float z) {
} // addDoodad
