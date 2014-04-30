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
    CEGUI::ProgressBar *loadingBar;
    void createWidgets();
    void createRootWindow();

public:
    LoadingMenu();
    ~LoadingMenu();
    void show(std::string title);
    void hide();
    void setProgress(float progress);
};

#endif
