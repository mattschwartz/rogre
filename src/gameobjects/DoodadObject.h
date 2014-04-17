#ifndef _DOODAD_OBJECT_H_
#define _DOODAD_OBJECT_H_

/**
 * Included files
 */
#include "src/gameobjects/GameObject.h"

class Doodad;

/**
 * Data
 */
class DoodadObject : public GameObject {
private:
    Doodad *doodad;

public:
    DoodadObject(Doodad *doodad, Ogre::Vector3 pos);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
};

#endif
