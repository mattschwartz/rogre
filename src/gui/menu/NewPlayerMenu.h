#ifndef _NEW_PLAYER_MENU_H_
#define _NEW_PLAYER_MENU_H_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>
#include <string>

class NewPlayerMenu {
private:
    std::string playerName;
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *textLabel;
    CEGUI::Window *playerNameTextField;
    CEGUI::PushButton *backButton;
    CEGUI::PushButton *startGameButton;
    void createWidgets();
    void createRootWindow();
    void registerEvents();
    bool backEvent(const CEGUI::EventArgs &e);
    bool startGameEvent(const CEGUI::EventArgs &e);

public:
    NewPlayerMenu();
    ~NewPlayerMenu();
    void show();
    void hide();
};

#endif
