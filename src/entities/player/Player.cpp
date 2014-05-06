/**
 * Included files
 */
#include "Player.h"
#include "src/items/Item.h"
#include "src/items/Equippable.h"
#include "src/entities/player/Inventory.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/DeathMenu.h"
#include "src/gui/menu/ingamemenu/InGameMenu.h"
#include "src/utility/StringHelper.h"

/**
 * Data
 */
Player::Player(int level, std::string name) : Entity(level, 100, name) {
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

void Player::die(Entity *slayer) {
    GUIManager::getInstance().deathMenu->show();
    GUIManager::getInstance().deathMenu->setSlainBy(slayer->getName());
} // die

void Player::takeDamage(double amount, Entity *aggressor) {
    currentHitpoints -= amount;

    GUIManager::getInstance().inGameMenu->appendText(StringHelper::concat<double>("You are damaged for ", amount) + ".");
    
    if (currentHitpoints <= 0) {
        die(aggressor);
    } // if
} // takeDamage

double Player::calculateHit() {
    double result = 99.0f;

    return result;
} // calculateHit
