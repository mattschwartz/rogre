#ifndef _GOBLIN_ENTITY_OBJECT_H_
#define _GOBLIN_ENTITY_OBJECT_H_

/**
 * Included files
 */
#include "EntityObject.h"

class GoblinEntity;

class GoblinEntityObject : public EntityObject {
private:
    Ogre::RaySceneQuery *raySceneQuery;
    Ogre::SceneManager *sceneManager;

public:
    GoblinEntityObject(GoblinEntity *goblin, float x, float z);
    GoblinEntityObject(GoblinEntity *goblin, Ogre::Vector3 pos);
    ~GoblinEntityObject();
    void show();
    void hide();
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    void move(const Ogre::FrameEvent &evt);
    void attack(const Ogre::FrameEvent &evt);
    bool rangeCheck();
    void rotateEntity();
};

#endif

