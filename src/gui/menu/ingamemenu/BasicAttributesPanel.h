#ifndef _BASIC_ATTRIBUTES_PANEL_H_
#define _BASIC_ATTRIBUTES_PANEL_H_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>
#include "src/main/BaseApplication.h"

class Player;

class BasicAttributesPanel {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *hitpointsLabel;
    CEGUI::Window *hitpointsValue;
    CEGUI::Window *armorLabel;
    CEGUI::Window *armorValue;
    CEGUI::Window *strengthLabel;
    CEGUI::Window *strengthValue;
    void createWidgets();

public:
    BasicAttributesPanel();
    ~BasicAttributesPanel();
    void addPanelTo(CEGUI::Window *mRoot);
    void removePanelFrom(CEGUI::Window *mRoot);
    void updateAttributes(Player *player);
};

#endif
