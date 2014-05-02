/**
 * Included files
 */
#include "ChestDoodadObject.h"
#include "src/doodad/ChestDoodad.h"
#include "src/utility/StringHelper.h"

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, float x, float z) :
    DoodadObject(x, 2, z) {
    this->chest = chest;
} // constructor

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, Ogre::Vector3 pos) :
    DoodadObject(pos) {
    this->chest = chest;
} // constructor

void ChestDoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	doodadNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("ChestDoodad", id));
	doodadEntity = sceneMgr.createEntity(concat<int>("ChestDoodadEntity", id), "chest.mesh");
    doodadEntity->setMaterialName("Chest Wood");
	doodadEntity->setCastShadows(false);

	doodadNode->scale(2, 2, 2);
	doodadNode->attachObject(doodadEntity);
	doodadNode->setPosition(position);

    doodadNode->pitch(Ogre::Degree(90));
} // createObject

void ChestDoodadObject::show() {
} // show

void ChestDoodadObject::hide() {
} // hide

void ChestDoodadObject::update(const Ogre::FrameEvent &evt) {
} // update
