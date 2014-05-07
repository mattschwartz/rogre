#ifndef _PLAYER_H_
#define _PLAYER_H_

/**
 * Included files
 */
#include "src/entities/Entity.h"
#include <Ogre.h>

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
    double lifePerSecond;
    Ogre::Real timePlayed;
    Equippable *equippedItems[EQUIPMENT_SLOTS];
    Inventory *inventory;

public:
    Player(int level, std::string name);
    double getRegen();
    void regenerateLife();
    double getCurrentHitpoints();
    std::string getName();
    int getScore();
    void equipItem(Equippable *equippable);
    Equippable *getEquippedItemAt(int slotId);
    Inventory *getInventory();
    Ogre::Real getTimePlayed();
    void updateTimePlayed(Ogre::Real secondsPassed);

    double calculateHit();
    virtual void takeDamage(double amount, Entity *aggressor);
    void die(Entity *slayer);
    void onSpawn() {}
    void onDeath() {}
    void onDamageDealt() {}
    void onDamageTaken() {}
};

#endif
