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
class Level;

/**
 * Data
 */
class World {
private:
    Player *currentPlayer;
    Level *currentLevel;
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
    Level *getCurrentLevel();
    void setCurrentLevel(Level *level);

    void playerQuit();
};

#endif
