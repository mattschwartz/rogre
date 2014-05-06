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
#include "ItemGenerator.h"
#include "MonsterGenerator.h"
#include "src/utility/StringHelper.h"

Room *RoomGenerator::generate(Zone *zone, float x, float z, 
	float width, float depth) {
	float eX;
	float eZ;
    bool done = false;
    Room *r;
    GoblinEntity *e;
    ChestDoodad *d;
    Item *i;

    r = new Room(width, depth);

    while (!done) {
        e = (GoblinEntity*)MonsterGenerator::getInstance().generateMonster(zone->zoneLevel, zone->monsterDifficulty);
		eX = (rand() % (int)width) + x;
		eZ = (rand() % (int)depth) + z;
        zone->addEntity(new GoblinEntityObject(e, eX, eZ));

        d = new ChestDoodad();
		eX = (rand() % (int)width) + x;
		eZ = (rand() % (int)depth) + z;
        zone->addDoodad(new ChestDoodadObject(d, eX, eZ));

        i = ItemGenerator::getInstance().generateItem(zone->zoneLevel);
		eX = (rand() % (int)width) + x;
		eZ = (rand() % (int)depth) + z;
        zone->addLoot(new LootObject(i, eX, eZ));

        done = true;
    } // while

	return r;
} // generate