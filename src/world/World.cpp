/**
 * Included files
 */
#include "World.h"
#include "src/entities/player/Player.h"
#include "Zone.h"

/**
 * Defines
 */

/**
 * Data
 */
/**
 * 
 * @return Returns the current player
 */
Player *World::getCurrentPlayer() {
    return currentPlayer;
} // getCurrentPlayer

/**
 * Sets the current player to the provided argument. Only one player can be 
 * playing at once.
 * 
 * @param player The player to be playing
 */
void World::setCurrentPlayer(Player *player) {
    if (player == NULL || this->currentPlayer != NULL) {
        throw std::invalid_argument("There is already a player playing!");
    } // if
    else {
        this->currentPlayer = player;
    } // else
} // setCurrentPlayer

/**
 * 
 * @return Returns the current level
 */
Level *World::getCurrentLevel() {
    return currentLevel;
} // getCurrentLevel

/**
 * Sets the current level to the provided argument,
 * only one level may be loaded in at any given time.
 * 
 * @param level The new level to be loaded in
 */
void World::setCurrentLevel(Level *level) {
    this->currentLevel = level;
} // setCurrentLevel

void World::playerQuit() {
    delete this->currentPlayer;
    this->currentPlayer = NULL;
} // playerQuit
