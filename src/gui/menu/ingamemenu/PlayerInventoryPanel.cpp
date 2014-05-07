/**
 * Included files
 */
#include "PlayerInventoryPanel.h"
#include "InGameMenu.h"
#include "src/gui/GUIManager.h"
#include "src/items/Item.h"
#include "src/utility/StringHelper.h"
#include "src/entities/player/Player.h"
#include "src/entities/player/Inventory.h"
#include "src/items/Equippable.h"
#include "src/world/World.h"

PlayerInventoryPanel::PlayerInventoryPanel() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    registerEvents();
} // constructor

void PlayerInventoryPanel::createWidgets() {
    using namespace CEGUI;

    inventoryLabel = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InGameMenu/inventoryLabel"));
    inventory = static_cast<Listbox*>(
        windowManager.createWindow("OgreTray/Listbox", "InGameMenu/inventory"));
    equipItemButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InGameMenu/equipItemButton"));
    examineItemButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InGameMenu/equipItemButton2"));

#if USE_OGRE_LEGACY
    inventoryLabel->setSize(UVector2(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    inventory->setSize(UVector2(UDim(0.0f, 200.0f), UDim(0.0f, 250.0f)));
    equipItemButton->setSize(UVector2(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    examineItemButton->setSize(UVector2(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
#else
    inventoryLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    inventory->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 250.0f)));
    equipItemButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    examineItemButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
#endif
    
    inventoryLabel->setPosition(UVector2(UDim(1.0f, -210.0f), UDim(1.0f, -335.0f)));
    inventoryLabel->setText("Collapse Inventory");

    inventory->setPosition(UVector2(UDim(1.0f, -210.0f), UDim(1.0f, -295.0f)));

    equipItemButton->setPosition(UVector2(UDim(1.0f, -210.0f), UDim(1.0f, -45.0f)));
    equipItemButton->setText("Equip");
    equipItemButton->setEnabled(false);

    examineItemButton->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(1.0f, -45.0f)));
    examineItemButton->setText("Examine");
} // createWidgets

void PlayerInventoryPanel::registerEvents() {
    using namespace CEGUI;
    
    inventory->subscribeEvent(Listbox::EventMouseClick,
        Event::Subscriber(&PlayerInventoryPanel::inventorySelectionChanged, this));
    inventoryLabel->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&PlayerInventoryPanel::toggleInventory, this));
    equipItemButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&PlayerInventoryPanel::equipItemEvent, this));
    examineItemButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&PlayerInventoryPanel::examineItemEvent, this));
} // registerEvents

void PlayerInventoryPanel::addPanelTo(CEGUI::Window *mRoot) {
    parent = mRoot;

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(inventoryLabel);
    mRoot->addChildWindow(inventory);
    mRoot->addChildWindow(equipItemButton);
    mRoot->addChildWindow(examineItemButton);
#else
    mRoot->addChild(inventoryLabel);
    mRoot->addChild(inventory);
    mRoot->addChild(equipItemButton);
    mRoot->addChild(examineItemButton);
#endif

    visible = true;
} // addPanelTo

void PlayerInventoryPanel::addItem(Item *item) {
    inventoryItems.push_back(item);

    inventory->resetList();
    int it = 0;
    for (Item *i : inventoryItems) {
        CEGUI::ListboxTextItem *lbi = new CEGUI::ListboxTextItem(i->getName(), it++, i);
#if USE_OGRE_LEGACY
        lbi->setSelectionBrushImage("OgreTrayImages","GenericBrush");
#else
        lbi->setTextColours(CEGUI::Colour(0.0f, 0.0f, 0.0f));
#endif
        inventory->addItem(lbi);
        inventory->setItemSelectState(lbi, false);
        inventory->ensureItemIsVisible(lbi);
    } // for

    inventory->setMultiselectEnabled(false);
} // addItem

void PlayerInventoryPanel::loadPlayer(Player *player) {
    inventoryItems.clear();
    inventory->resetList();

    if (player != NULL) {
        for (Item *item : player->getInventory()->getItems()) {
            addItem(item);
        } // for
    } // else
} // loadPlayer

bool PlayerInventoryPanel::inventorySelectionChanged(const CEGUI::EventArgs &e) {
    using namespace CEGUI;

    equipItemButton->setText("Equip");
    equipItemButton->setEnabled(false);
    for (int i = 0, len = inventory->getItemCount(); i < len; i++) {
        ListboxTextItem *lbti = (ListboxTextItem*)inventory->getListboxItemFromIndex(i);

        if (lbti != NULL) {
            if (lbti->isSelected()) {
                if (((Item*)inventory->getFirstSelectedItem()->getUserData())->isEquippable()) {
                    equipItemButton->setEnabled(true);

                    if (((Equippable*)inventory->getFirstSelectedItem()->getUserData())->isEquippable()) {
                        equipItemButton->setText("Unequip");
                    } // if
                } // if
#if USE_OGRE_LEGACY
                lbti->setTextColours(colour(1.0f, 1.0f, 0.0f));
#else
                lbti->setTextColours(Colour(1.0f, 1.0f, 0.0f));
#endif
            } // if
            else {
#if USE_OGRE_LEGACY
                lbti->setTextColours(colour(0.0f, 0.0f, 0.0f));
#else
                lbti->setTextColours(Colour(0.0f, 0.0f, 0.0f));
#endif
            } // else
        } // if
    } // for

    inventory->invalidate(true);

    return false;
} // inventorySelectionChanged

bool PlayerInventoryPanel::toggleInventory(const CEGUI::EventArgs &e) {
    using namespace CEGUI;
    visible = !visible;

    if (visible) {
#if USE_OGRE_LEGACY
        parent->addChildWindow(inventory);
        parent->addChildWindow(equipItemButton);
        parent->addChildWindow(examineItemButton);
#else
        parent->addChild(inventory);
        parent->addChild(equipItemButton);
        parent->addChild(examineItemButton);
#endif

        inventoryLabel->setPosition(UVector2(UDim(1.0f, -210.0f), UDim(1.0f, -335.0f)));
        inventoryLabel->setText("Collapse Inventory");
    } // if 
    else {
#if USE_OGRE_LEGACY
        parent->removeChildWindow(inventory);
        parent->removeChildWindow(equipItemButton);
        parent->removeChildWindow(examineItemButton);
#else
        parent->removeChild(inventory);
        parent->removeChild(equipItemButton);
        parent->removeChild(examineItemButton);
#endif
        inventoryLabel->setPosition(UVector2(UDim(1.0f, -210.0f), UDim(1.0f, -45.0f)));
        inventoryLabel->setText("Expand Inventory");
    } // else

    return true;
} // equipItemEvent

bool PlayerInventoryPanel::equipItemEvent(const CEGUI::EventArgs &e) {
    Equippable *item;

    if (((Item*)inventory->getFirstSelectedItem()->getUserData())->isEquippable()) {
        item = (Equippable*)inventory->getFirstSelectedItem()->getUserData();
        World::getInstance().getCurrentPlayer()->equipItem(item);
    } // if

    return true;
} // equipItemEvent

bool PlayerInventoryPanel::examineItemEvent(const CEGUI::EventArgs &e) {
    using namespace StringHelper;
    std::string str = "";

    if (inventory->getFirstSelectedItem() != NULL) {
        str = ((Item*)inventory->getFirstSelectedItem()->getUserData())->getDescription();
        GUIManager::getInstance().inGameMenu->appendText(str);
    }

    return true;
} // examineItemButton
