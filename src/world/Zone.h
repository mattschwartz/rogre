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

class Zone {
public:
    int zoneLevel;
    std::vector<RoomObject*> rooms;
    Zone(int zoneLevel);
	bool containsPoint(Ogre::Vector3 point);
	Ogre::Vector3 getIntersectingPlane(Ogre::Ray ray);
};

#endif
