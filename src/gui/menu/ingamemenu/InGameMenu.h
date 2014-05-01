#ifndef _IN_GAME_MENU_H_
#define _IN_GAME_MENU_H_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>

class Item;
class PlayerAttributesPanel;
class PlayerInventoryPanel;

class InGameMenu {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::ProgressBar *healthBar;
    CEGUI::Window *scoreLabel;
    PlayerAttributesPanel *playerAttributes;
    PlayerInventoryPanel *playerInventory;

    void createWidgets();
    void createRootWindow();

public:
    InGameMenu();
    ~InGameMenu();
    void show();
    void hide();

};

#endif
