#ifndef _INVENTORY_H_
#define _INVENTORY_H_

/**
 * Included files
 */
#include "items/Item.h"

/**
 * Defines
 */
#define INVENTORY_SLOTS 24

/**
 * Data
 */
class Inventory {
private:
    Item *inventory[INVENTORY_SLOTS];

public:
    Inventory();
    ~Inventory();
    bool addItem(Item *item);
    Item *removeItem(int index);
};

#endif
