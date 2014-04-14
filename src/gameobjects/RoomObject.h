#ifndef _ROOM_OBJECT_H_
#define _ROOM_OBJECT_H_

/**
 * Included files
 */
#include "GameObject.h"
#include <vector>
#include <algorithm>

/** 
 * Forward declarations
 */
class Room;

static std::vector<int> idList;

/**
 * Data
 */
class RoomObject : public GameObject {
private:
    int id;
    Room *room;
    struct Dimension dimensions;
    Ogre::Plane *floor;
    Ogre::Plane *walls[4];
    void checkId(int id);
    void init();
	void createLights(Ogre::SceneManager &sceneMgr);
    void createMeshes();


public:
    RoomObject(int id, float width, float depth, float height, Ogre::Vector3 pos);
    RoomObject(int id, struct Dimension d, Ogre::Vector3 pos);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    float getWidth();
    float getDepth();
    float getHeight();
    struct Dimension getDimensions();
    void setDimensions(struct Dimension d);
    Ogre::Vector3 getPosition();
    void setPosition(Ogre::Vector3 pos);

};

#endif
