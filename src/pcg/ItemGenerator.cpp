/** 
 * Included files
 */
#include "ItemGenerator.h"
#include "src/items/Item.h"
#include "src/items/Equippable.h"

Item *ItemGenerator::generateItem(int monsterLevel) {
    struct affixdata itemData;
    Item *result = new Item(monsterLevel);

    return result;
} // generateItem

Equippable *ItemGenerator::generateEquippable(int monsterLevel) {
    struct affixdata itemData;
    Equippable *result = new Equippable(monsterLevel);
    
    itemData = ItemData::getInstance().getAffixData(monsterLevel);

    for (int i = 0; i < itemData.maxAttributes; i++) {
        result->addAffix(createAffix(itemData));
    } // for

    return result;
} // generateEquippable

affix_t ItemGenerator::createAffix(struct affixdata data) {
    int attr;
    double amount;
    affix_t result;

    attr = rand() % 3;
    switch (attr) {
        case 0:
            result.attr = strength;
            amount = MathHelper::tRand<double>(data.strengthRange.min, 
                data.strengthRange.max);
            break;
        case 1:
            result.attr = hitpoints;
            amount = MathHelper::tRand<double>(data.healthRange.min, 
                data.healthRange.max);
            break;
        case 2:
            result.attr = armor;
            amount = MathHelper::tRand<double>(data.armorRange.min, 
                data.armorRange.max);
            break;
    } // switch-case

    return result;
} // createAffix
