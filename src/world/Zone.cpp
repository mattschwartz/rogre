/** 
 * Included files
 */
#include "Zone.h"
#include "Room.h"
#include "src/gameobjects/RoomObject.h"
#include "src/gameobjects/EntityObject.h"
#include "src/gameobjects/LootObject.h"
#include "src/gameobjects/DoodadObject.h"
#include "src/pcg/RoomGenerator.h"

/**
 * Data
 */
Zone::Zone(int zoneLevel) {
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

bool Zone::containsPoint(Ogre::Vector3 point) {
	for (RoomObject *ro : rooms) {
		if (ro->containsPoint(point)) {
			return true;
		} // 
	} // for

	return false;
} // containsPoint

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
