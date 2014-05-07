#ifndef _HI_SCORES_MENU_H_
#define _HI_SCORES_MENU_H_

/**
 * Included files
 */
#include "CEGUI/CEGUI.h"

class HiScoresMenu {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *titleLabel;
    CEGUI::Window *scores;
    CEGUI::Window *backgroundWindow;
    CEGUI::PushButton *backButton;
    CEGUI::PushButton *resetScoresButton;
    void createWidgets();
    void createRootWindow();
    void registerEvents();
    bool backEvent(const CEGUI::EventArgs &e);
    bool resetScoresEvent(const CEGUI::EventArgs &e);

public:
    HiScoresMenu();
    void show();
    void hide();
};

#endif
