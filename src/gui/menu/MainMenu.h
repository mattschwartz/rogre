#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

/**
 * Included files
 */
#include <Ogre.h>
#include "MainMenu.h"
#include "CEGUI/CEGUI.h"

/**
 * Data
 */
class MainMenu {
private:
    CEGUI::Window *mRoot;

public:
    MainMenu();
    ~MainMenu();
};

#endif
