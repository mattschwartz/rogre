#ifndef _EQUIPPABLE_H_
#define _EQUIPPABLE_H_

/**
 * Included files
 */
#include "Item.h"

/**
 * Forward declarations
 */
class Player;
typedef enum equipmentSlot_t;

/**
 * Data
 */
class Equippable : public Item {
private:
    equipmentSlot_t equipmentSlot;
    std::vector<affix_t> affixes;

public:
    Equippable(int id, int level, int goldWorth, int stackSize, std::string name, int numAffixes, affix_t *affixes);
    ~Equippable();
    int getSlotId();
    int getNumAffixes();
    std::vector<affix_t> getAffixes();
};

#endif
