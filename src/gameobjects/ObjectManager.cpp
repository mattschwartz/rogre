/** 
 * Included files
 */
#include "ObjectManager.h"
#include "GameObject.h"

/**
 * Data
 */

/**
 * Initializes the ObjectManager singleton class. This will allow GameObjects
 * to spawn themselves from anywhere in the code by using this interface. This
 * class must be initialized before that can happen.
 *
 * @param sceneMgr The ogre scene manager
 * @param *camera The ogre camera
 */
void ObjectManager::init(Ogre::SceneManager *sceneMgr, Ogre::Camera *camera) {
    this->sceneManager = sceneMgr;
    this->camera = camera;
} // init

void ObjectManager::destroyEntity(std::string name) {
	sceneManager->destroyEntity(name);
} // destroyEntity

void ObjectManager::destroySceneNode(std::string name) {
	sceneManager->destroySceneNode(name);
} // destroySceneNode

/**
 * Spawns the specified object within the game world. This object is stored
 * in a list and updated when the game has a rendered frame. All objects in
 * this game must be registered with the ObjectManager via this method.
 * 
 * @param object The object to be registered and spawned into the game
 */
void ObjectManager::spawnObject(GameObject *object) {
    objects.push_back(object);
    object->createObject(*sceneManager, camera);
} // spawnObject

/**
 * This method is invoked via the Ogre method when a frame is rendered.
 * It goes through all registered objects and invokes their update method
 * so they can execute whatever updates they must.
 *
 * @param evt
 */
void ObjectManager::update(const Ogre::FrameEvent &evt) {
    for (GameObject *o : objects) {
        o->update(evt);
    } // for
} // update

/**
 * May not be necessary - used for determining if the mouse is hovering
 * over an object
 * 
 * @param evt
 * @return
 */
bool ObjectManager::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void ObjectManager::keyPressed(const OIS::KeyEvent &arg) {
    for (GameObject *o : objects) {
        o->keyPressed(arg);
    } // for
} // keyPressed

void ObjectManager::mouseMoved(const OIS::MouseEvent &evt) {
}

void ObjectManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
}

void ObjectManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
}
