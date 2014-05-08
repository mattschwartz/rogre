#ifndef _CreditPage_H_
#define _CreditPage_H_

/**
 * Included files
 */

#include <Ogre.h>
#include "CreditPage.h"
#include "CEGUI/CEGUI.h"

class CreditPage{
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *titleLabel;
    CEGUI::Window *credits;
    CEGUI::Window *backgroundWindow;
    CEGUI::PushButton *backButton;
    void createWidgets();
    void createRootWindow();
    void registerEvents();
    bool backEvent(const CEGUI::EventArgs &e);

public:
    CreditPage();
    void show();
    void hide();
};

#endif

































