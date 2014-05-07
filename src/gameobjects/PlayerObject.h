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
    bool dying;
    bool attacking;
    bool dead;
    Player *player;
    Ogre::Vector3 walkTo;
    Ogre::Vector3 mDirection;
    Ogre::Real mWalkSpeed;
    Ogre::Real lastHealthTick;
    Ogre::AnimationState *mAnimationState;
    Ogre::Camera *camera;
    void init();
    void move(const Ogre::FrameEvent &evt);
    void attack(const Ogre::FrameEvent &evt);
    void rotatePlayer();
    void setIdleAnimation();
    void setWalkAnimation();
    void setDeathAnimation();
    bool withinWorld();

public:
    PlayerObject(Player *player, float x, float y, float z);
    PlayerObject(Player *player, Ogre::Vector3 pos);
    ~PlayerObject();
    Ogre::Vector3 getPosition();

    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg) {}
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
};

#endif
