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
    ZoneGenerator() {}
    ZoneGenerator(ZoneGenerator const&);
    void operator=(ZoneGenerator const&);

public:
    static ZoneGenerator &getInstance() {
        static ZoneGenerator instance;
        return instance;
    } // getInstance

    Zone *generate(int seed, int monsterLevel, int numRooms) {
        float x;
        float z;
        float width;
        float height;
        Zone *zone = new Zone(monsterLevel);
        Room *r;
        srand(seed);

        for (int i = 0; i < numRooms; i++) {
            x = i;
            z = i;
            width = i;
            height = i;

            r = RoomGenerator::getInstance().generate(seed, zone->zoneLevel, x, z, 
                width, height);
            zone->rooms.push_back(r);
        } // for

        return zone;
    } // generate
};

#endif
