/**
 * Included files
 */
#include "src/world/World.h"
#include "src/world/Zone.h"
#include "PlayerObject.h"
#include "src/entities/player/Player.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "src/utility/StringHelper.h"

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
    mWalkSpeed = 8.0f;
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
			Ogre::Vector3 oldPos = playerNode->getPosition();
            playerNode->translate(mDirection * move);
			if (!World::getInstance().getCurrentZone()->containsPoint(playerNode->getPosition())) {
				mDirection = Ogre::Vector3::ZERO;
                mAnimationState = playerEntity->getAnimationState("Idle2");
                mAnimationState->setLoop(true);
                mAnimationState->setEnabled(true);
				mDistance = 0;
				walkList.clear();
				playerNode->setPosition(oldPos);
			} // if
            SoundManager::getInstance().PLAYER_FOOTSTEP_SOUND->play();
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
} // keyPressed

void PlayerObject::mouseMoved(const OIS::MouseEvent &evt) {
	if (false && evt.state.buttonDown(OIS::MB_Left)) {
		//find the current mouse position
		int x = evt.state.X.abs;
		int y = evt.state.Y.abs;
 
		//then send a raycast straight out from the camera at the mouse's position
		Ogre::Ray mouseRay = camera->getCameraToViewportRay(x/float(evt.state.width), y/float(evt.state.height));

		Ogre::Vector3 point = World::getInstance().getCurrentZone()->getIntersectingPlane(mouseRay);

		point.y = playerNode->getPosition().y;
	
		mDirection = Ogre::Vector3::ZERO;
		mDistance = 0;
		walkList.clear();
		walkList.push_back(point);
	} // if
} // mouseMoved

void PlayerObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	//find the current mouse position
	int x = evt.state.X.abs;
	int y = evt.state.Y.abs;
 
	//then send a raycast straight out from the camera at the mouse's position
	Ogre::Ray mouseRay = camera->getCameraToViewportRay(x/float(evt.state.width), y/float(evt.state.height));

	Ogre::Vector3 point = World::getInstance().getCurrentZone()->getIntersectingPlane(mouseRay);

	point.y = playerNode->getPosition().y;
	
	mDirection = Ogre::Vector3::ZERO;
	mDistance = 0;
	walkList.clear();
	walkList.push_back(point);
} // mousePresesd

void PlayerObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
