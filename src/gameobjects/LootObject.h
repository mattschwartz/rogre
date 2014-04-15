#ifndef _LOOT_OBJECT_H_
#define _LOOT_OBJECT_H_

/**
 * Included files
 */
#include "src/gameobjects/GameObject.h"

class Item;

/**
 * Data
 */
class LootObject : public GameObject {
private:
    Item *item;

public:
    LootObject(Item *item, Ogre::Vector3 pos);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
};

#endif
