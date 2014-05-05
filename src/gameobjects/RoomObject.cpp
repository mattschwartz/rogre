/**
 * Included files
 */
#include "ObjectManager.h"
#include "RoomObject.h"
#include "src/world/Room.h"
#include "src/utility/MathHelper.h"
#include "src/utility/StringHelper.h"
#include "src/world/World.h"

/**
 * Data
 */
static int roomCount = 0;

RoomObject::RoomObject(Room *room, float width, float depth, float height, 
    Ogre::Vector3 pos) : GameObject(pos) {
    this->id = roomCount++;
	this->room = room;
    this->dimensions.width = width;
    this->dimensions.depth = depth;
    this->dimensions.height = height;
    init();
} // constructor

RoomObject::RoomObject(Room *room, struct Dimension d, Ogre::Vector3 pos) : 
    GameObject(pos) {
    this->id = roomCount++;
	this->room = room;
    this->dimensions = d;
    init();
} // constructor

RoomObject::~RoomObject() {
	ObjectManager::getInstance().destroySceneNode("FloorEntity", id);
	ObjectManager::getInstance().destroySceneNode("Wall1Node", id);
	ObjectManager::getInstance().destroySceneNode("Wall2Node", id);
	ObjectManager::getInstance().destroySceneNode("Wall3Node", id);
	ObjectManager::getInstance().destroySceneNode("Wall4Node", id);
} // destructor

/** 
 * Performs the tasks that all constructors have in common
 * in one, convenient function.
 */
void RoomObject::init() {
    visible = false;

    // Initialize planes that make up the room
    floor = new Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);
    walls[0] = new Ogre::Plane(Ogre::Vector3::UNIT_X, 0);
    walls[1] = new Ogre::Plane(-Ogre::Vector3::UNIT_X, 0);
    walls[2] = new Ogre::Plane(Ogre::Vector3::UNIT_Z, 0);
    walls[3] = new Ogre::Plane(-Ogre::Vector3::UNIT_Z, 0);
} // init

void RoomObject::createEntities() {
	using namespace StringHelper;

    createMeshes();

    floorEntity = sceneManager->createEntity(concat<int>("FloorEntity", id), concat<int>("floor", id));
    wall1Entity = sceneManager->createEntity(concat<int>("Wall1Entity", id), concat<int>("wall1", id));
    wall2Entity = sceneManager->createEntity(concat<int>("Wall2Entity", id), concat<int>("wall2", id));
    wall3Entity = sceneManager->createEntity(concat<int>("Wall3Entity", id), concat<int>("wall3", id));
    wall4Entity = sceneManager->createEntity(concat<int>("Wall4Entity", id), concat<int>("wall4", id));

    // Meshes
    floorEntity->setMaterialName("Examples/Floor");
    wall1Entity->setMaterialName("Examples/Wall");
    wall2Entity->setMaterialName("Examples/Wall");
    wall3Entity->setMaterialName("Examples/Wall");
    wall4Entity->setMaterialName("Examples/Wall");

    // Cast no shadows
    floorEntity->setCastShadows(true);
    wall1Entity->setCastShadows(true);
    wall2Entity->setCastShadows(true);
    wall3Entity->setCastShadows(true);
    wall4Entity->setCastShadows(true);
    
    floorEntity->setQueryFlags(2);
} // createEntities

void RoomObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
	using namespace StringHelper;

    this->sceneManager = &sceneMgr;

    createEntities();
} // createScene

void RoomObject::show() {
    using namespace StringHelper;
    visible = true;

    floorNode = sceneManager->getRootSceneNode()->createChildSceneNode(concat<int>("FloorNode", id));
    wallNodes[0] = sceneManager->getRootSceneNode()->createChildSceneNode(concat<int>("Wall1Node", id));
    wallNodes[1] = sceneManager->getRootSceneNode()->createChildSceneNode(concat<int>("Wall2Node", id));
    wallNodes[2] = sceneManager->getRootSceneNode()->createChildSceneNode(concat<int>("Wall3Node", id));
    wallNodes[3] = sceneManager->getRootSceneNode()->createChildSceneNode(concat<int>("Wall4Node", id));

    // Attach them to nodes
    floorNode->attachObject(floorEntity);
    wallNodes[0]->attachObject(wall1Entity);
    wallNodes[1]->attachObject(wall2Entity);
    wallNodes[2]->attachObject(wall3Entity);
    wallNodes[3]->attachObject(wall4Entity);

	// Set position
	setPosition(position);
} // show

