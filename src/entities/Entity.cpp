/**
 * Included files
 */
#include "Entity.h"
#include "src/items/Item.h"

/**
 * Data
 */
Entity::Entity(int level, std::string name) {
    this->level = level;
    this->name = name;

    attributes[strength] = 50.0 * (1 + (int)((double)level/100.0));
    attributes[hitpoints] = 100.0 * (1 + (int)((double)level/100.0));
    attributes[armor] = 25.0 * (1 + (int)((double)level/100.0));

    currentHitpoints = attributes[hitpoints];
} // constructor

/**
 * This function is invoked whenever the Entity is spawned into 
 * the Game World
 */
void Entity::spawn() {
    onSpawn();
} // spawn

/**
 * This function is invoked whenever the Entity is killed
 * 
 * @param slayer The Entity who dealt the final, killing blow
 */
void Entity::die(Entity *slayer) {
    // Remove this Entity from the Game World
    onDeath();
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
    return 1;
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
    
    if (currentHitpoints <= 0) {
        die(aggressor);
    } // if
} // takeDamage
