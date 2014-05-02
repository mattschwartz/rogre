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
    CEGUI::Window *titleLabel;
    CEGUI::PushButton *saveAndResumeButton;
    CEGUI::PushButton *quitToMenuButton;
    CEGUI::PushButton *quitGameButton;
    CEGUI::Window *gameSoundsLabel;
    CEGUI::Window *menuSoundsLabel;
    //CEGUI::ToggleButton *gameSoundsEnabledCheckbox;
    //CEGUI::ToggleButton *menuSoundsEnabledCheckbox;
    CEGUI::Checkbox *gameSoundsEnabledCheckbox;
    CEGUI::Checkbox *menuSoundsEnabledCheckbox;
    void createButtons();
    void createRootWindow();
    void registerEvents();
    //bool OptionsMenu::toggleGameSounds(const CEGUI::EventArgs &e);
    //bool OptionsMenu::toggleMenuSounds(const CEGUI::EventArgs &e);
    bool toggleGameSounds(const CEGUI::EventArgs &e);
    bool toggleMenuSounds(const CEGUI::EventArgs &e);
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
