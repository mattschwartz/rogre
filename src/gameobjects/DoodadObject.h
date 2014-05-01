#ifndef _DOODAD_OBJECT_H_
#define _DOODAD_OBJECT_H_

/**
 * Included files
 */
#include "src/gameobjects/GameObject.h"

class Doodad;
static int doodadCount = 0;

/**
 * Data
 */
class DoodadObject : public GameObject {
protected:
	Ogre::Entity *doodadEntity;
	Ogre::SceneNode *doodadNode;

public:
    DoodadObject(float x, float y, float z) : GameObject(Ogre::Vector3(x, y, z)) {}
    DoodadObject(float x, float z) : GameObject(Ogre::Vector3(x, 0, z)) {}
    DoodadObject(Ogre::Vector3 pos) : GameObject(pos) {}
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) = 0;
    virtual void update(const Ogre::FrameEvent &evt) = 0;

    bool contains(const OIS::MouseEvent &evt) { return false; }
    void keyPressed(const OIS::KeyEvent &arg) {}
    void mouseMoved(const OIS::MouseEvent &evt) {}
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
};

#endif
