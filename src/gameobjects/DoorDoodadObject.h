#ifndef _DOOR_DOODAD_OBJECT_H_
#define _DOOR_DOODAD_OBJECT_H_

/**
 * Included files
 */
#include "DoodadObject.h"

class DoorDoodadObject : public DoodadObject {
private:
    Ogre::Degree rollBy;

public:
    DoorDoodadObject(float x, float z);
    DoorDoodadObject(Ogre::Vector3 pos);
    void setFacing(Ogre::Vector3 facing);
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
    void show();
    void hide();
};

#endif
