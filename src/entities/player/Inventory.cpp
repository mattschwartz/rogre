/**
 * Included files
 */
#include <stdexcept>
#include "Inventory.h"
#include "src/items/Item.h"

/**
 * Defines
 */

/**
 * Data
 */
Inventory::Inventory() {
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        inventory[i] = NULL;
    } // for
} // constructor

bool Inventory::addItem(Item *item) {
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        if (inventory[i] == item) {
            inventory[i]++;
        } // if
    } // for

    return false;
} // addItem

Item *Inventory::removeItem(int index) {
    Item *item;

    if (index < 0 || index >= INVENTORY_SLOTS) {
        throw std::invalid_argument("Index is invalid" + index);
    } // if

    item = inventory[index];
    inventory[index] = NULL;
    
    return inventory[index];
} // removeItem
