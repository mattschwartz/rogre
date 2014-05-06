/**
 * Included files
 */
#include "ChestDoodadObject.h"
#include "src/doodad/ChestDoodad.h"
#include "src/utility/StringHelper.h"

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, float x, float z) :
    DoodadObject(x, 1.2f, z) {
    this->chest = chest;
} // constructor

ChestDoodadObject::ChestDoodadObject(ChestDoodad *chest, Ogre::Vector3 pos) :
    DoodadObject(pos) {
    this->chest = chest;
} // constructor

void ChestDoodadObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	objectNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("ChestDoodad", id));
	objectEntity = sceneMgr.createEntity(concat<int>("ChestDoodadEntity", id), "chest.mesh");
    objectEntity->setMaterialName("Chest Wood");
	objectEntity->setCastShadows(false);

	objectNode->scale(2, 2, 2);
	objectNode->attachObject(objectEntity);
	objectNode->setPosition(position);

    objectNode->pitch(Ogre::Degree(90));
} // createObject

void ChestDoodadObject::show() {
} // show

void ChestDoodadObject::hide() {
} // hide

void ChestDoodadObject::update(const Ogre::FrameEvent &evt) {
} // update
