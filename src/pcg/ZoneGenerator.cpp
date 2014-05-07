/**
 * Included files
 */
#include "ZoneGenerator.h"
#include "src/gameobjects/RoomObject.h"
#include "src/gameobjects/DoodadObject.h"
#include "src/gameobjects/DoorDoodadObject.h"
#include "src/gameobjects/LootObject.h"
#include "src/gameobjects/EntityObject.h"
#include "src/world/Zone.h"
#include "src/world/Room.h"
#include "src/utility/StringHelper.h"
#include "src/utility/MathHelper.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/LoadingMenu.h"
#include "src/gameobjects/StairsDoodadObject.h"
#include <vector>

Zone *ZoneGenerator::generate(int seed, int monsterDifficulty, int zoneLevel, int numRooms) {
    float x;
    float z;
    float width;
    float depth;
    Room *r;
    Zone *zone = new Zone(monsterDifficulty, zoneLevel);
	struct Wall wall;
    srand(seed);
        
    GUIManager::getInstance().loadingMenu->setProgress(0.0f);
    GUIManager::getInstance().loadingMenu->setText("Generating rooms ...");

    x = 0.0f;
    z = 0.0f;
	width = (float)(rand() % MAX_ROOM_WIDTH + MIN_ROOM_WIDTH);
	depth = (float)(rand() % MAX_ROOM_DEPTH + MIN_ROOM_DEPTH);

    r = RoomGenerator::getInstance().generate(zone, x, z,
        width, depth);

	spawnRoom(zone, r, x, z, width, depth);

    for (int i = 1; i < numRooms; i++) {
		if (!freeWalls.empty()) {
			std::random_shuffle(freeWalls.begin(), freeWalls.end());

			wall = freeWalls.back();
			freeWalls.pop_back();
		} // if

		x = wall.x1;
		z = wall.z1;
		width = (float)(rand() % MAX_ROOM_WIDTH + MIN_ROOM_WIDTH);
		depth = (float)(rand() % MAX_ROOM_DEPTH + MIN_ROOM_DEPTH);

		if (wall.direction == Ogre::Vector3::UNIT_Z) {
			z -= depth;
		} else if (wall.direction == Ogre::Vector3::UNIT_X) {
			x -= width;
		}

		if (overlaps(zone, x, z, width, depth)) {
			continue;
		} // if

        r = RoomGenerator::getInstance().generate(zone, x, z,
            width, depth);

		spawnRoom(zone, r, x, z, width, depth);

        // drop a door here
        float doorX;
        float doorZ;
        DoorDoodadObject *door;

        // North wall
        if (wall.direction == Ogre::Vector3::UNIT_Z) { 
            float room1_wallWidth = (wall.x2 - wall.x1);
            float room2_wallWidth = width;
            float wallLength = MathHelper::min<float>(room1_wallWidth, room2_wallWidth);

            doorX = x + (rand() % (int)wallLength) + 3;
            doorZ = z + depth;
            door = new DoorDoodadObject(doorX, doorZ);
            door->setFacing(Ogre::Vector3::UNIT_Z);
        } // if
        // South wall
        else if (wall.direction == Ogre::Vector3::NEGATIVE_UNIT_Z) {
            float room1_wallWidth = (wall.x2 - wall.x1);
            float room2_wallWidth = width;
            float wallLength = MathHelper::min<float>(room1_wallWidth, room2_wallWidth);

            doorX = x + (rand() % (int)wallLength) + 3;
            doorZ = z;
            door = new DoorDoodadObject(doorX, doorZ);
            door->setFacing(Ogre::Vector3::NEGATIVE_UNIT_Z);
        } // else if
        // West wall
        else if (wall.direction == Ogre::Vector3::UNIT_X) {
            float room1_wallDepth = MathHelper::abs<float>(wall.z2 - wall.z1);
            float room2_wallDepth = depth;
            float wallDepth = MathHelper::min<float>(room1_wallDepth, room2_wallDepth);
            
            doorX = x + width;
            doorZ = z + (rand() % (int)wallDepth) + 3;
            door = new DoorDoodadObject(doorX, doorZ);
            door->setFacing(Ogre::Vector3::UNIT_X);
        } // else if
        // East wall
        else if (wall.direction == Ogre::Vector3::NEGATIVE_UNIT_X) {
            float room1_wallDepth = MathHelper::abs<float>(wall.z2 - wall.z1);
            float room2_wallDepth = depth;
            float wallDepth = MathHelper::min<float>(room1_wallDepth, room2_wallDepth);
            
            doorX = x;
            doorZ = z + (rand() % (int)wallDepth) + 3;
            door = new DoorDoodadObject(doorX, doorZ);
            door->setFacing(Ogre::Vector3::UNIT_X);
        } // else if

        zone->addDoorDoodad(door);

        GUIManager::getInstance().loadingMenu->setProgress((float)(i / (numRooms*1.0f)));
	} // for
    

    // get random room
    float stairsX;
    float stairsZ;
    int randomRoom = rand() % zone->rooms.size();
    RoomObject *rr = zone->rooms.at(randomRoom);

    // pick random location within it
    stairsX = rand() % (int)(rr->getWidth());
    stairsZ = rand() % (int)(rr->getDepth());

    // make sure the entire object fits

    // add it to the world
    zone->addDoodad(new StairsDoodadObject(stairsX, stairsZ));
    
    GUIManager::getInstance().loadingMenu->setText("Building doodads ...");
    for (DoodadObject *o : zone->doodads) {
        ObjectManager::getInstance().spawnObject(o);
    } // for
    
    GUIManager::getInstance().loadingMenu->setText("Opening doors ...");
    for (DoorDoodadObject *o : zone->doorDoodads) {
        ObjectManager::getInstance().spawnObject(o);
    } // for
    
    GUIManager::getInstance().loadingMenu->setText("Unearthing trinkets ...");
    for (LootObject *o : zone->loot) {
        ObjectManager::getInstance().spawnObject(o);
    } // for
    
    GUIManager::getInstance().loadingMenu->setText("Populating zone ...");
    for (EntityObject *o : zone->entities) {
        ObjectManager::getInstance().spawnObject(o);
    } // for

    GUIManager::getInstance().loadingMenu->setProgress(100.0f);
    GUIManager::getInstance().loadingMenu->hide();

    spawnLights(zone);
    freeWalls.clear();


    return zone;
} // generate

