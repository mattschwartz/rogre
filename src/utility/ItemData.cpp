/**
 * Included files
 */
#include "ItemData.h"
#include "src/utility/filesys/FileManager.h"
#include "src/utility/StringHelper.h"
#include <iterator>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

/**
 * Defines
 */
#define RESOURCE_FILE_PATH "data/itemdata/"
const std::string PREFIX_ADJECTIVES_FILE_PATH = RESOURCE_FILE_PATH + std::string("prefixAdjectives.txt");
const std::string SUFFIX_ADJECTIVES_FILE_PATH = RESOURCE_FILE_PATH + std::string("suffixAdjectives.txt");
const std::string BASE_ITEM_FILE_PATH = RESOURCE_FILE_PATH + std::string("baseItems.txt");
const std::string BASE_ARMOR_NAMES_FILE_PATH = RESOURCE_FILE_PATH + std::string("baseArmorNames.txt");

const std::string DEFAULT_ITEM_DESCRIPTION = "An unusual item.";
const std::string DEFAULT_HELMET_DESCRIPTION = "Place on head for best results.";
const std::string DEFAULT_CHEST_DESCRIPTION = "Place on body for best results.";
const std::string DEFAULT_GLOVES_DESCRIPTION = "Place on hands for best results.";
const std::string DEFAULT_BOOTS_DESCRIPTION = "Place on feet for best results.";

const double FLIMSY_MIN_ATTR = 10.0;
const double FLIMSY_MAX_ATTR = 20.0;

const double STURDY_MIN_ATTR = 21.0;
const double STURDY_MAX_ATTR = 50.0;

const double SOLID_MIN_ATTR = 51.0;
const double SOLID_MAX_ATTR = 100.0;

const double UNBREAKABLE_MIN_ATTR = 101.0;
const double UNBREAKABLE_MAX_ATTR = 250.0;

void ItemData::init() {
    initItemData();
    initItemNames();
    initAdjectives();
    initArmorNames();
} // init

void ItemData::initItemData() {
    using namespace MathHelper;
    
    flimsyItems.maxAttributes = 2;
    flimsyItems.levelRange = range<int>(1, 5);
    flimsyItems.healthRange = range<double>(FLIMSY_MIN_ATTR, FLIMSY_MAX_ATTR);
    flimsyItems.armorRange = range<double>(FLIMSY_MIN_ATTR, FLIMSY_MAX_ATTR);
    flimsyItems.strengthRange = range<double>(FLIMSY_MIN_ATTR, FLIMSY_MAX_ATTR);
    
    sturdyItems.maxAttributes = 4;
    sturdyItems.levelRange = range<int>(6, 10);
    sturdyItems.healthRange = range<double>(STURDY_MIN_ATTR, STURDY_MAX_ATTR);
    sturdyItems.armorRange = range<double>(STURDY_MIN_ATTR, STURDY_MAX_ATTR);
    sturdyItems.strengthRange = range<double>(STURDY_MIN_ATTR, STURDY_MAX_ATTR);
    
    solidItems.maxAttributes = 4;
    solidItems.levelRange = range<int>(11, 15);
    solidItems.healthRange = range<double>(SOLID_MIN_ATTR, SOLID_MAX_ATTR);
    solidItems.armorRange = range<double>(SOLID_MIN_ATTR, SOLID_MAX_ATTR);
    solidItems.strengthRange = range<double>(SOLID_MIN_ATTR, SOLID_MAX_ATTR);
    
    unbreakableItems.maxAttributes = 6;
    unbreakableItems.levelRange = range<int>(16, 20);
    unbreakableItems.healthRange = range<double>(UNBREAKABLE_MIN_ATTR, UNBREAKABLE_MAX_ATTR);
    unbreakableItems.armorRange = range<double>(UNBREAKABLE_MIN_ATTR, UNBREAKABLE_MAX_ATTR);
    unbreakableItems.strengthRange = range<double>(UNBREAKABLE_MIN_ATTR, UNBREAKABLE_MAX_ATTR);
} // initItemData

void ItemData::initAdjectives() {
    FileManager &fileManager = FileManager::getInstance();
    std::fstream *file;
    std::string line;

    // prefix names
    file = fileManager.openFile(PREFIX_ADJECTIVES_FILE_PATH);

    if (file == NULL) {
        return;
    } // if

    while (!file->eof()) {
        line = fileManager.readLine(file);
        
        if (line[0] == '#') {
            continue;
        } // if

        prefixAdjectives.push_back(line);
    } // while

    fileManager.closeFile(file);

    // suffix names
    file = fileManager.openFile(SUFFIX_ADJECTIVES_FILE_PATH);

    if (file == NULL) {
        return;
    } // if

    while (!file->eof()) {
        line = fileManager.readLine(file);
        
        if (line[0] == '#') {
            continue;
        } // if

        suffixAdjectives.push_back(line);
    } // while

    fileManager.closeFile(file);
} // initAdjectives

