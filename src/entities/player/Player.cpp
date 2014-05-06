/**
 * Included files
 */
#include "Player.h"
#include "src/items/Item.h"
#include "src/items/Equippable.h"
#include "src/entities/player/Inventory.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/DeathMenu.h"

/**
 * Data
 */
Player::Player(int level, std::string name) : Entity(level, name) {
    this->timePlayed = 0;
    this->inventory = new Inventory();
} // constructor

double Player::getCurrentHitpoints() {
    return currentHitpoints;
} // getCurrentHitpoints

int Player::getScore() {
    int score = 0;

    for (Item *item : inventory->getItems()) {
        score += item->getGoldWorth();
    } // for

    return score + timePlayed;
} // getScore

std::string Player::getName() {
    return name;
} // getName

void Player::equipItem(Equippable *equippable) {
    Equippable *equippedItem = getEquippedItemAt(equippable->getSlotid());
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

Ogre::Real Player::getTimePlayed() {
    return timePlayed;
} // getTimePlayed

void Player::updateTimePlayed(Ogre::Real secondsPassed) {
    timePlayed += secondsPassed;
} // updateTimePlayed

void Player::onSpawn() {
} // onSpawn

void Player::onDeath() {
    GUIManager::getInstance().deathMenu->show();
    // write score to file
} // onDeath

void Player::onDamageDealt() {
}  // onDamageDealt

void Player::onDamageTaken() {
} // onDamageTaken
