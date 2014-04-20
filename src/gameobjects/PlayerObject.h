#ifndef _PLAYER_OBJECT_H_
#define _PLAYER_OBJECT_H_

/**
 * Included files
 */
#include "src/gameobjects/GameObject.h"

class Player;

/**
 * Data
 */
class PlayerObject : public GameObject {
private:
    Player *player;
	Ogre::RaySceneQuery* rayScnQuery;
    Ogre::Vector3 mDirection;
    Ogre::Real mWalkSpeed;
    Ogre::Vector3 mDestination;
    Ogre::Real mDistance;
    std::deque<Ogre::Vector3> walkList;
    Ogre::SceneNode *playerNode;
    Ogre::Entity *playerEntity;
    Ogre::AnimationState *mAnimationState;
    Ogre::Camera *camera;
    void init();
    void move(const Ogre::FrameEvent &evt);
    void rotatePlayer();

public:
    PlayerObject(Player *player, float x, float y, float z);
    PlayerObject(Player *player, Ogre::Vector3 pos);
    bool nextLocation();

    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
};

#endif
