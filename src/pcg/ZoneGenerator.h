#ifndef _ZONE_GENERATOR_H_
#define _ZONE_GENERATOR_H_

/**
 * Included files
 */
#include "RoomGenerator.h"
#include "src/world/Zone.h"
#include "src/world/Room.h"
#include "src/utility/StringHelper.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/LoadingMenu.h"
#include <thread>
#include <chrono>

static int lightCount = 0;

class ZoneGenerator {
private:
	struct Wall {
		float x1;
		float x2;
		float z1;
		float z2;
		Ogre::Vector3 direction;
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
