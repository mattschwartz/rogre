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
    Entity *entity;
	Ogre::Entity *entityEntity;
	Ogre::SceneNode *entityNode;
    Ogre::AnimationState *mAnimationState;

public:
    EntityObject(Entity *entity, float x, float z);
    EntityObject(Entity *entity, Ogre::Vector3 pos);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
};

#endif
