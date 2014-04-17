#ifndef _ROOM_H_
#define _ROOM_H_

/**
 * Included files
 */
#include <vector>

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
    int monsterLevel;
    float x;
    float z;
    float width;
    float depth;
    std::vector<EntityObject*> monsters;
    std::vector<Loot*> loot;
    std::vector<DoodadObject*> doodads;

public:
    Room(int monsterLevel, float x, float z, float width, float depth);
    void addMonster(Entity *monster, float x, float z);
    void addLoot(Item *item, float x, float z);
    void addDoodad(Doodad *doodad, float x, float z);
};

#endif
