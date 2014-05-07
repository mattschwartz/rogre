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
#include "DoodadObject.h"
#include "EntityObject.h"
#include "GameObject.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/ingamemenu/InGameMenu.h"
#include "src/utility/filesys/FileManager.h"

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
    objectNode = sceneMgr.getRootSceneNode()->createChildSceneNode("PlayerNode");
    objectEntity = sceneMgr.createEntity("Player", "ninja.mesh");
    objectEntity->setCastShadows(true);

    objectNode->scale(0.025f, 0.025f, 0.025f);
    objectNode->attachObject(objectEntity);
    objectNode->setPosition(position);

    mDirection = Ogre::Vector3::ZERO;
    mWalkSpeed = 6.0f;
    mAnimationState = objectEntity->getAnimationState("Idle2");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
    this->camera = camera;

    dying = false;
    dead = false;
    attacking = false;
    updateGraveyard = true;
    walkTo = position;
    lastHealthTick = 0.0f;
} // createObject

void PlayerObject::update(const Ogre::FrameEvent &evt) {
    if (player->isDead()) {
        setDeathAnimation();

        if (mAnimationState->hasEnded()) {
            player->onDeath();
            if (updateGraveyard) {
                FileManager::getInstance().addToGraveyard(player);
                updateGraveyard = false;
            } // if
        } // if
    } // if
    else {
        lastHealthTick += evt.timeSinceLastEvent;

        if (lastHealthTick >= 1.0f) {
            player->regenerateLife();
            lastHealthTick = 0.0;
        } // if

        move(evt);
        attack(evt);
        Ogre::Vector3 campos = camera->getPosition();
        campos.x = objectNode->getPosition().x;
        campos.z = objectNode->getPosition().z + campos.y;
        camera->setPosition(campos);
        player->updateTimePlayed(evt.timeSinceLastEvent);
        GUIManager::getInstance().inGameMenu->updateAttributes(player);
        GUIManager::getInstance().inGameMenu->updatePlayerScore(player);
    } // else
    
    mAnimationState->addTime(evt.timeSinceLastFrame);
} // update

void PlayerObject::move(const Ogre::FrameEvent &evt) {
    Ogre::Vector3 initialPosition = objectNode->getPosition();
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
            objectNode->setPosition(destination);
            setIdleAnimation();
        } // if
        else {
            objectNode->translate(mDirection * move);
            if (!withinWorld()) {
                objectNode->setPosition(initialPosition);
                walkTo = initialPosition;
                setIdleAnimation();
            } // if
            else {
                setWalkAnimation();
                SoundManager::getInstance().PLAYER_FOOTSTEP_SOUND->stop();
                SoundManager::getInstance().PLAYER_FOOTSTEP_SOUND->play();
            } // else
        } // else
    } // if
} // move

void PlayerObject::setIdleAnimation() {
    int ran = rand() % 3;
    
    switch (ran) {
        case 0:
            mAnimationState = objectEntity->getAnimationState("Idle1");
            break;

        case 1:
            mAnimationState = objectEntity->getAnimationState("Idle2");
            break;

        case 2:
            mAnimationState = objectEntity->getAnimationState("Idle3");
    } // switch-case

    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
} // setIdleAnimation

void PlayerObject::setWalkAnimation() {
    mAnimationState = objectEntity->getAnimationState("Walk");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
} // setWalkAnimation

void PlayerObject::setDeathAnimation() {
    int ran = rand() % 2;

    if (dying) {
        return;
    }

    dying = true;
    switch (ran) {
        case 0:
            mAnimationState = objectEntity->getAnimationState("Death1");
            break;

        case 1:
            mAnimationState = objectEntity->getAnimationState("Death2");
    } // switch-case
    
    mAnimationState->setTimePosition(0);
    mAnimationState->setLoop(false);
    mAnimationState->setEnabled(true);
} // setDeathAnimation

bool PlayerObject::withinWorld() {
    return World::getInstance().getCurrentZone()->canMove(objectNode->getPosition());
} // withinWorld

void PlayerObject::attack(const Ogre::FrameEvent &evt) {
    if (attacking && mAnimationState->hasEnded()) {
        setIdleAnimation();
        attacking = false;
        
        double dmg;
        Zone *zone = World::getInstance().getCurrentZone();

        for (EntityObject *o : zone->entities) {
            if (ObjectManager::getInstance().canReach(this, o, 1.0f)) {
                dmg = player->calculateHit();
                o->monster->takeDamage(dmg, player);
            } // if
        } // for

        for (DoodadObject *o : zone->doodads) {
            if (ObjectManager::getInstance().canReach(this, o, 1.0f)) {
                dmg = player->calculateHit();
                o->interact();
            } // if
        } // for
    } // if
} // attack

void PlayerObject::rotatePlayer() {
    Ogre::Vector3 src = objectNode->getOrientation() * Ogre::Vector3::UNIT_X;
    src.y = 0;
    mDirection.y = 0;
    src.normalise();
    Ogre::Real mDistance = mDirection.normalise();
    Ogre::Quaternion quat = src.getRotationTo(mDirection);

    objectNode->rotate(quat);
    objectNode->yaw(Ogre::Degree(-90));
} // rotatePlayer

Ogre::Vector3 PlayerObject::getPosition() {
    return objectNode->getPosition();
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

	    point.y = objectNode->getPosition().y;
        walkTo = point;
	} // if
} // mouseMoved

void PlayerObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (dead || attacking) {
        return;
    } // if
	int x = evt.state.X.abs;
	int y = evt.state.Y.abs;
	Ogre::Ray mouseRay = camera->getCameraToViewportRay(x/float(evt.state.width), y/float(evt.state.height));
	Ogre::Vector3 point = World::getInstance().getCurrentZone()->getIntersectingPlane(mouseRay);
    point.y = objectNode->getPosition().y;

    if (id == OIS::MB_Left) {
        walkTo = point;
    } // if
    else if (id == OIS::MB_Right) {
        int ran = rand() % 3;
        attacking = true;
        walkTo = objectNode->getPosition();
 
        // Rotate player
        Ogre::Vector3 dir = point - walkTo;
        Ogre::Vector3 src = objectNode->getOrientation() * Ogre::Vector3::UNIT_X;
        src.y = 0;
        dir.y = 0;
        src.normalise();
        Ogre::Real mDistance = dir.normalise();
        Ogre::Quaternion quat = src.getRotationTo(dir);

        objectNode->rotate(quat);
        objectNode->yaw(Ogre::Degree(-90));
        
        switch (ran) {
            case 0:
                mAnimationState = objectEntity->getAnimationState("Attack1");
                break;

            case 1:
                mAnimationState = objectEntity->getAnimationState("Attack2");
                break;

            default:
                mAnimationState = objectEntity->getAnimationState("Attack3");
        } // switch-case
        
        mAnimationState->setTimePosition(0);
        mAnimationState->setLoop(false);
        mAnimationState->setEnabled(true);
        SoundManager::getInstance().ATTACK_MISS_1_SOUND->play();
    } // else if
} // mousePresesd
