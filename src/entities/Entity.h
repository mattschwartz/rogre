#ifndef _ENTITY_H_
#define _ENTITY_H_

/**
 * Included files
 */
#include <string>

/**
 * Defines
 */
#define NUM_ATTRIBUTES 3
#define EQUIPMENT_SLOTS 4

typedef enum {
    strength = 0,
    hitpoints = 1,
    armor = 2
} attribute_t;

class Item;

/**
 * Data
 */
class Entity {
protected:
    int level;
    int monsterPower;
    double currentHitpoints;
    double attributes[NUM_ATTRIBUTES];
    std::string name;
    Item *drop;

public:
    Entity(int level, int monsterPower, std::string name);

    std::string getName();
    void setName(std::string name);
    int getLevel();
    void setLevel(int level);
    void setDrop(Item *drop);
    Item *getDrop();
    void spawn();
    bool isDead();
    virtual void die(Entity *slayer);
    double getCurrentHitpoints();
    void setCurrentHitpoints(double value);
    double getAttribute(attribute_t attribute);
    void setAttribute(attribute_t attribute, double value);
    virtual double calculateHit();
    virtual double getDamageReduction(double damageTaken);
    virtual void takeDamage(double amount, Entity *aggressor);

    /**
     * This optional function is invoked whenever the Entity is spawned into 
     * the game and provides the Entity a way of performing some action or
     * actions when it is created.
     */
    virtual void onSpawn() = 0;

    /**
     * This optional function is invoked whenever the Entity is killed and is
     * about to be removed from the Game World and provides the Entity a way
     * of performing some action or actions when it dies.
     */
    virtual void onDeath() = 0;

    /**
     * This optional function is invoked whenever the Entity attacks another
     * Entity and provides the Entity a way of performing some action or 
     * actions during this time.
     */
    virtual void onDamageDealt() = 0;

    /**
     * This optional function is invoked whenever the Entity receives damage
     * from another Entity and provides the Entity a way of performing some
     * action or actions during this time.
     */
    virtual void onDamageTaken() = 0;

};
#endif
