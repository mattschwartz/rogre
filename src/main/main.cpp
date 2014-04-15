/**
 *  Note: Code modified from the Ogre Tutorial Framework
 *  http://www.ogre3d.org/tikiwiki/
 */

/**
 * Included files
 */
#include "main.h"
#include "src/gameobjects/RoomObject.h"
#include "src/gameobjects/ObjectManager.h"

/**
 * Data
 */
MainApplication::MainApplication() {
} // constructor

MainApplication::~MainApplication() {
} // destructor

void MainApplication::createScene() {
    ObjectManager::getInstance().init(mSceneMgr, mCamera);

    RoomObject *ro = new RoomObject(0, 75, 15, 10, Ogre::Vector3(0, 0, 0));
    RoomObject *ro2 = new RoomObject(1, 15, 75, 10, Ogre::Vector3(75/2 + 8, 0, 0));
    
    ObjectManager::getInstance().spawnObject(ro);
    ObjectManager::getInstance().spawnObject(ro2);

    mCamera->setPosition(0, ro->getHeight() * 1.25, ro->getDepth() * 0.75);
    mSceneMgr->setFog(Ogre::FOG_EXP, Ogre::ColourValue(0.5, 0.5, 0.5), Ogre::Real(0.005));
    mCamera->lookAt(0, 0, 0);
} // createScene

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        MainApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
