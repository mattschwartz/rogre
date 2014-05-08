#ifndef _CHEST_DOODAD_H_
#define _CHEST_DOODAD_H_

/**
 * Included files
 */
#include "Doodad.h"
#include <vector>

class Item;

class ChestDoodad : public Doodad {
private:
    std::vector<Item*> contents;

public:
    ChestDoodad();
    void addItem(Item *item);
    std::vector<Item*> getContents();
};

#endif
