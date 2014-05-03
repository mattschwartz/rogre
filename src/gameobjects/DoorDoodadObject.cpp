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
    if (facing == Ogre::Vector3::UNIT_X) {
        rollBy = Ogre::Degree(90);
    } // if
    else {
        rollBy = Ogre::Degree(0);
    } // else
} // setFacing

void DoorDoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	doodadNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("ChestDoodad", id));
	doodadEntity = sceneMgr.createEntity(concat<int>("ChestDoodadEntity", id), "Door1.mesh");
	doodadEntity->setCastShadows(false);

	doodadNode->scale(0.5, 0.5, 0.5);
	doodadNode->attachObject(doodadEntity);
    doodadNode->setPosition(position);
    doodadNode->yaw(Ogre::Degree(rollBy));
} // createObject

void DoorDoodadObject::show() {
} // show

void DoorDoodadObject::hide() {
} // hide

void DoorDoodadObject::update(const Ogre::FrameEvent &evt) {
} // update
