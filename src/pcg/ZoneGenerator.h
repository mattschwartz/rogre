#ifndef _ZONE_GENERATOR_H_
#define _ZONE_GENERATOR_H_

/**
 * Included files
 */
#include "RoomGenerator.h"
#include "src/world/Zone.h"
#include "src/world/Room.h"

class ZoneGenerator {
private:
	std::vector<Ogre::Plane> freeWalls;

    ZoneGenerator() {}
    ZoneGenerator(ZoneGenerator const&);
    void operator=(ZoneGenerator const&);

	void spawnRoom(int roomId, Room *room, float x, float z, float width, 
		float depth) {
		RoomObject *ro = new RoomObject(roomId, room, width, depth, 
			DEFAULT_ROOM_HEIGHT, Ogre::Vector3(x, (DEFAULT_ROOM_HEIGHT/2), z));
		
		freeWalls.push_back(*ro->walls[0]);
		freeWalls.push_back(*ro->walls[1]);
		freeWalls.push_back(*ro->walls[2]);
		freeWalls.push_back(*ro->walls[3]);

		ObjectManager::getInstance().spawnObject(ro);
	} // addRoom

public:
    static ZoneGenerator &getInstance() {
        static ZoneGenerator instance;
        return instance;
    } // getInstance

    Zone *generate(int seed, int monsterLevel, int numRooms) {
        float x;
        float z;
        float width;
        float depth;
        Room *r;
        Zone *zone = new Zone(monsterLevel);
		Ogre::Plane wall;
        srand(seed);

        x = 0.0f;
        z = 0.0f;

        r = RoomGenerator::getInstance().generate(0, zone->zoneLevel, x, z,
            width, depth);
        zone->rooms.push_back(r);

		spawnRoom(0, r, x, z, width, depth);

        for (int i = 1; i < numRooms; i++) {
			if (!freeWalls.empty()) {
				std::random_shuffle(freeWalls.begin(), freeWalls.end());

				wall = freeWalls.back();
				freeWalls.pop_back();
			} // if

            r = RoomGenerator::getInstance().generate(i, zone->zoneLevel, x, z,
                width, depth);
            zone->rooms.push_back(r);

			spawnRoom(i, r, x, z, width, depth);
		} // for

        return zone;
    } // generate
};

#endif
