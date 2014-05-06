#ifndef _DEATH_MENU_H_
#define _DEATH_MENU_H_

/**
 * Included files
 */

#include <CEGUI/CEGUI.h>

class DeathMenu {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *titleLabel;
    CEGUI::Window *textLabel;
    CEGUI::Window *scoreTextField;
    CEGUI::Window *backgroundWindow;
    CEGUI::PushButton *quitToMenuButton;
    CEGUI::PushButton *quitGameButton;
    void createWidgets();
    void createRootWindow();
    void registerEvents();
    bool quitToMenuEvent(const CEGUI::EventArgs &e);
    bool quitGameEvent(const CEGUI::EventArgs &e);

public:
    DeathMenu();
    ~DeathMenu();
    void show();
    void hide();

};

#endif
