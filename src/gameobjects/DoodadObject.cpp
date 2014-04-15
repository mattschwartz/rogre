/**
 * Included files
 */
#include "DoodadObject.h"
#include "src/doodad/Doodad.h"

/**
 * Data
 */
DoodadObject::DoodadObject(Doodad *doodad, Ogre::Vector3 pos) : GameObject(pos) {
    this->doodad = doodad;
} // constructor

void DoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
} // createObject

void DoodadObject::update(const Ogre::FrameEvent &evt) {
} // update

bool DoodadObject::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void DoodadObject::mouseMoved(const OIS::MouseEvent &evt) {
} // mouseMoved

void DoodadObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mousePresesd

void DoodadObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
