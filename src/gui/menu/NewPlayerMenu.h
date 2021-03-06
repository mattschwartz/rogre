#ifndef _NEW_PLAYER_MENU_H_
#define _NEW_PLAYER_MENU_H_

/**
 * Included files
 */
#include "CEGUI/CEGUI.h"
#include <string>
#include "src/gui/GUIManager.h"

class NewPlayerMenu {
private:
    std::string playerName;
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *titleLabel;
    CEGUI::Window *gameSettingsLabel;
    CEGUI::Window *playerNameLabel;
    CEGUI::Window *playerNameTextField;
    CEGUI::Window *backgroundWindow;
    CEGUI::Window *difficultyLabel;
    CEGUI::Window *difficultyTextField;
    CEGUI::Slider *difficultySlider;
    CEGUI::Window *startingZoneLevelLabel;
    CEGUI::Spinner *startingZoneLevelTextField;
    CEGUI::Window *seedLabel;
    CEGUI::Window *seedTextField;
    CEGUI::Window *blindModeLabel;
#if USE_OGRE_LEGACY
    CEGUI::Checkbox *blindModeCheckbox;
#else
    CEGUI::ToggleButton *blindModeCheckbox;
#endif
    CEGUI::PushButton *backButton;
    CEGUI::PushButton *startGameButton;
    void createWidgets();
    void createRootWindow();
    void registerEvents();
    void startNewPlayer();
    bool difficultyChanged(const CEGUI::EventArgs &e);
    bool backEvent(const CEGUI::EventArgs &e);
    bool startGameEvent(const CEGUI::EventArgs &e);

public:
    NewPlayerMenu();
    ~NewPlayerMenu();
    void show();
    void hide();
};

#endif
