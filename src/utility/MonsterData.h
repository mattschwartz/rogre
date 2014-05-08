#ifndef _MONSTER_DATA_H_
#define _MONSTER_DATA_H_

/**
 * Included files
 */
#include <vector>
#include <map>
#include <string>

const int FIRST_NAME = 0;
const int LAST_NAME = 1;
const int PREFIX_TITLE_NAME = 2;
const int SUFFIX_TITLE_NAME = 3;

class MonsterData {
private:
    std::map<int, std::vector<std::string>> monsterNames;
    MonsterData() {}
    MonsterData(MonsterData const&);
    void operator=(MonsterData const&);
    std::string getRandomName(int nameId);

public:
    static MonsterData &getInstance() {
        static MonsterData instance;
        return instance;
    } // getInstance

    void init();
    std::string getFullName(bool hasPrefix, bool hasSuffix);
};

#endif
