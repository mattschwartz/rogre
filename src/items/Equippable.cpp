/**
 * Included files
 */
#include "Equippable.h"
#include "entities/Entity.h"
#include "entities/player/Player.h"

/**
 * Defines
 */

/**
 * Data
 */
Equippable::Equippable(int id, int level, int goldWorth, int stackSize, std::string name, int numAffixes, affix_t *affixes) {
    this->id = id;
    this->level = level;
    this->goldWorth = goldWorth;
    this->stackSize = stackSize;
    this->name = name;

    numAffixes = numAffixes > MAX_AFFIXES ? MAX_AFFIXES : numAffixes;

    if (sizeof(affixes) != numAffixes * sizeof(affix_t)) {
        throw std::invalid_argument("numAffixes must equal the number of affixes provided");
    } // if

    for (int i = 0; i < numAffixes; i++) {
        this->affixes.push_back(affixes[i]);
    } // for
} // constructor

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
