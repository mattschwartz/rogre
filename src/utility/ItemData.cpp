/**
 * Included files
 */
#include "ItemData.h"
#include "src/utility/filesys/FileManager.h"

/**
 * Defines
 */
#define RESOURCE_FILE_PATH "media/res/"
const std::string PREFIX_ADJECTIVES_FILE_PATH = RESOURCE_FILE_PATH + std::string("prefixAdjectives.txt");
const std::string SUFFIX_ADJECTIVES_FILE_PATH = RESOURCE_FILE_PATH + std::string("suffixAdjectives.txt");
const std::string BASE_ITEM_NAMES_FILE_PATH = RESOURCE_FILE_PATH + std::string("baseItemNames.txt");
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

    file = fileManager.openFile(PREFIX_ADJECTIVES_FILE_PATH);

    while (!file->eof()) {
        line = fileManager.readLine(file);
        prefixAdjectives.push_back(line);
    } // while

    fileManager.closeFile(file);

    file = fileManager.openFile(SUFFIX_ADJECTIVES_FILE_PATH);

    while (!file->eof()) {
        line = fileManager.readLine(file);
        suffixAdjectives.push_back(line);
    } // while

    fileManager.closeFile(file);
} // initAdjectives

void ItemData::initItemNames() {
    FileManager &fileManager = FileManager::getInstance();
    std::fstream *file;
    std::string line;

    file = fileManager.openFile(BASE_ITEM_NAMES_FILE_PATH);

    while (!file->eof()) {
        line = fileManager.readLine(file);
        baseItemNames.push_back(line);
    } // while

    fileManager.closeFile(file);
} // initItemNames

void ItemData::initArmorNames() {
    FileManager &fileManager = FileManager::getInstance();
    std::fstream *file;
    std::string line;
    std::stringstream ss;
    int first;
    std::string second;

    file = fileManager.openFile(BASE_ARMOR_NAMES_FILE_PATH);

    if (file == NULL) {
        return;
    } // if

    while (!file->eof()) {
        line = fileManager.readLine(file);
        
        if (line[0] == '#') {
            continue;
        } // if

        ss = std::stringstream(line);
        ss >> first;

        second = "";
        line = "";
        while (ss >> line) {
            second += line + " ";
        } // while

        second.substr(0, second.length() - 1);

        switch (first) {
            case helmet:
                baseArmorNames[helmet] = second;
                break;
            case chest:
                baseArmorNames[chest] = second;
                break;
            case gloves:
                baseArmorNames[gloves] = second;
                break;
            case boots:
                baseArmorNames[boots] = second;
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
    if (unbreakableItems.levelRange.inRange(itemLevel)) {
        return unbreakableItems;
    } // if
} // getAffixData
