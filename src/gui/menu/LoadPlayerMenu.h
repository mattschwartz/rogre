#ifndef _LOAD_PLAYER_MENU_H_
#define _LOAD_PLAYER_MENU_H_

/**
 * Included files
 */
#include "CEGUI/CEGUI.h"
#include <src/main/BaseApplication.h>

class LoadPlayerMenu {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *titleLabel;
    CEGUI::Window *backgroundWindow;
    CEGUI::Listbox *playerSaveListbox;
    CEGUI::PushButton *backButton;
    CEGUI::PushButton *loadSaveButton;
    CEGUI::PushButton *deleteSaveButton;
    void createWidgets();
    void createRootWindow();
    void registerEvents();
    bool backEvent(const CEGUI::EventArgs &e);
    bool saveListSelectionChanged(const CEGUI::EventArgs &e);
    bool deleteSaveEvent(const CEGUI::EventArgs &e);
    bool loadSaveEvent(const CEGUI::EventArgs &e);

public:
    LoadPlayerMenu();
    void show();
    void hide();
};

#endif
