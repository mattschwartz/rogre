/**
 * Included files
 */
#include "RoomObject.h"
#include "src/world/Room.h"
#include "src/utility/MathHelper.h"

/**
 * Data
 */
RoomObject::RoomObject(int id, float width, float depth, float height, 
                       Ogre::Vector3 pos) : GameObject(pos) {
    checkId(id);

    this->id = id;
    this->dimensions.width = width;
    this->dimensions.depth = depth;
    this->dimensions.height = height;
    init();
} // constructor

RoomObject::RoomObject(int id, struct Dimension d, Ogre::Vector3 pos) : 
    GameObject(pos) {
    checkId(id);

    this->id = id;
    this->dimensions = d;
    init();
} // constructor

void RoomObject::checkId(int id) {
    if (!idList.empty() &&
        std::find(idList.begin(), idList.end(), id) != idList.end()) {
            throw std::invalid_argument("All IDs must be unique!");
    } // if

    idList.push_back(id);
} // checkId

/** 
 * Performs the tasks that all constructors have in common
 * in one, convenient function.
 */
void RoomObject::init() {
    // Initialize planes that make up the room
    floor = new Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);
    walls[0] = new Ogre::Plane(Ogre::Vector3::UNIT_X, 0);
    walls[1] = new Ogre::Plane(-Ogre::Vector3::UNIT_X, 0);
    walls[2] = new Ogre::Plane(Ogre::Vector3::UNIT_Z, 0);
    walls[3] = new Ogre::Plane(-Ogre::Vector3::UNIT_Z, 0);
} // init

void RoomObject::createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera) {
    // Let there be lights
    createLights(sceneMgr);

    // manage meshes for planes
    createMeshes();

    // Create plane entities
    Ogre::Entity *floorEntity = sceneMgr.createEntity("FloorEntity" + id, "floor" + id);
    Ogre::Entity *wall1Entity = sceneMgr.createEntity("Wall1Entity" + id, "wall1" + id);
    Ogre::Entity *wall2Entity = sceneMgr.createEntity("Wall2Entity" + id, "wall2" + id);
    Ogre::Entity *wall3Entity = sceneMgr.createEntity("Wall3Entity" + id, "wall3" + id);
    Ogre::Entity *wall4Entity = sceneMgr.createEntity("Wall4Entity" + id, "wall4" + id);
    Ogre::SceneNode *floorNode = sceneMgr.getRootSceneNode()->createChildSceneNode("FloorNode" + id);
    Ogre::SceneNode *wall1Node = sceneMgr.getRootSceneNode()->createChildSceneNode("Wall1Node" + id);
    Ogre::SceneNode *wall2Node = sceneMgr.getRootSceneNode()->createChildSceneNode("Wall2Node" + id);
    Ogre::SceneNode *wall3Node = sceneMgr.getRootSceneNode()->createChildSceneNode("Wall3Node" + id);
    Ogre::SceneNode *wall4Node = sceneMgr.getRootSceneNode()->createChildSceneNode("Wall4Node" + id);

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

    floorNode->setPosition(this->position.x, this->position.y - dimensions.height / 2, this->position.z);

    wall1Node->setPosition(this->position.x -dimensions.width / 2, this->position.y, this->position.z);
    wall2Node->setPosition(this->position.x + dimensions.width / 2, this->position.y, this->position.z);
    wall3Node->setPosition(this->position.x, this->position.y, this->position.z - dimensions.depth / 2);
    wall4Node->setPosition(this->position.x, this->position.y, this->position.z + dimensions.depth / 2);

    // Attach them to nodes
    floorNode->attachObject(floorEntity);
    wall1Node->attachObject(wall1Entity);
    wall2Node->attachObject(wall2Entity);
    wall3Node->attachObject(wall3Entity);
    wall4Node->attachObject(wall4Entity);
} // createScene

/**
 * Sets up the lights for the room.
 */
void RoomObject::createLights(Ogre::SceneManager &sceneMgr) {
    Ogre::Light *pointLight;


    pointLight = sceneMgr.createLight("pointLight" + id);

    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(position.x + 0, position.y + getHeight() / 2 - 1, position.z + 0);
    pointLight->setDiffuseColour(0.3f, 0.3f, 0.3f);
    pointLight->setSpecularColour(1.0f, 1.0f, 1.0f);
} // createLights

/**
 * Create the meshes for the 6 planes of the room
 */
void RoomObject::createMeshes() {
    Ogre::MeshManager::getSingleton().createPlane("floor" + id, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *floor, 
        dimensions.width, dimensions.depth, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.width / dimensions.height), MathHelper::max<float>(1, 
        dimensions.depth / dimensions.height), Ogre::Vector3::UNIT_Z);
    
    Ogre::MeshManager::getSingleton().createPlane("wall1" + id, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *walls[0], 
        dimensions.depth, dimensions.height, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.depth / dimensions.height), 1, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane("wall2" + id, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *walls[1], 
        dimensions.depth, dimensions.height, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.depth / dimensions.height), 1, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane("wall3" + id, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *walls[2], 
        dimensions.width, dimensions.height, 1, 1, true, 1, MathHelper::max<float>(1, 
        dimensions.width / dimensions.height), 1, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane("wall4" + id, 
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

struct Dimension RoomObject::getDimensions() {
    return this->dimensions;
} // getDimensions

void RoomObject::setDimensions(struct Dimension d) {
    this->dimensions = d;
} // setDimensions

Ogre::Vector3 RoomObject::getPosition() {
    return this->position;
} // getPosition

void RoomObject::setPosition(Ogre::Vector3 pos) {
    this->position = pos;
} // setPosition

bool RoomObject::contains(const OIS::MouseEvent &evt) {
    return false;
} // contains

void RoomObject::update(const Ogre::FrameEvent &evt) {
} // render

void RoomObject::keyPressed(const OIS::KeyEvent &arg) {}

void RoomObject::mouseMoved(const OIS::MouseEvent &evt) {
} // mouseMoved

void RoomObject::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mousePressed

void RoomObject::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
} // mouseReleased
