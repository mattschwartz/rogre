#ifndef _ROOM_H_
#define _ROOM_H_

/**
 * Included files
 */
#include <vector>

/**
 * Defines
 */

/**
 * Forward declarations
 */
class EntityObject;
class Loot;
class DoodadObject;

class Entity;
class Item;
class Doodad;

class Room {
private:
    float width;
    float depth;
    std::vector<EntityObject*> monsters;
    std::vector<Loot*> loot;
    std::vector<DoodadObject*> doodads;

public:
    Room(float width, float depth);
    void addMonster(Entity *entity, int x, int y);
    void addLoot(Item *loot, int x, int y);
    void addDoodad(Doodad *doodad, int x, int y);
};

#endif
