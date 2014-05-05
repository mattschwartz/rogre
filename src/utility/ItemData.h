#ifndef _ITEM_DATA_H_
#define _ITEM_DATA_H_

/**
 * Included files
 */
#include "src/items/Affix.h"
#include "src/utility/MathHelper.h"
#include "src/items/Equippable.h"
#include <sstream>
#include <vector>
#include <map>

struct affixdata {
    int maxAttributes;
    struct MathHelper::range<int> levelRange;
    struct MathHelper::range<double> healthRange;
    struct MathHelper::range<double> armorRange;
    struct MathHelper::range<double> strengthRange;
};

class ItemData {
private:
    ItemData() {}
    ItemData(ItemData const&);
    void operator=(ItemData const&);
    void initItemData();
    void initAdjectives();
    void initItemNames();
    void initArmorNames();

public:
    struct affixdata flimsyItems;
    struct affixdata sturdyItems;
    struct affixdata solidItems;
    struct affixdata unbreakableItems;
    static std::vector<std::string> prefixAdjectives;
    static std::vector<std::string> suffixAdjectives;
    static std::vector<std::string> baseItemNames;
    static std::map<equipmentSlot_t, std::string> baseArmorNames;

    static ItemData &getInstance() {
        static ItemData instance;
        return instance;
    } // getInstance

    void init();
    struct affixdata getAffixData(int itemType);
};

#endif
