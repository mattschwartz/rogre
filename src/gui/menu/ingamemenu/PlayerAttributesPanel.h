#ifndef _PLAYER_ATTRIBUTES_PANEL_H_
#define _PLAYER_ATTRIBUTES_PANEL_H_

/** 
 * Included files
 */
#include <CEGUI/CEGUI.h>
#include "src/main/BaseApplication.h"

class AdvancedAttributesPanel;
class BasicAttributesPanel;
class Player;

class PlayerAttributesPanel {
private:
    int pageNumber;
    CEGUI::Window *mRoot;
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *playerAttributesTitle;
    CEGUI::PushButton *togglePageButton;
    AdvancedAttributesPanel *advancedAttributesPanel;
    BasicAttributesPanel *basicAttributesPanel;
    void createWidgets();
    void createRootWindow();
    void registerEvents();

    bool togglePageEvent(const CEGUI::EventArgs &e);

public:
    PlayerAttributesPanel();
    ~PlayerAttributesPanel();
    void updateAttributes(Player *player);
    void addPanelTo(CEGUI::Window *mRoot);
};

#endif
