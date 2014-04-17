/**
 * Included files
 */
#include "PlayerObject.h"
#include "src/entities/player/Player.h"

PlayerObject::PlayerObject(Player *player, float x, float y, float z) : GameObject(Ogre::Vector3(x, y, z)) {
    this->player = player;
} // constructor

PlayerObject::PlayerObject(Player *player, Ogre::Vector3 pos) : GameObject(pos) {
    this->player = player;
} // constructor

void PlayerObject::init() {
} // init

void PlayerObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
    playerNode = sceneMgr.getRootSceneNode()->createChildSceneNode("PlayerNode");
    playerEntity = sceneMgr.createEntity("Player", "ninja.mesh");
    playerEntity->setCastShadows(true);

    playerNode->scale(0.025f, 0.025f, 0.025f);
    playerNode->attachObject(playerEntity);
    playerNode->setPosition(position);

    mDirection = Ogre::Vector3::ZERO;
    mWalkSpeed = 5.0f;
    mAnimationState = playerEntity->getAnimationState("Idle2");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
    this->camera = camera;
} // createObject

void PlayerObject::update(const Ogre::FrameEvent &evt) {
    move(evt);
} // update

void PlayerObject::move(const Ogre::FrameEvent &evt) {
    Ogre::Vector3 initialPosition = playerNode->getPosition();

    if (mDirection == Ogre::Vector3::ZERO) {
        if (nextLocation()) {
            mAnimationState = playerEntity->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);

            rotatePlayer();
        } // if
    } // if
    else {
        Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
        mDistance -= move;

        if (mDistance <= 0.0f) {
            playerNode->setPosition(mDestination);
            mDirection = Ogre::Vector3::ZERO;

            if (!nextLocation()) {
                mAnimationState = playerEntity->getAnimationState("Idle2");
                mAnimationState->setLoop(true);
                mAnimationState->setEnabled(true);
            } // if
            else {
                Ogre::Vector3 src = playerNode->getOrientation() * Ogre::Vector3::UNIT_X;

                if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
                    playerNode->yaw(Ogre::Degree(180));
                } // if
                else {
                    Ogre::Quaternion quat = src.getRotationTo(mDirection);
                    playerNode->rotate(quat);
                } // else
            } // else
        } // if
        else {
            playerNode->translate(mDirection * move);
            Ogre::Vector3 campos = camera->getPosition();
            campos.x = playerNode->getPosition().x;
            campos.z += playerNode->getPosition().z - initialPosition.z;
            camera->setPosition(campos);
        } // else
    } // else
        
    mAnimationState->addTime(evt.timeSinceLastFrame);
} // move

void PlayerObject::rotatePlayer() {
    /*
    Ogre::Vector3 src = playerNode->getOrientation() * Ogre::Vector3::UNIT_X;
    src.y = 0;
    mDirection.y = 0;
    src.normalise();
    Ogre::Real mDistance = mDirection.normalise();
    Ogre::Quaternion quat = src.getRotationTo(mDirection);

    playerNode->rotate(quat);
    */
} // rotate

bool PlayerObject::nextLocation() {
    if (walkList.empty()) {
        return false;
    } // if

    mDestination = walkList.front();
    walkList.pop_front();
    mDirection = mDestination - playerNode->getPosition();
    mDistance = mDirection.normalise();

    return true;
} // nextLocation

bool PlayerObject::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void PlayerObject::keyPressed(const OIS::KeyEvent &arg) {
    float moveAmount = 5;
    Ogre::Vector3 walkToLocation = playerNode->getPosition();

    switch (arg.key) {
        case OIS::KC_W:
            walkToLocation.z -= moveAmount;
            break;
        case OIS::KC_A:
            walkToLocation.x -= moveAmount;
            break;
        case OIS::KC_S:
            walkToLocation.z += moveAmount;
            break;
        case OIS::KC_D:
            walkToLocation.x += moveAmount;
            break;
    } // switch-case
    
    mDirection = Ogre::Vector3::ZERO;
    mDistance = 0;
    walkList.clear();
    walkList.push_back(walkToLocation);
} // keyPressed

void PlayerObject::mouseMoved(const OIS::MouseEvent &evt) {
} // mouseMoved

void PlayerObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mousePresesd

void PlayerObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
