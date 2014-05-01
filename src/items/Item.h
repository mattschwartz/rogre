#ifndef _ITEM_H_
#define _ITEM_H_

/**
 * Included files
 */
#include <string>
#include <vector>
#include "Affix.h"

/**
 * Defines
 */
#define MAX_AFFIXES 3

/**
 * Data
 */
class Item {
protected:
    int id;
    int level;
    int goldWorth;
    int stackSize;
    int numAffixes;
    std::string name;

public:
    Item(int id, int level, int goldWorth, int stackSize, std::string name);

    /**
     * Overriding operators
     */
    Item &operator++();
    bool operator==(const Item &item);

    /**
     * Getters & Setters
     */
    int getId();
    void setId(int id);
    int getGoldWorth();
    void setGoldWorth(int goldWorth);
    int getStackSize();
    void setStackSize(int stackSize);
    void setName(std::string name);
    std::string getName();
    std::string pickupText();
};

#endif
