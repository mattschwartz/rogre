/**
 * Included files
 */
#include "Player.h"
#include "items/Item.h"
#include "items/Equippable.h"
#include "entities/player/Inventory.h"

/**
 * Data
 */
Player::Player(int level, std::string name) : Entity(level, name) {
    this->gold = 0;
    this->timePlayed = time(NULL);
    this->inventory = new Inventory();
} // constructor

void Player::equipItem(Equippable *equippable) {
    Equippable *equippedItem = getEquippedItemAt(equippable->getSlotId());
    std::vector<affix_t> itemAffixes;

    if (equippedItem != NULL) {
        itemAffixes = equippedItem->getAffixes();

        for (affix_t affix : itemAffixes) {
            attributes[affix.attr] -= affix.amount;
        } // for
    } // if
    
    itemAffixes = equippable->getAffixes();
        
    for (affix_t affix : itemAffixes) {
            attributes[affix.attr] -= affix.amount;
    } // for
} // equipItem

Equippable *Player::getEquippedItemAt(int slotId) {
    if (slotId < 0 || slotId >= EQUIPMENT_SLOTS) {
        return NULL;
    } // if

    return equippedItems[slotId];
} // getEquippedItemAt

Inventory *Player::getInventory() {
    return inventory;
} // getInventory
