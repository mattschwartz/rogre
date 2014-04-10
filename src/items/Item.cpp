#include "Item.h"

/**
 * Constructor for a new Item
 *
 * @param id
 * @param level The level of the Item
 * @param goldWorth The amount the item is worth in gold, used for valuing a 
 *                  player's total worth
 * @param stackSize The number of this Item in a single stack
 * @param name The name of the Item, displayed to the user in the game
 * @param numAffixes The number of affixes present on this item
 */
Item::Item(int id, int level, int goldWorth, int stackSize, std::string name) {
    this->id = id;
    this->level = level;
    this->goldWorth = goldWorth;
    this->stackSize = stackSize;
    this->name = name;
} // constructor

/**
 * Increment the stack size of the item when the Item is incremented.
 */
Item &Item::operator++() {
    this->stackSize++;
    return *this;
} // operator++

/**
 * Compare an Item to this one for equality, this method is overridden for 
 * different types of Items.
 *
 * @param item The Item to compare this one to
 */
bool Item::operator==(const Item &item) {
    return false;
} // operator==

/**
 * 
 * @return Returns the id of this Item.
 */
int Item::getId() {
    return this->id;
} // getId

/**
 * Sets the ID of the Item to the provided argument.
 *
 * @param id The new id of the Item
 */
void Item::setId(int id) {
    this->id = id;
} // setId

/**
 * @return Returns the worth of the Item in gold
 */
int Item::getGoldWorth() {
    return this->goldWorth;
} // getGoldWorth

/**
 * Sets the gold worth of the Item to the provided argument.
 * 
 * @param goldWorth The new worth of the Item in gold
 */
void Item::setGoldWorth(int goldWorth) {
    this->goldWorth = goldWorth;
} // setGoldWorth

/**
 * @return Returns the stack size of the Item
 */
int Item::getStackSize() {
    return this->stackSize;
} // getStackSize

/**
 * Sets the stack size of the Item to the provided argument.
 *
 * @param stackSize The new stack size of the Item
 */
void Item::setStackSize(int stackSize) {
    this->stackSize = stackSize;
} // setStackSize
