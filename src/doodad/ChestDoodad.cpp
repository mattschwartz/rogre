/**
 * Included files
 */
#include "ChestDoodad.h"
#include "src/items/Item.h"

ChestDoodad::ChestDoodad() {
} // constructor

void ChestDoodad::addItem(Item *item) {
    contents.push_back(item);
} // addItem

std::vector<Item*> ChestDoodad::getContents() {
    std::vector<Item*> result;

    for (Item *item : contents) {
        result.push_back(item);
    } // for

    return result;
} // getContents