void RoomObject::hide() {
    visible = false;

	ObjectManager::getInstance().destroySceneNode("FloorEntity", id);
	ObjectManager::getInstance().destroySceneNode("Wall1Node", id);
	ObjectManager::getInstance().destroySceneNode("Wall2Node", id);
	ObjectManager::getInstance().destroySceneNode("Wall3Node", id);
	ObjectManager::getInstance().destroySceneNode("Wall4Node", id);
} // hide

/**
 * Create the meshes for the 6 planes of the room
 */
void RoomObject::createMeshes() {
	using namespace StringHelper;

    Ogre::MeshManager::getSingleton().createPlane(concat<int>("floor", id), 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *floor, 
        dimensions.width, dimensions.depth, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.width / dimensions.height), MathHelper::max<float>(1, 
        dimensions.depth / dimensions.height), Ogre::Vector3::UNIT_Z);
    
    Ogre::MeshManager::getSingleton().createPlane(concat<int>("wall1", id), 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *walls[0], 
        dimensions.depth, dimensions.height, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.depth / dimensions.height), 1, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane(concat<int>("wall2", id), 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *walls[1], 
        dimensions.depth, dimensions.height, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.depth / dimensions.height), 1, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane(concat<int>("wall3", id), 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *walls[2], 
        dimensions.width, dimensions.height, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.width / dimensions.height), 1, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane(concat<int>("wall4", id), 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *walls[3], 
        dimensions.width, dimensions.height, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.width / dimensions.height), 1, Ogre::Vector3::UNIT_Y);
} // createMeshes

float RoomObject::getWidth() {
    return dimensions.width;
} // getWidth

float RoomObject::getDepth() {
    return dimensions.depth;
} // getDepth

float RoomObject::getHeight() {
    return dimensions.height;
} // getHeight

struct Bounds RoomObject::getBounds() { 
	struct Bounds bounds;
	
	bounds.xStart = position.x;
	bounds.yStart = position.y;
	bounds.zStart = position.z;

	bounds.xEnd = bounds.xStart + dimensions.width;
	bounds.yEnd = bounds.yStart + dimensions.height;
	bounds.zEnd = bounds.zStart + dimensions.depth;

	return bounds;
} // getBounds

struct Dimension RoomObject::getDimensions() {
    return this->dimensions;
} // getDimensions

Ogre::Vector3 RoomObject::getPosition() {
    return this->position;
} // getPosition

void RoomObject::setPosition(Ogre::Vector3 pos) {
    this->position = pos;

    floorNode->setPosition(this->position.x + dimensions.width / 2, this->position.y, this->position.z + dimensions.depth / 2);

	wallNodes[0]->setPosition(this->position.x, this->position.y + dimensions.height / 2, this->position.z + dimensions.depth / 2);
    wallNodes[1]->setPosition(this->position.x + dimensions.width, this->position.y + dimensions.height / 2, this->position.z + dimensions.depth / 2);
    wallNodes[2]->setPosition(this->position.x + dimensions.width / 2, this->position.y + dimensions.height / 2, this->position.z);
    wallNodes[3]->setPosition(this->position.x + dimensions.width / 2, this->position.y + dimensions.height / 2, this->position.z + dimensions.depth);
} // setPosition

bool RoomObject::containsPoint(Ogre::Vector3 point) {
	struct Bounds bounds = getBounds();

	return point.x >= bounds.xStart && point.x <= bounds.xEnd &&
		point.z >= bounds.zStart && point.z <= bounds.zEnd;
} // containsPoint

bool RoomObject::overlaps(struct Bounds rectB) {
	struct Bounds rectA = getBounds();

	if (rectA.xStart < rectB.xEnd && rectA.xEnd > rectB.xStart &&
		rectA.zStart < rectB.zEnd && rectA.zEnd > rectB.zStart) {
		return true;
	} // if

	return false;
} // overlaps

void RoomObject::update(const Ogre::FrameEvent&) {
    if (visible) {
        return;
    } // if

    if (containsPoint(World::getInstance().getPlayerPosition())) {
        show();
    } // if
} // update
