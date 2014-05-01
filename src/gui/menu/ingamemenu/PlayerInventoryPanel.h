#ifndef _PLAYER_INVENTORY_PANEL_H_
#define _PLAYER_INVENTORY_PANEL_H_

/**
 * Included files
 */
#include <CEGUI/CEGUI.h>
#include <vector>

class Item;

class PlayerInventoryPanel {
private:
    bool visible;
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *parent;
    CEGUI::PushButton *inventoryLabel;
    CEGUI::Listbox *inventory;
    CEGUI::PushButton *equipItemButton;
    CEGUI::PushButton *dropItemButton;
    CEGUI::PushButton *examineItemButton;
    std::vector<Item*> inventoryItems;
    void createWidgets();
    void registerEvents();
    
    bool toggleInventory(const CEGUI::EventArgs &e);
    bool equipItemEvent(const CEGUI::EventArgs &e);
    bool dropItemEvent(const CEGUI::EventArgs &e);
    bool examineItemEvent(const CEGUI::EventArgs &e);

public:
    PlayerInventoryPanel();
    ~PlayerInventoryPanel();
    void addPanelTo(CEGUI::Window *mRoot);
};

#endif
