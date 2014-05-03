#ifndef _LEVEL_H_
#define _LEVEL_H_

/**
 * Included files
 */
#include <stdlib.h>
#include <vector>
#include <Ogre.h>

/**
 * Defines
 */

/**
 * Forward declarations
 */
class RoomObject;
class EntityObject;
class LootObject;
class DoodadObject;
class DoorDoodadObject;

class Zone {
public:
    int zoneLevel;
    std::vector<RoomObject*> rooms;
    std::vector<EntityObject*> entities;
    std::vector<LootObject*> loot;
    std::vector<DoodadObject*> doodads;
    std::vector<DoorDoodadObject*> doorDoodads;

    Zone(int zoneLevel);
    void addEntity(EntityObject *o);
    void addLoot(LootObject *o);
    void addDoodad(DoodadObject *o);
    void addDoorDoodad(DoorDoodadObject *o);
	bool canMove(Ogre::Vector3 point);
	Ogre::Vector3 getIntersectingPlane(Ogre::Ray ray);
};

#endif
