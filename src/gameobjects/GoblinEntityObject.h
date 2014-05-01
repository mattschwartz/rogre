#ifndef _GOBLIN_ENTITY_OBJECT_H_
#define _GOBLIN_ENTITY_OBJECT_H_

/**
 * Included files
 */
#include "EntityObject.h"

class GoblinEntity;

class GoblinEntityObject : public EntityObject {
private:
    Ogre::Real snarlRate;
    Ogre::Real lastSnarl;
    GoblinEntity *entity;

public:
    GoblinEntityObject(GoblinEntity *entity, float x, float z);
    GoblinEntityObject(GoblinEntity *entity, Ogre::Vector3 pos);
    ~GoblinEntityObject();
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    void move(const Ogre::FrameEvent &evt);
    bool rangeCheck();
    void rotateEntity();
};

#endif

