/**
 * Included files
 */
#include "EntityObject.h"
#include "src/world/World.h"
#include "src/world/Zone.h"
#include "src/utility/StringHelper.h"
#include "src/utility/MathHelper.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"

EntityObject::EntityObject(Entity *entity, float x, float z) : GameObject(Ogre::Vector3(x, 0, z)) {
	this->id = entityCount++;
    this->entity = entity;
    this->range = 1.0f;
} // constructor

EntityObject::EntityObject(Entity *entity, Ogre::Vector3 pos) : GameObject(pos) {
	this->id = entityCount++;
    this->entity = entity;
    this->range = 1.0f;
} // constructor

void EntityObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
	entityNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("Entity", id));
	entityEntity = sceneMgr.createEntity(concat<int>("EntityEntity", id), "ogrehead.mesh");
	entityEntity->setCastShadows(true);

    position.y = (float)((rand() % 40) / 10.0f);

	entityNode->scale(0.09f, 0.09f, 0.09f);
	entityNode->attachObject(entityEntity);
	entityNode->setPosition(position);

    mDirection = Ogre::Vector3::ZERO;
    mWalkSpeed = 3.0f;
    lastSnarl = 0;
    snarlRate = (rand() % 16) + 4;
    bounceUp = true;

    //mAnimationState = entityEntity->getAnimationState("Idle2");
    //mAnimationState->setLoop(true);
    //mAnimationState->setEnabled(true);
} // createObject

void EntityObject::update(const Ogre::FrameEvent &evt) {
    int ran;
    move(evt);

    lastSnarl += evt.timeSinceLastFrame;
    
    if (lastSnarl >= snarlRate) {
        lastSnarl = 0;
        ran = rand() % 4;

        switch (ran) {
        case 0:
            SoundManager::getInstance().MONSTER_BREATHING_1_SOUND->play();
            break;

        case 1:
            SoundManager::getInstance().MONSTER_BREATHING_2_SOUND->play();
            break;

        case 2:
            SoundManager::getInstance().MONSTER_BREATHING_3_SOUND->play();
            break;

        default:
            SoundManager::getInstance().MONSTER_BREATHING_4_SOUND->play();

        } // switch-case
    } // if

    //SoundManager::getInstance().PLAYER_FOOTSTEP_SOUND->play();
} // update

void EntityObject::move(const Ogre::FrameEvent &evt) {
    floater();

    // is the entity already in range of the player to attack?
    if (rangeCheck()) {
        return;
    } // if

    // can the entity see the player?
    // yes?
    mDestination = World::getInstance().getPlayerPosition();

    // no?
    // mDestination = this->randomPosition();

    // move the entity toward the player

    mDirection = mDestination - entityNode->getPosition();
    mDistance = mDirection.normalise();
    Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
    mDistance -= move;
    rotateEntity();

    if (mDirection == Ogre::Vector3::ZERO) {
    }
    else {
        if (mDistance <= 0.0f) {
            entityNode->setPosition(mDestination);

            if (rangeCheck()) {
                // set idle animation
            } // if
            else {

            } // else
        } // if
        else {
		    Ogre::Vector3 oldPos = entityNode->getPosition();
            entityNode->translate(mDirection * move);
		    if (!World::getInstance().getCurrentZone()->containsPoint(entityNode->getPosition())) {
                mDirection = Ogre::Vector3::ZERO;
                //mAnimationState = playerEntity->getAnimationState("Idle2");
                //mAnimationState->setLoop(true);
                //mAnimationState->setEnabled(true);
			    mDistance = 0;
			    entityNode->setPosition(oldPos);
		    } // if
        } // else
    } // else
    
    //mAnimationState->addTime(evt.timeSinceLastFrame);
} // move

void EntityObject::rotateEntity() {
    Ogre::Vector3 src = entityNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
    src.y = 0;
    mDirection.y = 0;
    src.normalise();
    Ogre::Real mDistance = mDirection.normalise();
    Ogre::Quaternion quat = src.getRotationTo(mDirection);

    entityNode->rotate(quat);
    entityNode->yaw(Ogre::Degree(-90));
} // rotateEntity

void EntityObject::floater() {
    Ogre::Vector3 pos = entityNode->getPosition();

    if (bounceUp) {
        pos.y += 0.02;
    } else {
        pos.y -= 0.02;
    }

    if (pos.y <= 0) {
        pos.y = 0;
        bounceUp = true;
    } else if (pos.y >= 4) {
        pos.y = 4;
        bounceUp = false;
    }

    entityNode->setPosition(pos);
} // floater

bool EntityObject::nextLocation() {
    if (rangeCheck()) {
        return false;
    } // if

    mDestination = World::getInstance().getPlayerPosition();
    mDirection = mDestination - entityNode->getPosition();
    mDistance = mDirection.normalise();

    return true;
} // nextLocation

bool EntityObject::rangeCheck() {
    Ogre::Vector3 playerPosition = World::getInstance().getPlayerPosition();
    Ogre::Vector3 position = entityNode->getPosition();
    Ogre::Vector3 distance = playerPosition - position;

    distance.x = MathHelper::abs<float>(distance.x);
    distance.y = MathHelper::abs<float>(distance.y);
    distance.z = MathHelper::abs<float>(distance.z);

    if (distance.x <= range && distance.z <= range) {
        return true;
    } // if

    return false;
} // rangeCheck

bool EntityObject::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void EntityObject::keyPressed(const OIS::KeyEvent &arg) {
}

void EntityObject::mouseMoved(const OIS::MouseEvent &evt) {
} // mouseMoved

void EntityObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mousePresesd

void EntityObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
