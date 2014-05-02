#ifndef _LOADING_MENU_
#define _LOADING_MENU_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>
#include <string.h>

class LoadingMenu {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *textLabel;
    CEGUI::Window *tipLabel;
    CEGUI::ProgressBar *loadingBar;
    void createWidgets();
    void createRootWindow();

public:
    LoadingMenu();
    ~LoadingMenu();
    void show();
    void hide();
    void setText(std::string text);
    void setProgress(float progress);
};

#endif
