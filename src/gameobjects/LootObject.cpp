/**
 * Included files
 */
#include "LootObject.h"
#include "src/items/Item.h"

/**
 * Data
 */
LootObject::LootObject(Item *item, float x, float y, float z) : 
    item(item),
    GameObject(Ogre::Vector3(x, y, z)) {
} // constructor

LootObject::LootObject(Item *item, Ogre::Vector3 pos) : 
    item(item),
    GameObject(pos) {
} // constructor

void LootObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
} // createObject

void LootObject::update(const Ogre::FrameEvent &evt) {
} // update

bool LootObject::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void LootObject::keyPressed(const OIS::KeyEvent &arg) {}

void LootObject::mouseMoved(const OIS::MouseEvent &evt) {
} // mouseMoved

void LootObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mousePresesd

void LootObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
