#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

/**
 * Included files
 */
#include "src/main/BaseApplication.h"
#include "CEGUI/CEGUI.h"
#if USE_OGRE_LEGACY
    #include "CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h"
#else
    #include "CEGUI/RendererModules/Ogre/Renderer.h"
#endif

class MainMenu;
class NewPlayerMenu;
class LoadPlayerMenu;
class HiScoresMenu;
class OptionsMenu;
class LoadingMenu;

/**
 * Data
 */
class GUIManager {
private:
    CEGUI::OgreRenderer *mRenderer;
    GUIManager() {}
    GUIManager(GUIManager const&);
    void operator=(GUIManager const&);
    void initCEGUI();
    void setResourceGroups();
    void setLookNFeel();

public:
    MainMenu *mainMenu;
    NewPlayerMenu *newPlayerMenu;
    LoadPlayerMenu *loadPlayerMenu;
    HiScoresMenu *hiScoresMenu;
    OptionsMenu *optionsMenu;
    LoadingMenu *loadingMenu;

    static GUIManager &getInstance() {
        static GUIManager instance;
        return instance;
    } // getInstance

    void init();
    void hideCurrentMenu();
};

#endif
