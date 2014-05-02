#ifndef _ZONE_GENERATOR_H_
#define _ZONE_GENERATOR_H_

/**
 * Included files
 */
#include <Ogre.h>
#include <vector>
#include "RoomGenerator.h"

class Zone;
class Room;
static int lightCount = 0;

class ZoneGenerator {
private:
	struct Wall {
		float x1;
		float x2;
		float z1;
		float z2;
		Ogre::Vector3 direction;
        Ogre::Plane *wallPointer;
	};

	std::vector<struct Wall> freeWalls;
    ZoneGenerator() {}
    ZoneGenerator(ZoneGenerator const&);
    void operator=(ZoneGenerator const&);

	void spawnRoom(Zone *zone, Room *room, float x, float z, float width, 
		float depth);
	bool overlaps(Zone *zone, float x, float z, float width, float depth);
    void spawnLights(Zone *zone);

public:
    static ZoneGenerator &getInstance() {
        static ZoneGenerator instance;
        return instance;
    } // getInstance

    Zone *generate(int seed, int monsterLevel, int numRooms);
};

#endif
