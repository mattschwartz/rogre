#ifndef _INVENTORY_H_
#define _INVENTORY_H_

/**
 * Included files
 */
#include <vector>

/**
 * Forward declarations
 */
class Item;

/**
 * Data
 */
class Inventory {
private:
    std::vector<Item*> items;

public:
    Inventory();
    ~Inventory();
    void addItem(Item *item);
    Item *removeItem(int index);
    std::vector<Item*> getItems();
};

#endif
