#ifndef _ENTITY_OBJECT_H_
#define _ENTITY_OBJECT_H_

/**
 * Included files
 */
#include "src/gameobjects/GameObject.h"

class Entity;
static int entityCount = 0;

/**
 * Data
 */
class EntityObject : public GameObject {
protected:
    float range;
    Ogre::Real mDistance;
    Ogre::Vector3 mDirection;
    Ogre::Real mWalkSpeed;
    Ogre::Vector3 mDestination;
    Ogre::AnimationState *mAnimationState;
    virtual void move(const Ogre::FrameEvent &evt) = 0;

public:
    Entity *monster;
    EntityObject(float x, float z);
    EntityObject(Ogre::Vector3 pos);
    ~EntityObject();
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) = 0;
    virtual void update(const Ogre::FrameEvent &evt) = 0;

    void keyPressed(const OIS::KeyEvent &arg) {}
    void mouseMoved(const OIS::MouseEvent &evt) {}
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
};

#endif
