/**
 * Included files
 */
#include "LootObject.h"
#include "src/items/Item.h"
#include "src/utility/StringHelper.h"
#include "src/gameobjects/ObjectManager.h"
#include "src/world/World.h"
#include "src/utility/MathHelper.h"
#include "src/entities/player/Player.h"

LootObject::LootObject(Item *item, float x, float z) : 
    GameObject(Ogre::Vector3(x, 0.5f, z)) {
    this->item = item;
    this->id = lootCount++;
} // constructor

LootObject::LootObject(Item *item, Ogre::Vector3 pos) : 
    GameObject(pos) {
    this->item = item;
    this->id = lootCount++;
} // constructor

void LootObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	lootEntity = sceneMgr.createEntity(concat<int>("LootEntity", id), "sphere.mesh");
    lootEntity->setMaterialName("Examples/LootTexture");
	lootEntity->setCastShadows(true);
    bounceUp = true;
    show();
} // createObject

void LootObject::show() {
    Ogre::SceneManager *sceneMgr;
	using namespace StringHelper;
    visible = true;

    sceneMgr = ObjectManager::getInstance().getSceneManager();
    lootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(concat<int>("LootNode", id));

	lootNode->attachObject(lootEntity);
	lootNode->scale(0.005f, 0.005f, 0.005f);
	lootNode->setPosition(position);
} // show

void LootObject::hide() {
    visible = false;
    position.y = -100;
    lootNode->setPosition(position);
    ObjectManager::getInstance().destroySceneNode("LootNode", id);
    // add to player inventory
    //World::getInstance().getCurrentPlayer()->
} // hide

void LootObject::update(const Ogre::FrameEvent &evt) {
    using namespace MathHelper;
    Ogre::Vector3 playerPosition;
    Ogre::Vector3 diff;

    if (!visible) {
        return;
    } // if

    bounce();
    
    playerPosition = World::getInstance().getPlayerPosition();
    diff = playerPosition - position;
    diff.x = abs<float>(diff.x);
    diff.z = abs<float>(diff.z);

    if (diff.x <= 0.5f && diff.z <= 0.5f) {
        hide();
    } // if
} // update

void LootObject::bounce() {
    if (position.y >= 2) {
        bounceUp = false;
    } else if (position.y <= 0.5f) {
        bounceUp = true;
    }

    if (bounceUp) {
        position.y += 0.02f;
    } else {
        position.y -= 0.02f;
    } 

    lootNode->setPosition(position);
} // bounce
