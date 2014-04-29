#ifndef _ROOM_OBJECT_H_
#define _ROOM_OBJECT_H_

/**
 * Included files
 */
#include "GameObject.h"
#include <vector>
#include <algorithm>

class Room;

/**
 * Data
 */
class RoomObject : public GameObject {
private:
    int id;
    bool visible;
    struct Dimension dimensions;
	Room *room;
    Ogre::Entity *floorEntity;
    Ogre::Entity *wall1Entity;
    Ogre::Entity *wall2Entity;
    Ogre::Entity *wall3Entity;
    Ogre::Entity *wall4Entity;
    Ogre::SceneManager *sceneManager;

    void init();
    void createMeshes();
    void createEntities();

public:
    Ogre::Plane *floor;
    Ogre::Plane *walls[4];
	Ogre::SceneNode *floorNode;
	Ogre::SceneNode *wallNodes[4];

    RoomObject(Room *room, float width, float depth, float height, Ogre::Vector3 pos);
    RoomObject(Room *room, struct Dimension d, Ogre::Vector3 pos);
	~RoomObject();

    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void show();
    void hide();
    void setPosition(Ogre::Vector3 pos);

	bool containsPoint(Ogre::Vector3 point);
	bool overlaps(struct Bounds rectB);
    float getWidth();
    float getDepth();
    float getHeight();
	struct Bounds getBounds();
    struct Dimension getDimensions();
    Ogre::Vector3 getPosition();

    void update(const Ogre::FrameEvent &evt);
    bool contains(const OIS::MouseEvent &evt) { return false; }
    void keyPressed(const OIS::KeyEvent &arg) {}
    void mouseMoved(const OIS::MouseEvent &evt) {}
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}

};

#endif
