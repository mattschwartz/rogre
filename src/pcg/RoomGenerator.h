#ifndef _ROOM_GENERATOR_H_
#define _ROOM_GENERATOR_H_

/**
 * Included files
 */

#define DEFAULT_ROOM_HEIGHT 15
#define MIN_ROOM_WIDTH 10
#define MIN_ROOM_DEPTH MIN_ROOM_WIDTH
#define MAX_ROOM_WIDTH 50
#define MAX_ROOM_DEPTH MAX_ROOM_WIDTH

class Zone;
class Room;

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

    Room *generate(Zone *zone, float x, float z, float width, float depth);
};

#endif
