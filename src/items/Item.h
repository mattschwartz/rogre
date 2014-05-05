#ifndef _ITEM_H_
#define _ITEM_H_

/**
 * Included files
 */
#include <string>
#include <vector>
#include "Affix.h"

/**
 * Data
 */
class Item {
protected:
    int level;
    int goldWorth;
    int stackSize;
    int numAffixes;
    std::string name;
    std::string description;

public:
    Item(int level);
    Item(int level, int goldWorth, int stackSize, std::string name);

    /**
     * Overriding operators
     */
    Item &operator++();
    bool operator==(const Item &item);

    /**
     * Getters & Setters
     */
    int getGoldWorth();
    void setGoldWorth(int goldWorth);
    int getStackSize();
    void setStackSize(int stackSize);
    void setName(std::string name);
    std::string getName();
    std::string pickupText();
    std::string getDescription();
    void setDescription(std::string text);
};

#endif
