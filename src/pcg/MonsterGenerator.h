#ifndef _MONSTER_GENERATOR_H_
#define _MONSTER_GENERATOR_H_

/**
 * Included files
 */
#include <string>

class Entity;

class MonsterGenerator {
private:
    MonsterGenerator();
    MonsterGenerator(MonsterGenerator const&);
    void operator=(MonsterGenerator const&);
    bool isRare();
    std::string getName();

public:
    static MonsterGenerator &getInstance() {
        static MonsterGenerator instance;
        return instance;
    } // getInstance

    Entity *generateMonster(int level, int monsterDifficulty);
};

#endif
