#ifndef _CHEST_DOODAD_OBJECT_H_
#define _CHEST_DOODAD_OBJECT_H_

/**
 * Included files
 */
#include "DoodadObject.h"
#include "src/doodad/ChestDoodad.h"

class ChestDoodad;

class ChestDoodadObject : public DoodadObject {
private:
    ChestDoodad *chest;

public:
    ChestDoodadObject(ChestDoodad *chest, float x, float z);
    ChestDoodadObject(ChestDoodad *chest, Ogre::Vector3 pos);
    void show();
    void hide();
    void interact();
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
};

#endif
