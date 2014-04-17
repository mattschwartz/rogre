#ifndef _PLAYER_H_
#define _PLAYER_H_

/**
 * Included files
 */
#include <time.h>
#include "src/entities/Entity.h"

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
    time_t timePlayed;
    Equippable *equippedItems[EQUIPMENT_SLOTS];
    Inventory *inventory;

public:
    Player(int level, std::string name);
    void equipItem(Equippable *equippable);
    Equippable *getEquippedItemAt(int slotId);
    Inventory *getInventory();

    void onSpawn();
    void onDeath();
    void onDamageDealt();
    void onDamageTaken();
};

#endif
