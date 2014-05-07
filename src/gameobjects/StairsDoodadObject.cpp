/**
 * Included files
 */
#include "StairsDoodadObject.h"
#include "src/world/World.h"
#include "src/world/Zone.h"
#include "src/utility/StringHelper.h"
#include "src/sound/SoundEffect.h"
#include "src/sound/SoundManager.h"

StairsDoodadObject::StairsDoodadObject(float x, float z) :
    DoodadObject(x, -1.8f, z) {
} // constructor

StairsDoodadObject::StairsDoodadObject(Ogre::Vector3 pos) :
    DoodadObject(pos.x, -1.8f, pos.z) {
} // constructor

void StairsDoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	objectEntity = sceneMgr.createEntity(concat<int>("StairsDoodad", id), "cube.mesh");
    objectEntity->setMaterialName("Examples/StairsTexture");
	objectEntity->setCastShadows(false);

    objectNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("StairsDoodad", id));
	objectNode->attachObject(objectEntity);
	objectNode->scale(0.05f, 0.05f, 0.05f);
	objectNode->setPosition(position);
} // createObject

void StairsDoodadObject::interact() {
    World::getInstance().descend();
    SoundManager::getInstance().DESCEND_STAIRS_SOUND->play();
} // interact

void StairsDoodadObject::show() {
    objectNode->setVisible(true, true);
} // show

void StairsDoodadObject::hide() {
    objectNode->setVisible(false, false);
    position.y += 100.0f;
    objectNode->setPosition(position);
} // hide

void StairsDoodadObject::update(const Ogre::FrameEvent &evt) {
} // update
