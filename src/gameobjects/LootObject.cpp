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
#include "src/gui/GUIManager.h"
#include "src/gui/menu/ingamemenu/InGameMenu.h"
#include "src/sound/SoundEffect.h"
#include "src/sound/SoundManager.h"

LootObject::LootObject(Item *item, float x, float z) : 
    GameObject(Ogre::Vector3(x, 2.0f, z)) {
    this->item = item;
    this->id = lootCount++;
} // constructor

LootObject::LootObject(Item *item, Ogre::Vector3 pos) : 
    GameObject(Ogre::Vector3(pos.x, 2.0f, pos.z)) {
    this->item = item;
    this->id = lootCount++;
} // constructor

void LootObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	objectEntity = sceneMgr.createEntity(concat<int>("LootEntity", id), "Bag.mesh");
	objectEntity->setCastShadows(true);
    bounceUp = true;
    show();
} // createObject

void LootObject::show() {
    Ogre::SceneManager *sceneMgr;
	using namespace StringHelper;
    visible = true;

    sceneMgr = ObjectManager::getInstance().getSceneManager();
    objectNode = sceneMgr->getRootSceneNode()->createChildSceneNode(concat<int>("LootNode", id));

	objectNode->attachObject(objectEntity);
	objectNode->scale(0.25f, 0.25f, 0.25f);
	objectNode->setPosition(position);
} // show

void LootObject::hide() {
    visible = false;
    remove = true;

    position.y = 100.0f;
    objectNode->setVisible(false);
    objectNode->setPosition(position);
    ObjectManager::getInstance().destroySceneNode("LootNode", id);
    GUIManager::getInstance().inGameMenu->appendText(item->pickupText());
    // add to player inventory
    Player *player = World::getInstance().getCurrentPlayer();
    GUIManager::getInstance().inGameMenu->addItemToInventory(player, item);
    SoundManager::getInstance().LOOT_ITEM_SOUND->play();
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

    if (diff.x <= 1.0f && diff.z <= 1.0f) {
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

    objectNode->setPosition(position);
} // bounce
