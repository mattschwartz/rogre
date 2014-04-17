#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

/**
 * Included files
 */
#include <Ogre.h>
#include <OISMouse.h>
#include <vector>

/**
 * Forward declarations
 */
class GameObject;

class ObjectManager {
private:
    std::vector<GameObject*> objects;
    Ogre::SceneManager *sceneManager;
    Ogre::Camera *camera;
    ObjectManager() {}
    ObjectManager(ObjectManager const&);
    void operator=(ObjectManager const&);

public:
    static ObjectManager &getInstance() {
        static ObjectManager instance;
        return instance;
    } // getInstance

    void init(Ogre::SceneManager *sceneMgr, Ogre::Camera *camera);
    void spawnObject(GameObject *object);

    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
};

#endif