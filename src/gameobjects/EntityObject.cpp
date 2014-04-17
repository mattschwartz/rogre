/**
 * Included files
 */
#include "EntityObject.h"

EntityObject::EntityObject(Entity *entity, float x, float y, float z) : GameObject(Ogre::Vector3(x, y, z)) {
    this->entity = entity;
} // constructor

EntityObject::EntityObject(Entity *entity, Ogre::Vector3 pos) : GameObject(pos) {
    this->entity = entity;
} // constructor

void EntityObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
} // createObject

void EntityObject::update(const Ogre::FrameEvent &evt) {
} // update

bool EntityObject::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void EntityObject::keyPressed(const OIS::KeyEvent &arg) {}

void EntityObject::mouseMoved(const OIS::MouseEvent &evt) {
} // mouseMoved

void EntityObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mousePresesd

void EntityObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
