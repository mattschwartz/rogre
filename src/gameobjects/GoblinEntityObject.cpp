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

GoblinEntityObject::GoblinEntityObject(GoblinEntity *goblin, float x, float z) :
    EntityObject(x, z) {
    monster = goblin;
} // constructor

GoblinEntityObject::GoblinEntityObject(GoblinEntity *goblin, Ogre::Vector3 pos) :
    EntityObject(pos) {
    monster = goblin;
} // constructor

void GoblinEntityObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;
    this->sceneManager = &sceneMgr;
	objectNode = sceneMgr.getRootSceneNode()->createChildSceneNode(concat<int>("GoblinEntity", id));
	objectEntity = sceneMgr.createEntity(concat<int>("GoblinEntityEntity", id), "Goblin.mesh");
    objectEntity->setQueryFlags(MONSTER_ENTITIES);
	objectEntity->setCastShadows(true);
    
	objectNode->scale(0.75f, 0.75f, 0.75f);
	objectNode->attachObject(objectEntity);
	objectNode->setPosition(position);

    mDirection = Ogre::Vector3::ZERO;
    mWalkSpeed = 3.0f;

    lastHit = 0.0f;
    mAttackSpeed = 1.5f;
} // createObject

void GoblinEntityObject::show() {
} // show

void GoblinEntityObject::hide() {
} // hide

void GoblinEntityObject::update(const Ogre::FrameEvent &evt) {
    if (monster->isDead()) {
        position.y += 100.0f;
        objectNode->setPosition(position);
        objectNode->setVisible(false);
        remove = true;
        return;
    } // if

    move(evt);
} // update

void GoblinEntityObject::move(const Ogre::FrameEvent &evt) {
    Ogre::SceneNode *playerNode = World::getInstance().getPlayerObject()->objectNode;

    // Can we even see the player?
    if (true || ObjectManager::getInstance().canSee(objectNode, playerNode)) {
        mDestination = World::getInstance().getPlayerPosition();
    } // if
    else {
        mDestination.x = (position.x + rand() % 10) - 5;
        mDestination.z = (position.z + rand() % 10) - 5;
    } // else

    // is the entity already in range of the player to attack?
    if (rangeCheck()) {
        attack(evt);
        return;
    } // if

    // move the entity toward the player
    mDirection = mDestination - objectNode->getPosition();
    mDistance = mDirection.normalise();
    Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
    mDistance -= move;
    rotateEntity();

    if (mDirection != Ogre::Vector3::ZERO) {
        if (mDistance <= 0.0f) {
            objectNode->setPosition(mDestination);

            if (rangeCheck()) {
            } // if
        } // if
        else {
		    Ogre::Vector3 oldPos = objectNode->getPosition();
            objectNode->translate(mDirection * move);
		    if (!World::getInstance().getCurrentZone()->canMove(objectNode->getPosition())) {
                mDirection = Ogre::Vector3::ZERO;
			    mDistance = 0;
			    objectNode->setPosition(oldPos);
		    } // if
        } // else
    } // if
    
    //mAnimationState->addTime(evt.timeSinceLastFrame);
} // move

void GoblinEntityObject::rotateEntity() {
    Ogre::Vector3 src = objectNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
    src.y = 0;
    mDirection.y = 0;
    src.normalise();
    Ogre::Real mDistance = mDirection.normalise();
    Ogre::Quaternion quat = src.getRotationTo(mDirection);

    objectNode->rotate(quat);
    objectNode->yaw(Ogre::Degree(-90));
} // rotateEntity

bool GoblinEntityObject::rangeCheck() {
    Ogre::Vector3 playerPosition = World::getInstance().getPlayerPosition();
    Ogre::Vector3 position = objectNode->getPosition();
    Ogre::Vector3 distance = playerPosition - position;

    distance.x = MathHelper::abs<float>(distance.x);
    distance.y = MathHelper::abs<float>(distance.y);
    distance.z = MathHelper::abs<float>(distance.z);

    if (distance.x <= range && distance.z <= range) {
        return true;
    } // if

    return false;
} // rangeCheck

void GoblinEntityObject::attack(const Ogre::FrameEvent &evt) {
    double damage;
    Player *player;
    lastHit += evt.timeSinceLastEvent;

    if (lastHit >= mAttackSpeed) {
        lastHit = 0.0f;
        // attack
        player = World::getInstance().getCurrentPlayer();
        damage = monster->calculateHit();
        player->takeDamage(damage, monster);
    } // if
} // attack
