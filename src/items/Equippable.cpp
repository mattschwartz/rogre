/**
 * Included files
 */
#include <stdexcept>
#include "Equippable.h"
#include "src/entities/Entity.h"
#include "src/entities/player/Player.h"

Equippable::Equippable(int level) :
    Item(level) {
    equippable = true;
    equipped = false;
} // constructor

Equippable::Equippable(int level, int goldWorth, int stackSize, std::string name, int numAffixes, affix_t *affixes) : 
    Item(level, goldWorth, stackSize, name) {
    for (int i = 0; i < numAffixes; i++) {
        this->affixes.push_back(affixes[i]);
    } // for
    equippable = true;
    equipped = false;
} // constructor

void Equippable::setSlotid(equipmentSlot_t slotid) {
    this->equipmentSlot = slotid;
} // setSlotid

bool Equippable::isEquipped() {
    return equipped;
} // isEquipped

void Equippable::setEquipped(bool value) {
    equipped = value;
} // setEquipped

/**
 * @return Returns the slot id into which this Equippable item fits
 */
equipmentSlot_t Equippable::getSlotid() {
    return equipmentSlot;
} // getSlotid

/**
 * @return Returns the number of affixes on the Item
 */
int Equippable::getNumAffixes() {
    return affixes.size();
} // getNumAffixes

/**
 * @return Returns a copy of the affixes present on the Item.
 */
std::vector<affix_t> Equippable::getAffixes() {
    std::vector<affix_t> affixCopy;

    for (affix_t affix : affixes) {
        affixCopy.push_back(affix);
    } // for

    return affixCopy;
} // getAffixes

void Equippable::addAffix(affix_t affix) {
    affixes.push_back(affix);
} // addAffix