bool ZoneGenerator::overlaps(Zone *zone, float x, float z, float width, float depth) {
	struct Bounds bounds;

	bounds.xStart = x;
	bounds.zStart = z;
	bounds.xEnd = x + width;
	bounds.zEnd = z + depth;

	for (RoomObject *r : zone->rooms) {
		if (r->overlaps(bounds)) {
			return true;
		} // if
	} // for

	return false;
} // overlaps

void ZoneGenerator::spawnRoom(Zone *zone, Room *room, float x, float z, float width, 
	float depth) {
	struct Wall wall;
	RoomObject *ro = new RoomObject(room, width, depth, 
		DEFAULT_ROOM_HEIGHT, Ogre::Vector3(x, 0, z));
		
	// North wall
	wall.x1 = ro->getPosition().x;
	wall.z1 = ro->getPosition().z;
	wall.x2 = ro->getBounds().xEnd;
	wall.z2 = wall.z1;
	wall.direction = Ogre::Vector3::UNIT_Z;
    wall.wallPointer = ro->walls[0];
	freeWalls.push_back(wall);

	// South wall
	wall.z1 = ro->getBounds().zEnd;
	wall.z2 = wall.z1;
	wall.direction = Ogre::Vector3::NEGATIVE_UNIT_Z;
    wall.wallPointer = ro->walls[1];
	freeWalls.push_back(wall);

	// West wall
	wall.x2 = ro->getPosition().x;
	wall.z1 = ro->getPosition().z;
	wall.z2 = ro->getBounds().zEnd;
	wall.direction = Ogre::Vector3::UNIT_X;
    wall.wallPointer = ro->walls[2];
	freeWalls.push_back(wall);

	// East wall
	wall.x1 = ro->getBounds().xEnd;
	wall.x2 = wall.x1;
	wall.direction = Ogre::Vector3::NEGATIVE_UNIT_X;
    wall.wallPointer = ro->walls[3];
	freeWalls.push_back(wall);

	ObjectManager::getInstance().spawnObject(ro);
	zone->rooms.push_back(ro);
} // addRoom

void ZoneGenerator::spawnLights(Zone *zone) {
    Ogre::SceneManager &sceneMgr = *ObjectManager::getInstance().getSceneManager();
    Ogre::Camera *camera = ObjectManager::getInstance().getCamera();
    Ogre::Vector3 position;
    RoomObject *room;
    Ogre::Light *pointLight;

	using namespace StringHelper;

    int i = rand() % zone->rooms.size();
    room = zone->rooms.at(i);
    position.x = rand() % (int)(room->getWidth());
    position.y = 0;
    position.z = rand() % (int)(room->getDepth());

    pointLight = sceneMgr.createLight(concat<int>("pointLight", lightCount++));

    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(position.x + 0, position.y + room->getHeight() / 2 - 1, position.z + 0);
    pointLight->setDiffuseColour(0.3f, 0.3f, 0.3f);
    pointLight->setSpecularColour(1.0f, 1.0f, 1.0f);
} // spawnLights
