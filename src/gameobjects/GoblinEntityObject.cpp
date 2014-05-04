/**
 * Included files
 */
#include "PlayerObject.h"
#include "GoblinEntityObject.h"
#include "src/entities/player/Player.h"
#include "src/gameobjects/ObjectManager.h"
#include "src/utility/StringHelper.h"
#include "src/utility/MathHelper.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "src/entities/monsters/GoblinEntity.h"
#include "src/world/World.h"
#include "src/world/Zone.h"

GoblinEntityObject::GoblinEntityObject(GoblinEntity *entity, float x, float z) :
    EntityObject(x, z) {
} // constructor

GoblinEntityObject::GoblinEntityObject(GoblinEntity *entity, Ogre::Vector3 pos) :
    EntityObject(pos) {
} // constructor

void GoblinEntityObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
    this->sceneManager = &sceneMgr;
	entityNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("GoblinEntity", id));
	entityEntity = sceneMgr.createEntity(concat<int>("GoblinEntityEntity", id), "Goblin.mesh");
	entityEntity->setCastShadows(true);
    
	entityNode->scale(0.75f, 0.75f, 0.75f);
	entityNode->attachObject(entityEntity);
	entityNode->setPosition(position);

    mDirection = Ogre::Vector3::ZERO;
    mWalkSpeed = 3.0f;
} // createObject

void GoblinEntityObject::show() {
} // show

void GoblinEntityObject::hide() {
} // hide

void GoblinEntityObject::update(const Ogre::FrameEvent &evt) {
    move(evt);
} // update

void GoblinEntityObject::move(const Ogre::FrameEvent &evt) {
    Ogre::SceneNode *playerNode = World::getInstance().getCurrentPlayer()->playerNode;

    // Can we even see the player?
    if (ObjectManager::getInstance().canSee(entityNode, playerNode)) {
        mDestination = World::getInstance().getPlayerPosition();
    } // if
    else {
        mDestination.x = (position.x + rand() % 10) - 5;
        mDestination.z = (position.z + rand() % 10) - 5;
    } // else

    // is the entity already in range of the player to attack?
    if (rangeCheck()) {
        return;
    } // if

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
		    if (!World::getInstance().getCurrentZone()->canMove(entityNode->getPosition())) {
                mDirection = Ogre::Vector3::ZERO;
			    mDistance = 0;
			    entityNode->setPosition(oldPos);
		    } // if
        } // else
    } // else
    
    //mAnimationState->addTime(evt.timeSinceLastFrame);
} // move

void GoblinEntityObject::rotateEntity() {
    Ogre::Vector3 src = entityNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
    src.y = 0;
    mDirection.y = 0;
    src.normalise();
    Ogre::Real mDistance = mDirection.normalise();
    Ogre::Quaternion quat = src.getRotationTo(mDirection);

    entityNode->rotate(quat);
    entityNode->yaw(Ogre::Degree(-90));
} // rotateEntity

bool GoblinEntityObject::rangeCheck() {
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
