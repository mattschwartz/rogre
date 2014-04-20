/** 
 * Included files
 */
#include "Zone.h"
#include "Room.h"
#include "src/gameobjects/RoomObject.h"
#include "src/pcg/RoomGenerator.h"
#include <stdlib.h>

/**
 * Data
 */
Zone::Zone(int zoneLevel) {
    this->zoneLevel = zoneLevel;
} // constructor

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
