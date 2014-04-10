#ifndef _EQUIPPABLE_H_
#define _EQUIPPABLE_H_

/**
 * Included files
 */
#include "Item.h"

/**
 * Defines
 */
typedef enum {
    helmet,
    chest,
    gloves,
    boots
} equipmentSlot_t;

/**
 * Forward declarations
 */
class Player;

/**
 * Data
 */
class Equippable : public Item {
private:
    equipmentSlot_t equipmentSlot;
    std::vector<affix_t> affixes;

public:
    Equippable(int id, int level, int goldWorth, int stackSize, std::string name, int numAffixes, affix_t *affixes);
    equipmentSlot_t getSlotId();
    int getNumAffixes();
    std::vector<affix_t> getAffixes();
};

#endif
