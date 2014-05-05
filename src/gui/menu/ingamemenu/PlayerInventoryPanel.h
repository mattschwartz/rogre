#ifndef _PLAYER_INVENTORY_PANEL_H_
#define _PLAYER_INVENTORY_PANEL_H_

/**
 * Included files
 */
#include <vector>
#include "CEGUI/CEGUI.h"
#include "src/main/BaseApplication.h"

class Item;
class Player;

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
    bool inventorySelectionChanged(const CEGUI::EventArgs &e);
    bool toggleInventory(const CEGUI::EventArgs &e);
    bool equipItemEvent(const CEGUI::EventArgs &e);
    bool dropItemEvent(const CEGUI::EventArgs &e);
    bool examineItemEvent(const CEGUI::EventArgs &e);

public:
    PlayerInventoryPanel();
    ~PlayerInventoryPanel();
    void addPanelTo(CEGUI::Window *mRoot);
    void addItem(Item *item);
    void loadPlayer(Player *player);
};

#endif
