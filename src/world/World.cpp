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

/**
 * 
 * @return Returns the current player
 */
Player *World::getCurrentPlayer() {
    return currentPlayer;
} // getCurrentPlayer

Ogre::Vector3 World::getPlayerPosition() {
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

void World::spawnCurrentPlayer(float x, float y, float z) {
    playerObject = new PlayerObject(this->currentPlayer, x, y, z);
    ObjectManager::getInstance().spawnObject(playerObject);
} // spawnCurrentPlayer

/**
 * Terminates the player's game, saving it and exiting to the main menu.
 */
void World::playerQuit() {
    delete this->currentPlayer;
    this->currentPlayer = NULL;
    ObjectManager::getInstance().destroyScene();
} // playerQuit

void World::pauseGame() {
    SoundManager::getInstance().pauseSounds();
    paused = true;
} // pauseGame

void World::resumeGame() {
    SoundManager::getInstance().resumeSounds();
    paused = false;
} // resumeGame

bool World::isGamePaused() {
    return paused;
} // isGamePaused

/**
 * Generates a new Zone that is abstractly one level below the current Zone
 * and thus one level more difficult.
 */
void World::loadZone() {
    paused = false;

    if (currentZone != NULL) {
		delete currentZone;
		currentZoneLevel++;
	} // if

    currentZone = ZoneGenerator::getInstance().generate((int)time(NULL), currentZoneLevel, 15);
    SoundManager::getInstance().AMBIANCE_RUMBLE_SOUND->loop(-1);
    GUIManager::getInstance().loadingMenu->hide();
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
