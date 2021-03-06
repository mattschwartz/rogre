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
Room::Room(float width, float depth) {
    this->width = width;
    this->depth = depth;
} // constructor

void Room::addMonster(Entity *monster, float x, float z) {
} // addMonster

void Room::addLoot(Item *item, float x, float z) {
} // addLoot

void Room::addDoodad(Doodad *doodad, float x, float z) {
} // addDoodad
