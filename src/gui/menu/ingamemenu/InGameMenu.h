#ifndef _IN_GAME_MENU_H_
#define _IN_GAME_MENU_H_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>

class PlayerAttributesPanel;
class PlayerInventoryPanel;
class InfoLogPanel;
class Player;

class InGameMenu {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::ProgressBar *healthBar;
    CEGUI::Window *scoreLabel;
    PlayerAttributesPanel *playerAttributes;
    PlayerInventoryPanel *playerInventory;
    InfoLogPanel *infoLog;

    void createWidgets();
    void createRootWindow();

public:
    InGameMenu();
    ~InGameMenu();
    void appendText(std::string text);
    void appendLine(std::string  text);
    void updateAttributes(Player *player);
    void show();
    void hide();

};

#endif
