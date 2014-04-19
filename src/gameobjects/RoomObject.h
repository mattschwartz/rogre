#ifndef _ROOM_OBJECT_H_
#define _ROOM_OBJECT_H_

/**
 * Included files
 */
#include "GameObject.h"
#include <vector>
#include <algorithm>

static std::vector<int> idList;

class Room;

/**
 * Data
 */
class RoomObject : public GameObject {
private:
    int id;
    struct Dimension dimensions;
	Room *room;
    void checkId(int id);
    void init();
	void createLights(Ogre::SceneManager &sceneMgr);
    void createMeshes();

public:
    Ogre::Plane *floor;
    Ogre::Plane *walls[4];

    RoomObject(int id, Room *room, float width, float depth, float height, Ogre::Vector3 pos);
    RoomObject(int id, Room *room, struct Dimension d, Ogre::Vector3 pos);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt);
    void keyPressed(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    float getWidth();
    float getDepth();
    float getHeight();
    struct Dimension getDimensions();
    void setDimensions(struct Dimension d);
    Ogre::Vector3 getPosition();
    void setPosition(Ogre::Vector3 pos);

};

#endif
