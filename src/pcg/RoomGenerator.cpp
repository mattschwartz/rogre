/**
 * Included files
 */
#include "RoomGenerator.h"
#include "src/world/Zone.h"
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

Room *RoomGenerator::generate(Zone *zone, float x, float z, 
	float width, float depth) {
	float eX;
	float eZ;
    bool done = false;
    Room *r;
    GoblinEntity *e;
    ChestDoodad *d;
    Item *i;

    r = new Room(zone->zoneLevel, width, depth);

    while (!done) {
        e = new GoblinEntity(zone->zoneLevel, "monster1");
		eX = (rand() % (int)width) + x;
		eZ = (rand() % (int)depth) + z;
        zone->addEntity(new GoblinEntityObject(e, eX, eZ));

        d = new ChestDoodad();
		eX = (rand() % (int)width) + x;
		eZ = (rand() % (int)depth) + z;
        zone->addDoodad(new ChestDoodadObject(d, eX, eZ));

        i = new Item(0, zone->zoneLevel, 99, 1, "jesus");
		eX = (rand() % (int)width) + x;
		eZ = (rand() % (int)depth) + z;
        zone->addLoot(new LootObject(i, eX, eZ));

        done = true;
    } // while

	return r;
} // generate