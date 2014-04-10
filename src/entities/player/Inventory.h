#ifndef _INVENTORY_H_
#define _INVENTORY_H_

/**
 * Included files
 */

/**
 * Defines
 */
#define INVENTORY_SLOTS 24

/**
 * Forward declarations
 */
class Item;

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
