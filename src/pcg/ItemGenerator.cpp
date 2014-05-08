/** 
 * Included files
 */
#include "ItemGenerator.h"
#include "src/items/Item.h"
#include "src/items/Equippable.h"

const static int ARMOR_DROP_CHANCE = 50;

Item *ItemGenerator::generateItem(int monsterLevel) {
    int goldWorth;
    int minWorth;
    int maxWorth;
    int ran;
    Item *result;
    std::pair<std::string, std::string> itemData;

    ran = rand() % 100;
    if (ran <= ARMOR_DROP_CHANCE) {
        return generateEquippable(monsterLevel);
    } // if

    result = new Item(monsterLevel);

    itemData = ItemData::getInstance().getRandomItem();
    minWorth = 100 * monsterLevel;
    maxWorth = 100 * (monsterLevel + 1);
    goldWorth = (rand() % maxWorth - minWorth) + minWorth;

    result->setName(itemData.first);
    result->setDescription(itemData.second);
    result->setGoldWorth(goldWorth);

    return result;
} // generateItem

Equippable *ItemGenerator::generateEquippable(int monsterLevel) {
    int goldWorth;
    int minWorth;
    int maxWorth;
    int numAffixes;
    struct affixdata itemData;
    Equippable *result = new Equippable(monsterLevel);
    equippableItem randomEquippable;
    
    itemData = ItemData::getInstance().getAffixData(monsterLevel);
    minWorth = 100 * monsterLevel;
    maxWorth = 100 * (monsterLevel + 1);
    goldWorth = (rand() % maxWorth - minWorth) + minWorth;
    numAffixes = rand() % itemData.maxAttributes;
    
    for (int i = 0; i < numAffixes; i++) {
        result->addAffix(createAffix(itemData));
    } // for

    randomEquippable = ItemData::getInstance().getRandomArmor();
    result->setSlotid(randomEquippable.first);
    result->setName(randomEquippable.second.first);
    result->setDescription(randomEquippable.second.second);
    result->setGoldWorth(goldWorth);

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

    result.amount = amount;

    return result;
} // createAffix
