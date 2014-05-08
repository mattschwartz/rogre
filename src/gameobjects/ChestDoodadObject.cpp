/**
 * Included files
 */
#include "ChestDoodadObject.h"
#include "LootObject.h"
#include "src/doodad/ChestDoodad.h"
#include "src/gameobjects/ObjectManager.h"
#include "src/utility/StringHelper.h"
#include "src/sound/SoundEffect.h"
#include "src/sound/SoundManager.h"

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, float x, float z) :
    DoodadObject(x, 1.0f, z) {
    this->chest = chest;
} // constructor

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, Ogre::Vector3 pos) :
    DoodadObject(pos) {
    this->chest = chest;
} // constructor

void ChestDoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	objectNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("ChestDoodad", id));
	objectEntity = sceneMgr.createEntity(concat<int>("ChestDoodadEntity", id), "chest3.mesh");
	objectEntity->setCastShadows(false);

	objectNode->scale(0.4f, 0.4f, 0.4f);
	objectNode->attachObject(objectEntity);
	objectNode->setPosition(position);

    objectNode->pitch(Ogre::Degree(90));
    remove = false;
} // createObject

void ChestDoodadObject::interact() {
    Ogre::Vector3 lootPosition;
    LootObject *loot;

    for (Item *item : chest->getContents()) {
        lootPosition = position;
        
        lootPosition.x += Ogre::Real((rand() % 4) - 2.5);
        lootPosition.z += Ogre::Real((rand() % 4) - 2.5);

        loot = new LootObject(item, lootPosition);
        ObjectManager::getInstance().spawnObject(loot);
    } // for
    SoundManager::getInstance().CHEST_OPEN_SOUND->stop();
    SoundManager::getInstance().CHEST_OPEN_SOUND->play();
    hide();
} // openChest

void ChestDoodadObject::show() {
    remove = false;
    objectNode->setVisible(true, true);
} // show

void ChestDoodadObject::hide() {
    remove = true;
    position.y = 100.0f;
    objectNode->setPosition(position);
    objectNode->setVisible(false, false);
} // hide

void ChestDoodadObject::update(const Ogre::FrameEvent &evt) {
} // update
