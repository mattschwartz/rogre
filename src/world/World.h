#ifndef _WORLD_H_
#define _WORLD_H_

/**
 * Included files
 */
#include <stdexcept>
#include <stdlib.h>

class Player;
class Zone;

/**
 * Data
 */
class World {
private:
    int currentZoneLevel;
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

    void playerQuit();
    void loadZone();
    void spawnCurrentPlayer(float x, float y, float z);

    /**
     * Getters & Setters
     */
    int getZoneLevel();
    void setZoneLevel(int zoneLevel);
    Player *getCurrentPlayer();
    void setCurrentPlayer(Player *player);
    Zone *getCurrentZone();
    void setCurrentZone(Zone *zone);
};

#endif
