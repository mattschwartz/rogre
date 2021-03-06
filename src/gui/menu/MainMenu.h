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
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *titleLabel;
    CEGUI::Window *backgroundWindow;
    CEGUI::PushButton *newPlayerButton;
    CEGUI::PushButton *loadPlayerButton;
    CEGUI::PushButton *hiScoresButton;
    CEGUI::PushButton *quitButton;
    CEGUI::PushButton *creditButton;
    void createButtons();
    void createRootWindow();
    void registerEvents();
    bool newPlayerEvent(const CEGUI::EventArgs &e);
    bool loadPlayerEvent(const CEGUI::EventArgs &e);
    bool hiScoresEvent(const CEGUI::EventArgs &e);
    bool quitEvent(const CEGUI::EventArgs &e);
    bool creditEvent(const CEGUI::EventArgs &e);

public:
    MainMenu();
    ~MainMenu();
    void show();
    void hide();
};

#endif
