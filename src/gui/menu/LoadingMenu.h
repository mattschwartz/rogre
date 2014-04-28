#ifndef _LOADING_MENU_
#define _LOADING_MENU_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>

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
    void show();
    void hide();
    void setProgress(float progress);
};

#endif
