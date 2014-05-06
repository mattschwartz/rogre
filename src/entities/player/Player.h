#ifndef _PLAYER_H_
#define _PLAYER_H_

/**
 * Included files
 */
#include "src/entities/Entity.h"
#include <Ogre.h>

/**
 * Defines
 */

/**
 * Forward declarations
 */
class Equippable;
class Inventory;

/**
 * Data
 */
class Player : public Entity {
private:
    int gold;
    Ogre::Real timePlayed;
    Equippable *equippedItems[EQUIPMENT_SLOTS];
    Inventory *inventory;

public:
    Player(int level, std::string name);
    double getCurrentHitpoints();
    std::string getName();
    int getScore();
    void equipItem(Equippable *equippable);
    Equippable *getEquippedItemAt(int slotId);
    Inventory *getInventory();
    int getTimePlayed();
    void updateTimePlayed(Ogre::Real secondsPassed);

    void onSpawn();
    void onDeath();
    void onDamageDealt();
    void onDamageTaken();
};

#endif
