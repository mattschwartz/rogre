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

    Room *generate(int seed, int zoneLevel, float x, float z, float width, float depth) {
        bool done;
        Room *r;
        Entity *e;
        Item *i;
        Doodad *d;

        r = new Room(zoneLevel, x, z, width, depth);
        done = false;

        while (!done) {
            e = new SkeletonEntity(zoneLevel, "monster1");
            i = new Item(1, zoneLevel, 0, 1, "item1");
            d = new Doodad();

            r->addMonster(e, 0, 0);
            r->addLoot(i, 0, 0);
            r->addDoodad(d, 0, 0);

            done = true;
        } // while

        return r;
    } // generate
};

#endif
