/** 
 * Included files
 */
#include "Zone.h"
#include "Room.h"
#include "src/gameobjects/RoomObject.h"
#include "src/gameobjects/EntityObject.h"
#include "src/gameobjects/LootObject.h"
#include "src/gameobjects/DoodadObject.h"
#include "src/gameobjects/DoorDoodadObject.h"
#include "src/pcg/RoomGenerator.h"
#include "src/utility/MathHelper.h"

/**
 * Data
 */
Zone::Zone(int monsterDifficulty, int zoneLevel) {
    this->monsterDifficulty = monsterDifficulty;
    this->zoneLevel = zoneLevel;
} // constructor

void Zone::addEntity(EntityObject *o) {
    entities.push_back(o);
} // addEntity

void Zone::addLoot(LootObject *o) {
    loot.push_back(o);
} // addLoot

void Zone::addDoodad(DoodadObject *o) {
    doodads.push_back(o);
} // addDoodad

void Zone::addDoorDoodad(DoorDoodadObject *o) {
    doorDoodads.push_back(o);
} // addDoorDoodad

bool Zone::canMove(Ogre::Vector3 point) {
    using namespace MathHelper;

    for (DoorDoodadObject *door : doorDoodads) {
        if (door->contains(point)) {
            return true;
        } // if
    } // for

	for (RoomObject *ro : rooms) {
		if (ro->containsPoint(point)) {
            struct Bounds b = ro->getBounds();

            // north wall
            if (greaterIsh<float>(point.x, b.xStart, 0.2f) && 
                lesserIsh<float>(point.x, b.xEnd, 0.2f) &&
                equalIsh<float>(point.z, b.zStart, 0.2f)) {
                return false;
            }
            // south wall
            if (greaterIsh<float>(point.x, b.xStart, 0.2f) && 
                lesserIsh<float>(point.x, b.xEnd, 0.2f) &&
                equalIsh<float>(point.z, b.zEnd, 0.2f)) {
                return false;
            }
            // west wall
            if (greaterIsh<float>(point.z, b.zStart, 0.2f) && 
                lesserIsh<float>(point.z, b.zEnd, 0.2f) &&
                equalIsh<float>(point.x, b.xStart, 0.2f)) {
                return false;
            }
            // east wall
            if (greaterIsh<float>(point.z, b.zStart, 0.2f) && 
                lesserIsh<float>(point.z, b.zEnd, 0.2f) &&
                equalIsh<float>(point.x, b.xEnd, 0.2f)) {
                return false;
            }

			return true;
		} // 
	} // for

	return false;
} // canMove

Ogre::Vector3 Zone::getIntersectingPlane(Ogre::Ray ray) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	for (RoomObject *ro : rooms) {
		std::pair<bool, Ogre::Real> point = ray.intersects(*ro->floor);
		if (point.first) {
			Ogre::Vector3 pos = ray.getPoint(point.second);
			return pos;
		} // if
	}

	return Ogre::Vector3::UNIT_Y;
} // getIntersectingPlane
