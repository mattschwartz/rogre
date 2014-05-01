#ifndef _ROOM_GENERATOR_H_
#define _ROOM_GENERATOR_H_

/**
 * Included files
 */
#include "src/world/Room.h"
#include "src/doodad/ChestDoodad.h"
#include "src/entities/Entity.h"
#include "src/entities/monsters/GoblinEntity.h"
#include "src/items/Item.h"
#include "src/gameobjects/EntityObject.h"
#include "src/gameobjects/GoblinEntityObject.h"
#include "src/gameobjects/ChestDoodadObject.h"
#include "src/gameobjects/RoomObject.h"
#include "src/gameobjects/ObjectManager.h"
#include "src/gameobjects/LootObject.h"

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
        GoblinEntity *e;
        ChestDoodad *d;
        Item *i;

        r = new Room(zoneLevel, width, depth);

        while (!done) {
            e = new GoblinEntity(zoneLevel, "monster1");
			eX = (rand() % (int)width) + x;
			eZ = (rand() % (int)depth) + z;
            
			ObjectManager::getInstance().spawnObject(new GoblinEntityObject(e, eX, eZ));

            d = new ChestDoodad();
			eX = (rand() % (int)width) + x;
			eZ = (rand() % (int)depth) + z;

			ObjectManager::getInstance().spawnObject(new ChestDoodadObject(d, eX, eZ));

            i = new Item(0, zoneLevel, 99, 1, "gold");
			eX = (rand() % (int)width) + x;
			eZ = (rand() % (int)depth) + z;

            ObjectManager::getInstance().spawnObject(new LootObject(i, eX, eZ));

            done = true;
        } // while

		return r;
    } // generate
};

#endif
