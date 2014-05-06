/**
 * Included files
 */
#include "World.h"
#include "src/entities/player/Player.h"
#include "Zone.h"
#include "src/pcg/ZoneGenerator.h"
#include "src/gameobjects/ObjectManager.h"
#include "src/gameobjects/PlayerObject.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/ingamemenu/InGameMenu.h"
#include "src/gui/menu/NewPlayerMenu.h"
#include "src/gui/menu/LoadingMenu.h"
#include "src/gameobjects/RoomObject.h"

Player *World::getCurrentPlayer() {
    return currentPlayer;
} // getCurrentPlayer

/**
 * 
 * @return Returns the current player
 */
PlayerObject *World::getPlayerObject() {
    return playerObject;
} // getPlayerObject

Ogre::Vector3 World::getPlayerPosition() {
    if (playerObject == NULL) {
        return Ogre::Vector3::NEGATIVE_UNIT_Y;
    } // if

    return playerObject->getPosition();
} // getPlayerPosition

/**
 * Sets the current player to the provided argument. Only one player can be 
 * playing at once.
 * 
 * @param player The player to be playing
 */
void World::setCurrentPlayer(Player *player) {
    if (player == NULL || this->currentPlayer != NULL) {
    } // if
    else {
        this->currentPlayer = player;
    } // else
} // setCurrentPlayer

void World::spawnCurrentPlayer() {
    Ogre::Vector3 position;
    RoomObject *ro;
    
    if (currentZone == NULL) {
        return;
    } // if

    ro = currentZone->rooms[0];
    ro->show();

    position.x = rand() % (int)(ro->getWidth()) + 1.0f;
    position.y = 0;
    position.z = rand() % (int)(ro->getDepth()) + 1.0f;

    playerObject = new PlayerObject(this->currentPlayer, position);
    ObjectManager::getInstance().spawnObject(playerObject);

    paused = false;
    currentZoneLevel = 0;
    GUIManager::getInstance().inGameMenu->updateAttributes(currentPlayer);
} // spawnCurrentPlayer

/**
 * Terminates the player's game, saving it and exiting to the main menu.
 */
void World::playerQuit() {
    delete this->currentPlayer;
    this->currentPlayer = NULL;
    SoundManager::getInstance().resetSound();
    ObjectManager::getInstance().destroyScene();
} // playerQuit

void World::pauseGame() {
    paused = true;
} // pauseGame

void World::resumeGame() {
    paused = false;
} // resumeGame

bool World::isGamePaused() {
    return paused;
} // isGamePaused

/**
 * Generates a new Zone that is abstractly one level below the current Zone
 * and thus one level more difficult.
 */
void World::loadZone(int zoneLevel, int monsterDifficulty, int seed) {
    int roomSize = 15;
    paused = true;

    currentZoneLevel = zoneLevel;
    currentZone = ZoneGenerator::getInstance().generate(seed, monsterDifficulty, currentZoneLevel, roomSize);
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
