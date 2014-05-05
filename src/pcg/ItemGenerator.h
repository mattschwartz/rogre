#ifndef _ITEM_GENERATOR_H_
#define _ITEM_GENERATOR_H_

#include "src/utility/ItemData.h"

class Item;
class Equippable;

class ItemGenerator {
private:
    ItemGenerator() {
        ItemData::getInstance().init();
    }
    ItemGenerator(ItemGenerator const&);
    void operator=(ItemGenerator const&);

public:
    static ItemGenerator &getInstance() {
        static ItemGenerator instance;
        return instance;
    } // getInstance

    Item *generateItem(int monsterLevel);
    Equippable *generateEquippable(int monsterLevel);
    affix_t createAffix(struct affixdata data);
};

#endif
