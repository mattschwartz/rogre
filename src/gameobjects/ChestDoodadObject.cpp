/**
 * Included files
 */
#include "ChestDoodadObject.h"
#include "src/doodad/ChestDoodad.h"
#include "src/utility/StringHelper.h"

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, float x, float z) :
    DoodadObject(x, z) {
    this->chest = chest;
    this->id = doodadCount++;
} // constructor

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, Ogre::Vector3 pos) :
    DoodadObject(pos) {
    this->chest = chest;
    this->id = doodadCount++;
} // constructor

void ChestDoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	doodadNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("ChestDoodad", id));
	doodadEntity = sceneMgr.createEntity(concat<int>("ChestDoodadEntity", id), "ogrehead.mesh");
	doodadEntity->setCastShadows(true);

	doodadNode->scale(0.04f, 0.04f, 0.04f);
	doodadNode->attachObject(doodadEntity);
	doodadNode->setPosition(position);
} // createObject

void ChestDoodadObject::show() {
} // show

void ChestDoodadObject::hide() {
} // hide

void ChestDoodadObject::update(const Ogre::FrameEvent &evt) {
} // update
