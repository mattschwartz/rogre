#ifndef _ROOM_OBJECT_H_
#define _ROOM_OBJECT_H_

/**
 * Included files
 */
#include "GameObject.h"
#include <vector>
#include <algorithm>

static int roomCount = 0;

class Room;

/**
 * Data
 */
class RoomObject : public GameObject {
private:
    int id;
    struct Dimension dimensions;
	Room *room;
    void init();
	void createLights(Ogre::SceneManager &sceneMgr);
    void createMeshes();

public:
    Ogre::Plane *floor;
    Ogre::Plane *walls[4];
	Ogre::SceneNode *floorNode;
	Ogre::SceneNode *wallNodes[4];

    RoomObject(Room *room, float width, float depth, float height, Ogre::Vector3 pos);
    RoomObject(Room *room, struct Dimension d, Ogre::Vector3 pos);
	~RoomObject();
	bool containsPoint(Ogre::Vector3 point);
	bool overlaps(struct Bounds rectB);
    float getWidth();
    float getDepth();
    float getHeight();
	struct Bounds getBounds();
    struct Dimension getDimensions();
    Ogre::Vector3 getPosition();
    void setPosition(Ogre::Vector3 pos);

    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

};

#endif
