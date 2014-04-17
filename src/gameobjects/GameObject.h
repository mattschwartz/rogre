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

/**
 * Data
 */
class GameObject {
protected:
    Ogre::Vector3 position;

public:
    GameObject() {
        this->position = Ogre::Vector3(0, 0, 0);
    } // constructor

    GameObject(Ogre::Vector3 position) {
        this->position = position;
    } // constructor
    
    virtual void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) = 0;
    virtual void update(const Ogre::FrameEvent &evt) = 0;
    virtual bool contains(const OIS::MouseEvent &evt) = 0;
    virtual void keyPressed(const OIS::KeyEvent &arg) = 0;
    virtual void mouseMoved(const OIS::MouseEvent &evt) = 0;
    virtual void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
    virtual void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;

};

#endif
