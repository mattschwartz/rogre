/**
 * Included files
 */
#include "ItemData.h"
#include "src/utility/filesys/FileManager.h"
#include "src/utility/StringHelper.h"
#include <iterator>
#include <stdlib.h>

/**
 * Defines
 */
#define RESOURCE_FILE_PATH "data/itemdata/"
const std::string PREFIX_ADJECTIVES_FILE_PATH = RESOURCE_FILE_PATH + std::string("prefixAdjectives.txt");
const std::string SUFFIX_ADJECTIVES_FILE_PATH = RESOURCE_FILE_PATH + std::string("suffixAdjectives.txt");
const std::string BASE_ITEM_FILE_PATH = RESOURCE_FILE_PATH + std::string("baseItems.txt");
const std::string BASE_ARMOR_NAMES_FILE_PATH = RESOURCE_FILE_PATH + std::string("baseArmorNames.txt");

const double FLIMSY_MIN_ATTR = 1.0;
const double FLIMSY_MAX_ATTR = 10.0;

const double STURDY_MIN_ATTR = 11.0;
const double STURDY_MAX_ATTR = 20.0;

const double SOLID_MIN_ATTR = 21.0;
const double SOLID_MAX_ATTR = 30.0;

const double UNBREAKABLE_MIN_ATTR = 50.0;
const double UNBREAKABLE_MAX_ATTR = 100.0;

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
        itemId = atoi(strs.back().c_str());
        strs.pop_back();
        description = strs.back();
        strs.pop_back();
        name = strs.back();

        switch (itemId) {
            case helmet:
                baseArmorNames[helmet].first = name;
                baseArmorNames[helmet].second = description;
                break;
            case chest:
                baseArmorNames[chest].first = name;
                baseArmorNames[chest].second = description;
                break;
            case gloves:
                baseArmorNames[gloves].first = name;
                baseArmorNames[gloves].second = description;
                break;
            case boots:
                baseArmorNames[boots].first = name;
                baseArmorNames[boots].second = description;
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

std::pair<std::string, std::string> ItemData::getRandomItem() {
    int ran = rand() % baseItems.size();
    auto iter = baseItems.begin();
    std::pair<std::string, std::string> result;

    std::advance(iter, rand() % baseItems.size());
    result.first = iter->first;
    result.second = iter->second;

    return result;
} // getRandomItem
