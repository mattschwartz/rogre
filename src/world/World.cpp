/**
 * Included files
 */
#include "World.h"
#include "src/entities/player/Player.h"
#include "Zone.h"
#include "src/pcg/ZoneGenerator.h"
#include "src/gameobjects/ObjectManager.h"
#include "src/gameobjects/PlayerObject.h"

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

void World::spawnCurrentPlayer(float x, float y, float z) {
    PlayerObject *playerObject = new PlayerObject(this->currentPlayer, x, y, z);
    ObjectManager::getInstance().spawnObject(playerObject);
} // spawnCurrentPlayer

/**
 * Terminates the player's game, saving it and exiting to the main menu.
 */
void World::playerQuit() {
    delete this->currentPlayer;
    this->currentPlayer = NULL;
} // playerQuit

/**
 * Generates a new Zone that is abstractly one level below the current Zone
 * and thus one level more difficult.
 */
void World::loadZone() {
    delete currentZone;
    currentZoneLevel++;

    currentZone = ZoneGenerator::getInstance().generate(0, currentZoneLevel, 5);
} // loadZone

int World::getZoneLevel() {
    return currentZoneLevel;
} // getZoneLevel

void World::setZoneLevel(int zoneLevel) {
    this->currentZoneLevel = zoneLevel;
} // setZoneLevel

Zone *World::getCurrentZone() {
    return currentZone;
} // getCurrentZone

void World::setCurrentZone(Zone *zone) {
    this->currentZone = zone;
} // setCurrentZone
