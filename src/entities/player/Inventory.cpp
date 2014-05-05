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
} // constructor

void Inventory::addItem(Item *item) {
    items.push_back(item);
} // addItem

Item *Inventory::removeItem(int index) {
    Item *result = items.at(index);
    items.erase(items.begin() + index);

    return result;
} // removeItem

std::vector<Item*> Inventory::getItems() {
    std::vector<Item*> result;

    for (Item *i : items) {
        result.push_back(i);
    } // for

    return result;
} // getItems
