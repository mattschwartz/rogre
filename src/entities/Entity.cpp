/**
 * Included files
 */
#include "Entity.h"
#include "src/items/Item.h"
#include "src/gui/menu/ingamemenu/InGameMenu.h"
#include "src/gui/GUIManager.h"
#include "src/utility/StringHelper.h"

/**
 * Data
 */
Entity::Entity(int level, int monsterPower, std::string name) {
    this->level = level;
    this->monsterPower = monsterPower;
    this->name = name;
    drop = NULL;

    attributes[strength] = 50.0 * (1 + (int)((double)level/100.0)) * ((double)monsterPower/100.0);
    attributes[hitpoints] = 100.0 * (1 + (int)((double)level/100.0)) * ((double)monsterPower/100.0);
    attributes[armor] = 25.0 * (1 + (int)((double)level/100.0)) * ((double)monsterPower/100.0);

    currentHitpoints = attributes[hitpoints];
} // constructor

std::string Entity::getName() {
    return name;
} // getName

int Entity::getLevel() { 
    return level;
} // getLevel

void Entity::setDrop(Item *drop) {
    this->drop = drop;
} // setDrop

Item *Entity::getDrop() {
    return drop;
} // getDrop

/**
 * This function is invoked whenever the Entity is spawned into 
 * the Game World
 */
void Entity::spawn() {
    onSpawn();
} // spawn

bool Entity::isDead() {
    return currentHitpoints <= 0.0;
} // isDead

/**
 * This function is invoked whenever the Entity is killed
 * 
 * @param slayer The Entity who dealt the final, killing blow
 */
void Entity::die(Entity *slayer) {
    onDeath();
    
    GUIManager::getInstance().inGameMenu->appendText(name + " has been slain.");
} // die

double Entity::getAttribute(attribute_t attribute) {
    return attributes[attribute];
} // getAttribute

/**
 * Determines the amount of damage to deal on the next hit,
 * invoked whenever this Entity is to deal damage to another.
 * This damage is increased by the amount of Strength the Entity
 * has and whether or not the hit critically hits for double 
 * damage.
 *
 * @return Returns the damage dealt
 */
double Entity::calculateHit() {
    onDamageDealt();

    return 10.0;
} // calculateHit

/**
 * This function is invoked whenever the Entity is hit by
 * another Entity. If its current health falls to 0, it dies.
 * 
 * @param amount The amount of damage dealt to this Entity
 * @param aggressor This is the Entity who has attacked this Entity
 */
void Entity::takeDamage(double amount, Entity *aggressor) {
    currentHitpoints -= amount;
    onDamageTaken();

    GUIManager::getInstance().inGameMenu->appendText(StringHelper::concat<double>(name + " is damaged for ", amount) + ".");
    
    if (currentHitpoints <= 0) {
        die(aggressor);
    } // if
} // takeDamage
