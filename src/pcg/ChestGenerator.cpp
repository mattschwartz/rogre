/**
 * Included files
 */
#include "ChestGenerator.h"
#include "ItemGenerator.h"
#include "src/doodad/ChestDoodad.h"

const int SMALL_LOOT = 1;
const int MEDIUM_LOOT = 2;
const int LARGE_LOOT = 6;
const int MASSIVE_LOOT = 10;

const int SMALL_LOOT_CHANCE = 80;
const int MEDIUM_LOOT_CHANCE = 60;
const int LARGE_LOOT_CHANCE = 25;
const int MASSIVE_LOOT_CHANCE = 12;

ChestDoodad *ChestGenerator::generateChest(int level) {
    int numItems;
    ChestDoodad *result;
    Item *item;

    result = new ChestDoodad();
    numItems = rand() % 100;

    if (numItems <= MASSIVE_LOOT_CHANCE) {
        numItems = MASSIVE_LOOT;
    } // if
    else if (numItems <= LARGE_LOOT_CHANCE) {
        numItems = LARGE_LOOT;
    } // if
    else if (numItems <= MEDIUM_LOOT_CHANCE) {
        numItems = MEDIUM_LOOT;
    } // else if
    else if (numItems <= SMALL_LOOT_CHANCE) {
        numItems = SMALL_LOOT;
    } // else if
    else {
        numItems = 0;
    } // else

    for (int i = 0; i < numItems; i++) {
        item = ItemGenerator::getInstance().generateItem(level);
        result->addItem(item);
    } // for

    return result;
} // generateChest