#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

/**
 * Included files
 */
#include <Ogre.h>
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <vector>
#include <queue>

/**
 * Forward declarations
 */
class GameObject;
class EntityObject;

enum QueryFlags{
    MONSTER_ENTITIES,
    FLOOR_ENTITY
};

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
	void destroySceneNode(std::string name);
	void destroySceneNode(std::string name, int);
    void spawnObject(GameObject *object);
    void destroyScene();
    Ogre::Camera *getCamera();
    Ogre::SceneManager *getSceneManager();

    bool canSee(Ogre::SceneNode *a, Ogre::SceneNode *b);
    bool canReach(GameObject *object1, GameObject *object2, float reach);

    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    
};

#endif
