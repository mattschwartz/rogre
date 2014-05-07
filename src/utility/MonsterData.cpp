/**
 * Included files
 */
#include "MonsterData.h"
#include "src/entities/Entity.h"
#include "src/entities/monsters/GoblinEntity.h"
#include "src/entities/monsters/SkeletonEntity.h"
#include "src/utility/filesys/FileManager.h"
#include "src/utility/StringHelper.h"

const std::string MONSTER_NAMES_FILE_PATH = "data/monsterNames.txt";

void MonsterData::init() {
    using namespace std;

    int nameId;
    FileManager &fileManager = FileManager::getInstance();
    fstream *file;
    string line;
    vector<string> split;
    string first, second;

    file = fileManager.openFile(MONSTER_NAMES_FILE_PATH);

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

        nameId = atoi(first.c_str());
        if (nameId >= FIRST_NAME && nameId <= SUFFIX_TITLE_NAME) {
            monsterNames[nameId].push_back(second);
        } // if
    } // while

    fileManager.closeFile(file);
} // init

std::string MonsterData::getFullName(bool hasPrefix, bool hasSuffix) {
    std::stringstream result;

    if (hasPrefix) {
        result << getRandomName(PREFIX_TITLE_NAME) << " ";
    } // if

    result << getRandomName(FIRST_NAME) << " ";
    result << getRandomName(LAST_NAME);

    if (hasSuffix) {
        result << ", " << getRandomName(SUFFIX_TITLE_NAME);
    } // if

    return result.str();
} // getFullName

std::string MonsterData::getRandomName(int nameId) {
    int ran = rand() % monsterNames[nameId].size();
    auto iter = monsterNames[nameId].begin();
    std::string result = "???";

    std::advance(iter, ran);
    if (!iter->empty()) {
        result = iter->c_str();
    } // if

    return result;
} // getRandomName
