#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

/**
 * Included files
 */
#include <Ogre.h>
#include <OISMouse.h>
#include <OISKeyboard.h>

/**
 * Defines
 */
struct Dimension {
    float width;
    float depth;
    float height;
};

struct Bounds {
	float xStart;
	float yStart;
	float zStart;
	float xEnd;
	float yEnd;
	float zEnd;
};

/**
 * Data
 */
class GameObject {
protected:
    bool remove;
    int id;
    Ogre::Vector3 position;

public:
    Ogre::SceneNode *objectNode;
    Ogre::Entity *objectEntity;

    GameObject() {
        this->position = Ogre::Vector3(0, 0, 0);
        remove = false;
    } // constructor
    GameObject(Ogre::Vector3 position) {
        this->position = position;
        remove = false;
    } // constructor

    bool contains(Ogre::Vector3 vec) {
        return objectEntity->getWorldBoundingBox().contains(vec);
    } // contains

    bool shouldRemove() {
        return remove;
    } // shouldRemove
    
    virtual void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) = 0;
    virtual void update(const Ogre::FrameEvent &evt) = 0;
    virtual void keyPressed(const OIS::KeyEvent &arg) = 0;
    virtual void mouseMoved(const OIS::MouseEvent &evt) = 0;
    virtual void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
    virtual void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
};

#endif
