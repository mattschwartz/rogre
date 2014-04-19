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
	struct Wall {
		float x1;
		float x2;
		float z1;
		float z2;
		Ogre::Vector3 direction;
	};
	std::vector<RoomObject *> rooms;
	std::vector<struct Wall> freeWalls;

    ZoneGenerator() {}
    ZoneGenerator(ZoneGenerator const&);
    void operator=(ZoneGenerator const&);

	void spawnRoom(int roomId, Room *room, float x, float z, float width, 
		float depth) {
		struct Wall wall;
		RoomObject *ro = new RoomObject(roomId, room, width, depth, 
			DEFAULT_ROOM_HEIGHT, Ogre::Vector3(x, 0, z));
		
		// North wall
		wall.x1 = ro->getPosition().x;
		wall.z1 = ro->getPosition().z;
		wall.x2 = ro->getBounds().xEnd;
		wall.z2 = wall.z1;
		wall.direction = Ogre::Vector3::UNIT_Z;
		freeWalls.push_back(wall);

		// South wall
		wall.z1 = ro->getBounds().zEnd;
		wall.z2 = wall.z1;
		wall.direction = Ogre::Vector3::NEGATIVE_UNIT_Z;
		freeWalls.push_back(wall);

		// West wall
		wall.x2 = ro->getPosition().x;
		wall.z1 = ro->getPosition().z;
		wall.z2 = ro->getBounds().zEnd;
		wall.direction = Ogre::Vector3::UNIT_X;
		freeWalls.push_back(wall);

		// East wall
		wall.x1 = ro->getBounds().xEnd;
		wall.x2 = wall.x1;
		wall.direction = Ogre::Vector3::NEGATIVE_UNIT_X;
		freeWalls.push_back(wall);

		ObjectManager::getInstance().spawnObject(ro);
		rooms.push_back(ro);
	} // addRoom

	bool overlaps(float x, float z, float width, float depth) {
		struct Bounds bounds;

		bounds.xStart = x;
		bounds.zStart = z;
		bounds.xEnd = x + width;
		bounds.zEnd = z + depth;

		for (RoomObject *r : rooms) {
			if (r->overlaps(bounds)) {
				return true;
			} // if
		} // for

		return false;
	} // overlaps

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
		struct Wall wall;
		struct Bounds newRoomBounds;
        srand(seed);

        x = 0.0f;
        z = 0.0f;
		width = (float)(rand() % MAX_ROOM_WIDTH + MIN_ROOM_WIDTH);
		depth = (float)(rand() % MAX_ROOM_DEPTH + MIN_ROOM_DEPTH);

        r = RoomGenerator::getInstance().generate(zone->zoneLevel, x, z,
            width, depth);
        zone->rooms.push_back(r);

		spawnRoom(0, r, x, z, width, depth);

        for (int i = 1; i < numRooms; i++) {
			if (!freeWalls.empty()) {
				std::random_shuffle(freeWalls.begin(), freeWalls.end());

				wall = freeWalls.back();
				freeWalls.pop_back();
			} // if

			x = wall.x1;
			z = wall.z1;
			width = (float)(rand() % MAX_ROOM_WIDTH + MIN_ROOM_WIDTH);
			depth = (float)(rand() % MAX_ROOM_DEPTH + MIN_ROOM_DEPTH);

			if (wall.direction == Ogre::Vector3::UNIT_Z) {
				z -= depth;
			} else if (wall.direction == Ogre::Vector3::UNIT_X) {
				x -= width;
			}

			if (overlaps(x, z, width, depth)) {
				continue;
			} // if

            r = RoomGenerator::getInstance().generate(zone->zoneLevel, x, z,
                width, depth);
            zone->rooms.push_back(r);

			spawnRoom(i, r, x, z, width, depth);
		} // for

        return zone;
    } // generate
};

#endif
