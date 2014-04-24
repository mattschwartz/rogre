#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

/**
 * Included files
 */
#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"

/**
 * Data
 */
class GUIManager {
private:
    CEGUI::OgreRenderer *mRenderer;
    GUIManager() {}
    GUIManager(GUIManager const&);
    void operator=(GUIManager const&);
    void setResourceGroups();
    void setLookNFeel();

public:
    static GUIManager &getInstance() {
        static GUIManager instance;
        return instance;
    } // getInstance

    void initCEGUI();
};

#endif
