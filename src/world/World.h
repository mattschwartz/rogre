#ifndef _WORLD_H_
#define _WORLD_H_

/**
 * Included files
 */
#include <Ogre.h>
#include <stdexcept>
#include <stdlib.h>

class Player;
class PlayerObject;
class Zone;

/**
 * Data
 */
class World {
private:
    bool paused;
    int currentZoneLevel;
    Player *currentPlayer;
    PlayerObject *playerObject;
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
    void pauseGame();
    void resumeGame();
    bool isGamePaused();
    void loadZone();
    void spawnCurrentPlayer(float x, float y, float z);

    /**
     * Getters & Setters
     */
    int getZoneLevel();
    void setZoneLevel(int zoneLevel);
    Player *getCurrentPlayer();
    Ogre::Vector3 getPlayerPosition();
    void setCurrentPlayer(Player *player);
    Zone *getCurrentZone();
    void setCurrentZone(Zone *zone);
};

#endif
