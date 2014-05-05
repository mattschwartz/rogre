/** 
 * Included files
 */
#include "src/utility/MathHelper.h"
#include "src/utility/StringHelper.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "src/world/World.h"

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

void ObjectManager::destroyScene() {
    sceneManager->clearScene();

    for (GameObject *o : objects) {
        o->~GameObject();
    } // for

    objects.clear();
} // destroyScene

Ogre::Camera *ObjectManager::getCamera() {
    return camera;
} // getCamera

Ogre::SceneManager *ObjectManager::getSceneManager() {
    return sceneManager;
} // getSceneManager

void ObjectManager::destroySceneNode(std::string name) {
    sceneManager->getSceneNode(name)->removeAndDestroyAllChildren();
} // destroySceneNode

void ObjectManager::destroySceneNode(std::string name, int id) {
    sceneManager->getSceneNode(StringHelper::concat<int>(name, id))->removeAndDestroyAllChildren();
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
    if (World::getInstance().isGamePaused()) {
        return;
    } // if

    for (GameObject *o : objects) {
        o->update(evt);
    } // for
} // update

bool ObjectManager::canSee(Ogre::SceneNode *a, Ogre::SceneNode *b) {
    Ogre::Vector3 positionA = a->getPosition();
    Ogre::Vector3 positionB = b->getPosition();
    Ogre::RaySceneQuery *mRayScnQuery;
    Ogre::Ray robotRay(positionA, positionB);

    mRayScnQuery = sceneManager->createRayQuery(robotRay);

    Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
    Ogre::RaySceneQueryResult::iterator iter = result.begin();

    if (iter != result.end()) {
      	bool temp = iter->movable->getName() == Ogre::String(b->getName());
        mRayScnQuery->clearResults();

        return temp;
    }
    mRayScnQuery->clearResults();
    return false;
} // canSee

/**
 * May not be necessary - used for determining if the mouse is hovering
 * over an object
 * 
 * @param evt
 * @return
 */
bool ObjectManager::contains(const OIS::MouseEvent &evt) {
    if (World::getInstance().isGamePaused()) {
        return false;
    } // if

    return false;
} // contains

void ObjectManager::keyPressed(const OIS::KeyEvent &arg) {
    if (World::getInstance().isGamePaused()) {
        return;
    } // if

    for (GameObject *o : objects) {
        o->keyPressed(arg);
    } // for
} // keyPressed

void ObjectManager::mouseMoved(const OIS::MouseEvent &evt) {
    if (World::getInstance().isGamePaused()) {
        return;
    } // if

	if (evt.state.Z.rel > 0) {
		Ogre::Vector3 oldpos = camera->getPosition();
		oldpos.y = MathHelper::max<Ogre::Real>(15, oldpos.y - 5);
		oldpos.z = MathHelper::max<Ogre::Real>(15, oldpos.z - 5);
		camera->setPosition(oldpos);
	} // if
	else if (evt.state.Z.rel < 0) {
		Ogre::Vector3 oldpos = camera->getPosition();
		oldpos.y = MathHelper::min<Ogre::Real>(45, oldpos.y + 5);
		oldpos.z = MathHelper::min<Ogre::Real>(45, oldpos.z + 5);
		camera->setPosition(oldpos);
	} // else if

	for (GameObject *o : objects) {
		o->mouseMoved(evt);
	} // for
} // mouseMoved

void ObjectManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (World::getInstance().isGamePaused()) {
        return;
    } // if

	for (GameObject *o : objects) {
		o->mousePressed(evt, id);
	} // for
} // mousePressed

void ObjectManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (World::getInstance().isGamePaused()) {
        return;
    } // if

}
