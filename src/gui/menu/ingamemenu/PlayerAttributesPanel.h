#ifndef _PLAYER_ATTRIBUTES_PANEL_H_
#define _PLAYER_ATTRIBUTES_PANEL_H_

/** 
 * Included files
 */
#include <CEGUI/CEGUI.h>

class PlayerAttributesPanel {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *palyerAttributesTitle;
    CEGUI::Window *playerHealthLabel;
    CEGUI::Window *playerHealthValue;
    CEGUI::Window *playerDmgReductionLabel;
    CEGUI::Window *playerDmgReductionValue;
    CEGUI::Window *playerDmgOutputLabel;
    CEGUI::Window *playerDmgOutputValue;
    void createWidgets();

public:
    PlayerAttributesPanel();
    ~PlayerAttributesPanel();
    void addPanelTo(CEGUI::Window *mRoot);
};

#endif
