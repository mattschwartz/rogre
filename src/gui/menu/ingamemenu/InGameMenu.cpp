/**
 * Included files
 */
#include "InGameMenu.h"
#include "PlayerAttributesPanel.h"
#include "PlayerInventoryPanel.h"
#include "InfoLogPanel.h"
#include "src/entities/player/Player.h"
#include "src/items/Item.h"
#include "src/utility/StringHelper.h"
#include "src/entities/player/Inventory.h"

InGameMenu::InGameMenu() : 
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
} // constructor

void InGameMenu::createWidgets() {
    using namespace CEGUI;

    playerAttributes = new PlayerAttributesPanel();
    playerInventory = new PlayerInventoryPanel();
    infoLog = new InfoLogPanel();

    healthBar = static_cast<ProgressBar*>(
        windowManager.createWindow("OgreTray/ProgressBar", "InGameMenu/healthBar"));
    scoreLabel = windowManager.createWindow("OgreTray/Title", "InGameMenu/scoreLabel");
#if USE_OGRE_LEGACY
    healthBar->setSize(UVector2(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    scoreLabel->setSize(UVector2(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
#else
    healthBar->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    scoreLabel->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
#endif

    healthBar->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.0f, 5.0f)));
    healthBar->setProgress(100.0f);
    healthBar->setText("Health");

    scoreLabel->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.0f, 45.0f)));
    scoreLabel->setText("Score: 0");
} // createWidgets

void InGameMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "InGameMenu/root");

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(healthBar);
    mRoot->addChildWindow(scoreLabel);
#else
    mRoot->addChild(healthBar);
    mRoot->addChild(scoreLabel);
#endif

    playerAttributes->addPanelTo(mRoot);
    playerInventory->addPanelTo(mRoot);
    infoLog->addPanelTo(mRoot);
} // createRootWindow

void InGameMenu::appendText(std::string text) {
    infoLog->append(text);
} // appendText

void InGameMenu::appendLine(std::string text) {
    infoLog->append(text);
} // appendLine

void InGameMenu::updateAttributes(Player *player) {
    healthBar->setProgress(player->getCurrentHitpoints() / player->getAttribute(hitpoints));
    playerAttributes->updateAttributes(player);
} // update

void InGameMenu::addItemToInventory(Player *player, Item *item) {
    player->getInventory()->addItem(item);
    playerInventory->addItem(item);
} // addItemToInventory

void InGameMenu::updatePlayerScore(Player *player) {
    using namespace StringHelper;

    scoreLabel->setText(concat<int>("Score: ", player->getScore()));
} // updatePlayerScore

void InGameMenu::show() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif
} // show

void InGameMenu::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hide

void InGameMenu::loadPlayer(Player *player) {
    playerAttributes->updateAttributes(player);
    playerInventory->loadPlayer(player);
    infoLog->loadPlayer(player);
} // loadPlayer
