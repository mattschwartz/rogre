#ifndef _WORLD_H_
#define _WORLD_H_

/**
 * Included files
 */
#include <stdlib.h>

/**
 * Defines
 */

/**
 * Forward declarations
 */
class Player;
class Zone;

/**
 * Data
 */
class World {
private:
    Player *currentPlayer;
    Zone *currentZone;
    World() {}
    World(World const&);
    void operator=(World const&);

public:
    static World &getInstance() {
        static World instance;
        return instance;
    } // getInstance

    /**
     * Getters & Setters
     */
    Player *getCurrentPlayer();
    void setCurrentPlayer(Player *player);
    Zone *getCurrentZone();
    void setCurrentZone(Zone *zone);

    void playerQuit();
};

#endif