void ItemData::initItemNames() {
    using namespace std;

    FileManager &fileManager = FileManager::getInstance();
    fstream *file;
    string line;
    vector<string> split;
    string first, second;

    file = fileManager.openFile(BASE_ITEM_FILE_PATH);

    if (file == NULL) {
        return;
    } // if

    while (!file->eof()) {
        line = fileManager.readLine(file);
        
        if (line[0] == '#') {
            continue;
        } // if

        split = StringHelper::split(line, ';');
        second = split.back();
        split.pop_back();
        first = split.back();

        baseItems[first] = second;
    } // while

    fileManager.closeFile(file);
} // initItemNames

void ItemData::initArmorNames() {
    using namespace std;

    FileManager &fileManager = FileManager::getInstance();
    fstream *file;
    string line;
    stringstream ss;
    int itemId;
    string name;
    string description;
    vector<string> strs;
    pair<string, string> nameDes;

    file = fileManager.openFile(BASE_ARMOR_NAMES_FILE_PATH);

    if (file == NULL) {
        return;
    } // if

    while (!file->eof()) {
        line = fileManager.readLine(file);
        
        if (line[0] == '#') {
            continue;
        } // if

        strs = StringHelper::split(line, ';');
        itemId = atoi(strs[0].c_str());
        name = strs[1];
        description = strs[2];

        switch (itemId) {
            case helmet:
                if (strncmp(description.c_str(), "", 1) == 0) {
                    description = DEFAULT_HELMET_DESCRIPTION;
                } // if
                
                nameDes = make_pair(name, description);
                baseArmorNames[helmet].push_back(nameDes);
                break;
            case chest:
                if (strncmp(description.c_str(), "", 1) == 0) {
                    description = DEFAULT_CHEST_DESCRIPTION;
                } // if
                
                nameDes = make_pair(name, description);
                baseArmorNames[chest].push_back(nameDes);
                break;
            case gloves:
                if (strncmp(description.c_str(), "", 1) == 0) {
                    description = DEFAULT_GLOVES_DESCRIPTION;
                } // if
                
                nameDes = make_pair(name, description);
                baseArmorNames[gloves].push_back(nameDes);
                break;
            case boots:
                if (strncmp(description.c_str(), "", 1) == 0) {
                    description = DEFAULT_BOOTS_DESCRIPTION;
                } // if
                
                nameDes = make_pair(name, description);
                baseArmorNames[boots].push_back(nameDes);
                break;
            default:
                continue;
        } // switch-case
    } // while

    fileManager.closeFile(file);
} // initArmorNames

struct affixdata ItemData::getAffixData(int itemLevel) {
    using namespace MathHelper;

    if (flimsyItems.levelRange.inRange(itemLevel)) {
        return flimsyItems;
    } // if
    if (sturdyItems.levelRange.inRange(itemLevel)) {
        return sturdyItems;
    } // if
    if (solidItems.levelRange.inRange(itemLevel)) {
        return solidItems;
    } // if

    return unbreakableItems;
} // getAffixData

std::string ItemData::getDescriptionForItem(std::string itemName) {
    return baseItems[itemName];
} // getDescriptionForItem

std::string ItemData::getRandomPrefix() {
    int ran = rand() % prefixAdjectives.size();

    return prefixAdjectives[ran];
}

std::string ItemData::getRandomSuffix() {
    int ran = rand() % suffixAdjectives.size();

    return suffixAdjectives[ran];
}

std::pair<std::string, std::string> ItemData::getRandomItem() {
    int ran = rand() % baseItems.size();
    auto iter = baseItems.begin();
    std::pair<std::string, std::string> result;

    std::advance(iter, rand() % baseItems.size());
    result.first = iter->first;
    result.second = iter->second;

    return result;
} // getRandomItem

equippableItem ItemData::getRandomArmor() {
    int ran = rand() % 4;
    equipmentSlot_t slotid;

    switch (ran) {
        case helmet:
            slotid = helmet;
            break;
        case chest:
            slotid = chest;
            break;
        case gloves:
            slotid = gloves;
            break;
        default:
            slotid = boots;
    } // switch-case

    ran = rand() % baseArmorNames[slotid].size();
    auto iter = baseArmorNames[slotid].begin();
    equippableItem result;

    std::advance(iter, ran);
    result.first = slotid;
    result.second.first = iter->first;
    result.second.second = iter->second;

    return result;
} // getRandomArmor
