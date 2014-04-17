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
public:
    int zoneLevel;
    std::vector<Room*> rooms;
    Zone(int zoneLevel);
};

#endif
