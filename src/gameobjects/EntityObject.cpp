/**
 * Included files
 */
#include "EntityObject.h"
#include "src/utility/StringHelper.h"

EntityObject::EntityObject(Entity *entity, float x, float z) : GameObject(Ogre::Vector3(x, 0, z)) {
	this->id = entityCount++;
    this->entity = entity;
} // constructor

EntityObject::EntityObject(Entity *entity, Ogre::Vector3 pos) : GameObject(pos) {
	this->id = entityCount++;
    this->entity = entity;
} // constructor

void EntityObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	entityNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("Entity", id));
	entityEntity = sceneMgr.createEntity(concat<int>("EntityEntity", id), "ninja.mesh");
	entityEntity->setCastShadows(true);

	entityNode->scale(0.025f, 0.025f, 0.025f);
	entityNode->attachObject(entityEntity);
	entityNode->setPosition(position);

    mAnimationState = entityEntity->getAnimationState("Idle2");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
} // createObject

void EntityObject::update(const Ogre::FrameEvent &evt) {
} // update

bool EntityObject::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void EntityObject::keyPressed(const OIS::KeyEvent &arg) {
}

void EntityObject::mouseMoved(const OIS::MouseEvent &evt) {
} // mouseMoved

void EntityObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mousePresesd

void EntityObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
