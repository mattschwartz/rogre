#ifndef _ROOM_GENERATOR_H_
#define _ROOM_GENERATOR_H_

/**
 * Included files
 */
#include "src/world/Room.h"
#include "src/doodad/Doodad.h"
#include "src/entities/Entity.h"
#include "src/entities/monsters/SkeletonEntity.h"
#include "src/items/Item.h"
#include "src/gameobjects/EntityObject.h"
#include "src/gameobjects/RoomObject.h"
#include "src/gameobjects/ObjectManager.h"

#define DEFAULT_ROOM_HEIGHT 15
#define MIN_ROOM_WIDTH 10
#define MIN_ROOM_DEPTH MIN_ROOM_WIDTH
#define MAX_ROOM_WIDTH 50
#define MAX_ROOM_DEPTH MAX_ROOM_WIDTH

/**
 * Data
 */
class RoomGenerator {
private:
    RoomGenerator() {}
    RoomGenerator(RoomGenerator const&);
    void operator=(RoomGenerator const&);

public:
    static RoomGenerator &getInstance() {
        static RoomGenerator instance;
        return instance;
    } // getInstance

    Room *generate(int zoneLevel, float x, float z, 
		float width, float depth) {
		float eX;
		float eZ;
        bool done = false;
        Room *r;
        Entity *e;
        Item *i;
        Doodad *d;

        r = new Room(zoneLevel, width, depth);

        while (!done) {
            e = new SkeletonEntity(zoneLevel, "monster1");
            i = new Item(1, zoneLevel, 0, 1, "item1");
            d = new Doodad();

			eX = (rand() % (int)width) + x;
			eZ = (rand() % (int)depth) + z;

			ObjectManager::getInstance().spawnObject(new EntityObject(e, eX, eZ));

            done = true;
        } // while

		return r;
    } // generate
};

#endif
