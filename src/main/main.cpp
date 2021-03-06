/**
 *  Note: Code modified from the Ogre Tutorial Framework
 *  http://www.ogre3d.org/tikiwiki/
 */

/**
 * Included files
 */
#include "main.h"
#include "src/entities/player/Player.h"
#include "src/input/KeyHandler.h"
#include "src/gameobjects/ObjectManager.h"
#include "src/gameobjects/RoomObject.h"
#include "src/gameobjects/PlayerObject.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "src/world/World.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/MainMenu.h"

/**
 * Data
 */
MainApplication::MainApplication() {
} // constructor

MainApplication::~MainApplication() {
} // destructor

void MainApplication::createScene() {
    GUIManager::getInstance().init();
    ObjectManager::getInstance().init(mSceneMgr, mCamera);
    SoundManager::getInstance().init();
	KeyHandler::getInstance().init();
    
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    mSceneMgr->setFog(Ogre::FOG_EXP, Ogre::ColourValue(0.25, 0.25, 0.25), Ogre::Real(0.025));

    GUIManager::getInstance().mainMenu->show();
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
