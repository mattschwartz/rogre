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
private:
	int id;
    float range;
    int bounceUp;
    Ogre::Real snarlRate;
    Ogre::Real lastSnarl;
    Entity *entity;
    Ogre::Vector3 mDirection;
    Ogre::Real mWalkSpeed;
    Ogre::Vector3 mDestination;
    Ogre::Real mDistance;
    std::deque<Ogre::Vector3> walkList;
	Ogre::Entity *entityEntity;
	Ogre::SceneNode *entityNode;
    Ogre::AnimationState *mAnimationState;
    void move(const Ogre::FrameEvent &evt);
    bool nextLocation();
    bool rangeCheck();
    void rotateEntity();
    void floater();

public:
    EntityObject(Entity *entity, float x, float z);
    EntityObject(Entity *entity, Ogre::Vector3 pos);
    ~EntityObject();
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
};

#endif
