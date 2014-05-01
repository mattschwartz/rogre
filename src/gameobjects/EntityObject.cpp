/**
 * Included files
 */
#include "EntityObject.h"
#include "src/world/World.h"
#include "src/world/Zone.h"
#include "src/utility/StringHelper.h"
#include "src/utility/MathHelper.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "src/gameobjects/ObjectManager.h"

EntityObject::EntityObject(float x, float z) : GameObject(Ogre::Vector3(x, 0, z)) {
	this->id = entityCount++;
    this->range = 1.0f;
} // constructor

EntityObject::EntityObject(Ogre::Vector3 pos) : GameObject(pos) {
	this->id = entityCount++;
    this->range = 1.0f;
} // constructor

EntityObject::~EntityObject() {
    ObjectManager::getInstance().destroySceneNode("Entity", id);
} // destructor

