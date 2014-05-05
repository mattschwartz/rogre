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
    Equippable(int level);
    Equippable(int level, int goldWorth, int stackSize, std::string name, int numAffixes, affix_t *affixes);

    void setSlotid(equipmentSlot_t slotid);
    equipmentSlot_t getSlotid();
    int getNumAffixes();
    std::vector<affix_t> getAffixes();
    void addAffix(affix_t affix);
};

#endif
