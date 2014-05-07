/**
 * Included files
 */
#include "MonsterGenerator.h"
#include "ItemGenerator.h"
#include "src/utility/MonsterData.h"
#include "src/entities/Entity.h"
#include "src/entities/monsters/GoblinEntity.h"
#include "src/items/Item.h"

const int RARE_CHANCE = 50;
const int REALLY_RARE_CHANCE = 50;
const int DROP_ITEM_CHANCE = 40;

MonsterGenerator::MonsterGenerator() {
    MonsterData::getInstance().init();
} // constructor

Entity *MonsterGenerator::generateMonster(int level, int monsterDifficulty) {
    bool drop = (rand() % 100) <= DROP_ITEM_CHANCE;
    Entity *result;
    Item *item = NULL;

    if (drop) {
        item = ItemGenerator::getInstance().generateItem(level);
    } // if
    result = new GoblinEntity(level, monsterDifficulty, getName());
    result->setDrop(item);

    return result;
} // generateMonster

std::string MonsterGenerator::getName() {
    bool isRare;
    bool isReallyRare;

    isRare = (rand() % 100) <= RARE_CHANCE;
    isReallyRare = isRare && ((rand() % 100) <= REALLY_RARE_CHANCE);

    return MonsterData::getInstance().getFullName(isRare, isReallyRare);
} // getName
