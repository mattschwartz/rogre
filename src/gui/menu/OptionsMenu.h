#ifndef _OPTIONS_MENU_
#define _OPTIONS_MENU_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>

class OptionsMenu {
private:
    bool visible;
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::PushButton *saveAndResumeButton;
    CEGUI::PushButton *quitToMenuButton;
    CEGUI::PushButton *quitGameButton;
    void createButtons();
    void createRootWindow();
    void registerEvents();
    bool saveAndResumeEvent(const CEGUI::EventArgs &e);
    bool quitToMenuEvent(const CEGUI::EventArgs &e);
    bool quitGameEvent(const CEGUI::EventArgs &e);

public:
    OptionsMenu();
    ~OptionsMenu();
    void show();
    void hide();
    void toggle();
};

#endif
