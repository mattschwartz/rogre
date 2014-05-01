#ifndef _ADVANCED_ATTRIBUTES_PANEL_H_
#define _ADVANCED_ATTRIBUTES_PANEL_H_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>

class Player;

class AdvancedAttributesPanel {
private:
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *playerHealthLabel;
    CEGUI::Window *playerHealthValue;
    CEGUI::Window *playerDmgReductionLabel;
    CEGUI::Window *playerDmgReductionValue;
    CEGUI::Window *playerDmgOutputLabel;
    CEGUI::Window *playerDmgOutputValue;
    void createWidgets();

public:
    AdvancedAttributesPanel();
    ~AdvancedAttributesPanel();
    void addPanelTo(CEGUI::Window *mRoot);
    void removePanelFrom(CEGUI::Window *mRoot);
    void updateAttributes(Player *player);
};

#endif
