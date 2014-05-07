#ifndef _STAIRS_DOODAD_OBJECT_H_
#define _STAIRS_DOODAD_OBJECT_H_

/**
 * Included files
 */
#include "DoodadObject.h"
#include <Ogre.h>

class StairsDoodadObject : public DoodadObject {
private:
public:
    StairsDoodadObject(float x, float z);
    StairsDoodadObject(Ogre::Vector3 pos);

    void interact();
    void show();
    void hide();
    void createObject(Ogre::SceneManager &sceneMgr, Ogre::Camera *camera);
    void update(const Ogre::FrameEvent &evt);
};

#endif
