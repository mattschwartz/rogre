/**
 * Included files
 */
#include "DoorDoodadObject.h"
#include "src/utility/StringHelper.h"

DoorDoodadObject::DoorDoodadObject(float x, float z) :
    DoodadObject(x, 0, z) {
} // constructor

DoorDoodadObject::DoorDoodadObject(Ogre::Vector3 pos) :
    DoodadObject(pos) {
} // constructor

void DoorDoodadObject::setFacing(Ogre::Vector3 facing) {
    if (facing == Ogre::Vector3::UNIT_X || facing == Ogre::Vector3::NEGATIVE_UNIT_X) {
        yawBy = Ogre::Degree(90);
    } // if
    else {
        yawBy = Ogre::Degree(0);
    } // else
} // setFacing

void DoorDoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	objectNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("DoorDoodad", id));
	objectEntity = sceneMgr.createEntity(concat<int>("DoorDoodadEntity", id), "Door1.mesh");
	objectEntity->setCastShadows(false);

	objectNode->scale(0.5, 0.5, 0.5);
	objectNode->attachObject(objectEntity);
    objectNode->setPosition(position);
    objectNode->yaw(Ogre::Degree(yawBy));
} // createObject

void DoorDoodadObject::show() {
} // show

void DoorDoodadObject::hide() {
} // hide

void DoorDoodadObject::update(const Ogre::FrameEvent &evt) {
} // update
