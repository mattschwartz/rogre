/**
 * Included files
 */
#include "FileManager.h"
#include "src/entities/player/Player.h"
#include "src/entities/player/Inventory.h"
#include "src/items/Item.h"
#include "src/utility/ItemData.h"
#include "src/world/Zone.h"
#include "src/utility/StringHelper.h"
#include <cstring>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <Ogre.h>

static const std::string SAVE_DATA_META_FILE = "data/save/.savefiles";
static const std::string GRAVEYARD_FILE = "data/graveyard.txt";

void FileManager::init() {
} // init

std::vector<std::string> FileManager::getGraveyard() {
    using namespace std;
    string line;
    stringstream deathNote;
    vector<string> result;
    vector<string> split;
    string name, score, timePlayed, timeOfDeath;
    string filepath = GRAVEYARD_FILE;
    fstream file(filepath);

    if (!file.is_open()) {
        return result;
    } // if

    while (!file.eof()) {
        line = readLine(&file);

        if (line[0] == '#') {
            continue;
        } // if

        split = StringHelper::split(line, ';');
        name = split[0];
        score = split[1];
        timePlayed = split[2];
        timeOfDeath = split[3];

        deathNote.str("");
        deathNote.clear();

        char buf[10];
        sprintf(buf, "%.2f", atof(timePlayed.c_str()));
        timePlayed = string(buf);

        deathNote << name << " perished with a score of " << score << " after " << timePlayed << " seconds at " << timeOfDeath << ".";
        result.push_back(deathNote.str());
    } // while

    return result;
} // getGraveyard

void FileManager::addToGraveyard(Player *player) {
    using namespace std;
    ofstream file;

    file.open(GRAVEYARD_FILE, fstream::out | fstream::app);

    file << player->getName() << ";" << player->getScore() << ";" << player->getTimePlayed() << ";" << timestamp() << endl;
    file.close();
} // addToGraveyard

std::set<std::string> FileManager::getLoadablePlayers() {
    using namespace std;
    set<string> result;
    string playerName;
    ifstream savelist;

    savelist.open(SAVE_DATA_META_FILE);

    while (savelist.is_open() && !savelist.eof()) {
        getline(savelist, playerName);

        if (playerName.length() > 0) {
            result.insert(playerName);
        } // if
    } // while

    return result;
} // getLoadablePlayers

Player *FileManager::loadPlayer(std::string playerName, int *seed, int *monsterLevel, int *monsterDifficulty, bool *blindMode) {
    using namespace std;
    Player *player = new Player(1, playerName);;
    Item *item;
    string line;
    vector<string> split;
    string first, second;
    string filepath = "data/save/" + playerName + "_Save.sav";
    fstream file(filepath);

    if (!file.is_open()) {
        return player;
    } // if

    while (!file.eof()) {
        line = readLine(&file);

        if (line[0] == '#') {
            continue;
        } // if

        split = StringHelper::split(line, '=');
        second = split.back();
        split.pop_back();
        first = split.back();

        if (strncmp(first.c_str(), "name", 5) == 0) {
            player->setName(second);
        } // if
        else if (strncmp(first.c_str(), "level", 6) == 0) {
            player->setLevel(atoi(second.c_str()));
        } // else if
        else if (strncmp(first.c_str(), "hitpoints", 10) == 0) {
            player->setAttribute(hitpoints, atof(second.c_str()));
        } // else if
        else if (strncmp(first.c_str(), "currentHitpoints", 17) == 0) {
            player->setCurrentHitpoints(atof(second.c_str()));
        } // else if
        else if (strncmp(first.c_str(), "strength", 9) == 0) {
            player->setAttribute(strength, atof(second.c_str()));
        } // else if
        else if (strncmp(first.c_str(), "armor", 6) == 0) {
            player->setAttribute(armor, atof(second.c_str()));
        } // else if
        else if (strncmp(first.c_str(), "seed", 5) == 0) {
            *seed = atoi(second.c_str());
        } // else if
        else if (strncmp(first.c_str(), "monsterLevel", 13) == 0) {
            *monsterLevel = atoi(second.c_str());
        } // else if
        else if (strncmp(first.c_str(), "monsterDifficulty", 18) == 0) {
            *monsterDifficulty = atoi(second.c_str());
        } // else if
        else if (strncmp(first.c_str(), "blindMode", 10) == 0) {
            *blindMode = atoi(second.c_str()) != 0;
        } // else if
        else if (strncmp(first.c_str(), "timePlayed", 10) == 0) {
            player->setTimePlayed((Ogre::Real)atof(second.c_str()));
        } // else if
        else if (strncmp(first.c_str(), "isDead", 7) == 0) {
            if (atoi(second.c_str())) {
                // player is dead!!!??
                return player;
            } // if
        } // else if
        // must be an item
        else {
            item = new Item(*monsterLevel);
            item->setName(first);
            item->setDescription(ItemData::getInstance().getDescriptionForItem(first));
            item->setGoldWorth(atoi(second.c_str()));
            player->getInventory()->addItem(item);
        } // else
    } // while

    return player;
} // loadPlayer

void FileManager::updateSaveMetaFile(std::string playerName) {
    using namespace std;
    fstream file;
    set<string> savelist = getLoadablePlayers();

    savelist.insert(playerName);

    file.open(SAVE_DATA_META_FILE, fstream::out);

    for (string str : savelist) {
        file << str << endl;
    } // for

    file.close();
} // updateSaveMetaFile

void FileManager::savePlayer(int seed, Player *player, Zone *zone, bool blindMode) {
    using namespace std;
    string filePath = "data/save/" + player->getName() + "_Save.sav";
    ofstream savefile;

    savefile.open(filePath);

    savefile << "# This save file was automatically generated by the game on" << endl;
    savefile << "# " << timestamp() << "." << endl;
    savefile << "# Editing this file may corrupt it if it is malformed." << endl << endl;

    savefile << "name=" << player->getName() << endl;
    savefile << "level=" << player->getLevel() << endl;
    savefile << "currentHitpoints=" << player->getCurrentHitpoints() << endl;
    savefile << "hitpoints=" << player->getAttribute(hitpoints) << endl;
    savefile << "strength=" << player->getAttribute(strength) << endl;
    savefile << "armor=" << player->getAttribute(armor) << endl;
    savefile << "seed=" << seed << endl;
    savefile << "monsterLevel=" << zone->zoneLevel << endl;
    savefile << "monsterDifficulty=" << zone->monsterDifficulty << endl;
    savefile << "blindMode=" << blindMode << endl;
    savefile << "timePlayed=" << player->getTimePlayed() << endl;
    savefile << "isDead=" << (int)player->isDead() << endl;
    
    savefile << endl << "# Begin inventory list" << endl << endl;

    for (Item *item : player->getInventory()->getItems()) {
        savefile << item->getName() << "=" << item->getGoldWorth() << endl;
    } // for

    savefile << endl << "# End inventory list" << endl;

    savefile.close();

    updateSaveMetaFile(player->getName());
} // savePlayer

std::string FileManager::timestamp() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
} // timestamp

std::fstream *FileManager::openFile(std::string filepath) {
    std::fstream *result = new std::fstream();

    result->open(filepath);

    if (!result->is_open()) {
        return NULL;
    } // if

    return result;
} // openFile

void FileManager::closeFile(std::fstream *file) {
    file->close();
} // closeFile

std::string FileManager::readLine(std::fstream *file) {
    std::string result;

    std::getline(*file, result);

    if (result.length() <= 1) {
        return "#";
    }

    return result;
} // readLine
