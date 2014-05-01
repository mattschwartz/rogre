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
#include "src/gameobjects/ObjectManager.h"

PlayerObject::PlayerObject(Player *player, float x, float y, float z) : GameObject(Ogre::Vector3(x, y, z)) {
    this->player = player;
    init();
} // constructor

PlayerObject::PlayerObject(Player *player, Ogre::Vector3 pos) : GameObject(pos) {
    this->player = player;
    init();
} // constructor

PlayerObject::~PlayerObject() {
    ObjectManager::getInstance().destroySceneNode("PlayerNode");
} // destructor

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
    mWalkSpeed = 6.0f;
    mAnimationState = playerEntity->getAnimationState("Idle2");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
    this->camera = camera;

    attacking = false;
    walkTo = position;
    dead = false;
} // createObject

void PlayerObject::update(const Ogre::FrameEvent &evt) {
    if (player->isDead()) {
        setDeathAnimation();

        if (mAnimationState->hasEnded()) {
            player->onDeath();
        } // if
    } // if
    else {
        move(evt);
        attack(evt);
        Ogre::Vector3 campos = camera->getPosition();
        campos.x = playerNode->getPosition().x;
        campos.z = playerNode->getPosition().z + campos.y;
        camera->setPosition(campos);
    } // else
        
    mAnimationState->addTime(evt.timeSinceLastFrame);
} // update

void PlayerObject::move(const Ogre::FrameEvent &evt) {
    Ogre::Vector3 initialPosition = playerNode->getPosition();
    Ogre::Vector3 destination = walkTo;
    Ogre::Real distance;
    Ogre::Real move;

    if (initialPosition != destination) {
        mDirection = destination - initialPosition;
        distance = mDirection.normalise();
        move = mWalkSpeed * evt.timeSinceLastFrame;
        distance -= move;
        rotatePlayer();

        if (distance <= 0.0f) {
            playerNode->setPosition(destination);
            setIdleAnimation();
        } // if
        else {
            playerNode->translate(mDirection * move);
            if (!withinWorld()) {
                playerNode->setPosition(initialPosition);
                walkTo = initialPosition;
                setIdleAnimation();
            } // if
            else {
                setWalkAnimation();
                SoundManager::getInstance().PLAYER_FOOTSTEP_SOUND->play();
            } // else
        } // else
    } // if
} // move

void PlayerObject::setIdleAnimation() {
    int ran = rand() % 3;
    
    switch (ran) {
        case 0:
            mAnimationState = playerEntity->getAnimationState("Idle1");
            break;

        case 1:
            mAnimationState = playerEntity->getAnimationState("Idle2");
            break;

        case 2:
            mAnimationState = playerEntity->getAnimationState("Idle3");
    } // switch-case

    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
} // setIdleAnimation

void PlayerObject::setWalkAnimation() {
    mAnimationState = playerEntity->getAnimationState("Walk");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
} // setWalkAnimation

void PlayerObject::setDeathAnimation() {
    int ran = rand() % 2;
    
    switch (ran) {
        case 0:
            mAnimationState = playerEntity->getAnimationState("Death1");
            break;

        case 1:
            mAnimationState = playerEntity->getAnimationState("Death2");
    } // switch-case

    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
} // setDeathAnimation

bool PlayerObject::withinWorld() {
    return World::getInstance().getCurrentZone()->containsPoint(playerNode->getPosition());
} // withinWorld

void PlayerObject::attack(const Ogre::FrameEvent &evt) {
    if (attacking && mAnimationState->hasEnded()) {
        setIdleAnimation();
        attacking = false;
    } // if
} // attack

void PlayerObject::rotatePlayer() {
    Ogre::Vector3 src = playerNode->getOrientation() * Ogre::Vector3::UNIT_X;
    src.y = 0;
    mDirection.y = 0;
    src.normalise();
    Ogre::Real mDistance = mDirection.normalise();
    Ogre::Quaternion quat = src.getRotationTo(mDirection);

    playerNode->rotate(quat);
    playerNode->yaw(Ogre::Degree(-90));
} // rotatePlayer

Ogre::Vector3 PlayerObject::getPosition() {
    return playerNode->getPosition();
} // getPosition

void PlayerObject::mouseMoved(const OIS::MouseEvent &evt) {
    if (dead || attacking) {
        return;
    } // if

	if (evt.state.buttonDown(OIS::MB_Left)) {
		//find the current mouse position
	    int x = evt.state.X.abs;
	    int y = evt.state.Y.abs;
 
	    Ogre::Ray mouseRay = camera->getCameraToViewportRay(x/float(evt.state.width), y/float(evt.state.height));
	    Ogre::Vector3 point = World::getInstance().getCurrentZone()->getIntersectingPlane(mouseRay);

	    point.y = playerNode->getPosition().y;
        walkTo = point;
	} // if
} // mouseMoved

void PlayerObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (dead || attacking) {
        return;
    } // if

    if (id == OIS::MB_Left) {
	    int x = evt.state.X.abs;
	    int y = evt.state.Y.abs;
 
	    Ogre::Ray mouseRay = camera->getCameraToViewportRay(x/float(evt.state.width), y/float(evt.state.height));
	    Ogre::Vector3 point = World::getInstance().getCurrentZone()->getIntersectingPlane(mouseRay);

	    point.y = playerNode->getPosition().y;
        walkTo = point;
    } // if
    else if (id == OIS::MB_Right) {
        int ran = rand() % 3;
        attacking = true;
        walkTo = playerNode->getPosition();
        
        switch (ran) {
            case 0:
                mAnimationState = playerEntity->getAnimationState("Attack1");
                break;

            case 1:
                mAnimationState = playerEntity->getAnimationState("Attack2");
                break;

            default:
                mAnimationState = playerEntity->getAnimationState("Attack3");
        } // switch-case
        
        mAnimationState->setTimePosition(0);
        mAnimationState->setLoop(false);
        mAnimationState->setEnabled(true);
        SoundManager::getInstance().ATTACK_MISS_1_SOUND->play();
    } // else if
} // mousePresesd
