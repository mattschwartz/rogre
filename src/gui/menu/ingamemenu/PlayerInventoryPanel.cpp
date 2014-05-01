/**
 * Included files
 */
#include "PlayerInventoryPanel.h"
#include "src/items/Item.h"

PlayerInventoryPanel::PlayerInventoryPanel() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    registerEvents();
} // constructor

void PlayerInventoryPanel::createWidgets() {
    using namespace CEGUI;

    inventoryLabel = windowManager.createWindow("OgreTray/Title", "InGameMenu/inventoryLabel");

    inventory = static_cast<Listbox*>(
        windowManager.createWindow("OgreTray/Listbox", "InGameMenu/inventory"));
    equipItemButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InGameMenu/equipItemButton"));
    dropItemButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InGameMenu/equipItemButton"));
    examineItemButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InGameMenu/equipItemButton"));

    inventoryLabel->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    inventoryLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(1.0f, -335.0f)));
    inventoryLabel->setText("Inventory");

    inventory->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 250.0f)));
    inventory->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(1.0f, -295.0f)));
    
    equipItemButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    equipItemButton->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(1.0f, -45.0f)));
    equipItemButton->setText("Equip");
    
    dropItemButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    dropItemButton->setPosition(UVector2(UDim(1.0f, -210.0f), UDim(1.0f, -45.0f)));
    dropItemButton->setText("Drop");
    
    examineItemButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    examineItemButton->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(1.0f, -45.0f)));
    examineItemButton->setText("Examine");
} // createWidgets

void PlayerInventoryPanel::registerEvents() {
    using namespace CEGUI;
    
    equipItemButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&PlayerInventoryPanel::equipItemEvent, this));
    dropItemButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&PlayerInventoryPanel::dropItemEvent, this));
    examineItemButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&PlayerInventoryPanel::examineItemEvent, this));
} // registerEvents

void PlayerInventoryPanel::addPanelTo(CEGUI::Window *mRoot) {
    mRoot->addChild(inventoryLabel);
    mRoot->addChild(inventory);
    mRoot->addChild(equipItemButton);
    mRoot->addChild(dropItemButton);
    mRoot->addChild(examineItemButton);
} // addPanelTo

bool PlayerInventoryPanel::equipItemEvent(const CEGUI::EventArgs &e) {
    return true;
} // equipItemEvent

bool PlayerInventoryPanel::dropItemEvent(const CEGUI::EventArgs &e) {
    return true;
} // dropItemButton

bool PlayerInventoryPanel::examineItemEvent(const CEGUI::EventArgs &e) {
    return true;
} // examineItemButton
