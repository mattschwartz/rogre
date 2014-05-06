#ifndef _LOOT_OBJECT_H_
#define _LOOT_OBJECT_H_

/**
 * Included files
 */
#include "src/gameobjects/GameObject.h"

class Item;
static int lootCount = 0;

/**
 * Data
 */
class LootObject : public GameObject {
private:
    bool bounceUp;
    bool visible;
    Item *item;
    void bounce();

public:
    LootObject(Item *item, float x, float z);
    LootObject(Item *item, Ogre::Vector3 pos);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void show();
    void hide();
    void update(const Ogre::FrameEvent &evt);

    void keyPressed(const OIS::KeyEvent &arg) {}
    void mouseMoved(const OIS::MouseEvent &evt) {}
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
};

#endif
