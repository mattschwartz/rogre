/** 
 * Included files
 */
#include "Zone.h"
#include "Room.h"

/**
 * Data
 */
Zone::Zone(int zoneLevel) {
    this->zoneLevel = zoneLevel;
} // constructor

void Zone::generateRooms(int seed, int numRooms) {
    srand(seed);
} // generateRooms

std::vector<Room*> Zone::getRooms() {
    std::vector<Room*> roomsCopy;

    for (Room *r : this->rooms) {
        roomsCopy.push_back(r);
    } // for

    return roomsCopy;
} // getRooms

Room *Zone::getRoom(int index) {
    int i = 0;

    for (Room *r : this->rooms) {
        if ((i++) == index) {
            return r;
        } // if
    } // for

    return NULL;
} // getRoom

int Zone::getZoneLevel() {
    return this->zoneLevel;
} // getZoneLevel
