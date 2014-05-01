/**
 * Included files
 */
#include "InGameMenu.h"
#include "PlayerAttributesPanel.h"
#include "PlayerInventoryPanel.h"
#include "src/entities/player/Player.h"

InGameMenu::InGameMenu() : 
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
} // constructor

void InGameMenu::createWidgets() {
    using namespace CEGUI;

    playerAttributes = new PlayerAttributesPanel();
    playerInventory = new PlayerInventoryPanel();

    healthBar = static_cast<ProgressBar*>(
        windowManager.createWindow("OgreTray/ProgressBar", "InGameMenu/healthBar"));
    scoreLabel = windowManager.createWindow("OgreTray/Title", "InGameMenu/scoreLabel");

    healthBar->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    healthBar->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.0f, 5.0f)));
    healthBar->setProgress(100.0f);
    healthBar->setText("Health");

    scoreLabel->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    scoreLabel->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.0f, 45.0f)));
    scoreLabel->setText("Score: 25,918");
} // createWidgets

void InGameMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "InGameMenu/root");
    mRoot->addChild(healthBar);
    mRoot->addChild(scoreLabel);
    playerInventory->addPanelTo(mRoot);
    playerAttributes->addPanelTo(mRoot);
} // createRootWindow

void InGameMenu::updateAttributes(Player *player) {
    playerAttributes->updateAttributes(player);
} // update

void InGameMenu::show() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
} // show

void InGameMenu::hide() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
} // hide
