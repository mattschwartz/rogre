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

    attributes[strength] = 50.0 * (1 + ((double)level / 10.0)) * ((double)monsterPower/100.0);
    attributes[hitpoints] = 100.0 * (1 + (int)((double)level/100.0)) * ((double)monsterPower/100.0);
    attributes[armor] = 25.0 * (1 + (int)((double)level/100.0)) * ((double)monsterPower/100.0);

    currentHitpoints = attributes[hitpoints];
} // constructor

void Entity::setName(std::string name) {
    this->name =name;
} // setName

std::string Entity::getName() {
    return name;
} // getName

int Entity::getLevel() { 
    return level;
} // getLevel

void Entity::setLevel(int level) {
    this->level = level;
} // setLevel

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

double Entity::getCurrentHitpoints() {
    return currentHitpoints;
} // getCurrentHitpoints

void Entity::setCurrentHitpoints(double value) {
    currentHitpoints = value;
} // setCurrentHitpoints

double Entity::getAttribute(attribute_t attribute) {
    return attributes[attribute];
} // getAttribute

void Entity::setAttribute(attribute_t attribute, double value) {
    if (attribute < 0 || attribute > 3) {
        return;
    } // if

    attributes[attribute] = value;
} // setAttribute

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

    return 15 * (1 + (attributes[strength] / 100.0));
} // calculateHit

double Entity::getDamageReduction(double damageTaken) {
    double reduction = (1 + (100.0 / attributes[armor]));

    return damageTaken * (reduction / 100.0);
} // getDamageReduction

/**
 * This function is invoked whenever the Entity is hit by
 * another Entity. If its current health falls to 0, it dies.
 * 
 * @param amount The amount of damage dealt to this Entity
 * @param aggressor This is the Entity who has attacked this Entity
 */
void Entity::takeDamage(double amount, Entity *aggressor) {
    using namespace StringHelper;
    double amountAbsorbed = getDamageReduction(amount);
    currentHitpoints -= amount - amountAbsorbed;
    onDamageTaken();

    GUIManager::getInstance().inGameMenu->appendText(concat<double>(name + " is damaged for ", amount) + 
        concat<double>(" (", amountAbsorbed) + " damage absorbed).");
    
    if (currentHitpoints <= 0) {
        die(aggressor);
    } // if
} // takeDamage
