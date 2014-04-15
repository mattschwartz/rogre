#ifndef _ENTITY_OBJECT_H_
#define _ENTITY_OBJECT_H_

/**
 * Included files
 */
#include "src/gameobjects/GameObject.h"

class Entity;

/**
 * Data
 */
class EntityObject : public GameObject {
private:
    Entity *entity;

public:
    EntityObject(Entity *entity, Ogre::Vector3 pos);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
};

#endif
