#ifndef _LEVEL_H_
#define _LEVEL_H_

/**
 * Included files
 */
#include <vector>

/**
 * Defines
 */

/**
 * Forward declarations
 */
class Room;

class Zone {
private:
    int zoneLevel;
    std::vector<Room*> rooms;

public:
    Zone(int zoneLevel);
    void generateRooms(int seed, int numRooms);
    std::vector<Room*> getRooms();
    Room *getRoom(int index);

    /**
     * Getters & Setters
     */
    int getZoneLevel();
};

#endif
