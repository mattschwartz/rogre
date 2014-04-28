/**
 * Included files
 */
#include "NewPlayerMenu.h"
#include "MainMenu.h"
#include "LoadingMenu.h"
#include "src/gui/GUIManager.h"
#include "src/world/World.h"
#include "src/entities/player/Player.h"

NewPlayerMenu::NewPlayerMenu() :
    windowManager(CEGUI::WindowManager::getSingleton()) {

    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor

void NewPlayerMenu::createWidgets() { 
    using namespace CEGUI;

    textLabel = windowManager.createWindow("OgreTray/Label", "NewPlayerMenu/textLabel");
    playerNameTextField = windowManager.createWindow("OgreTray/Editbox", "NewPlayerMenu/playerNameTextField");
    backButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "NewPlayerMenu/backButton"));
    startGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "NewPlayerMenu/startGameButton"));

    textLabel->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    textLabel->setPosition(UVector2(UDim(0.0f, 0.0f), UDim(0.05f, 0.0f)));
    textLabel->setText("Player Name");

    playerNameTextField->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    playerNameTextField->setPosition(UVector2(UDim(0.0f, 150.0f), UDim(0.05f, 0.0f)));
    playerNameTextField->setText("player1");

    backButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    backButton->setPosition(UVector2(UDim(0.0f, 0.0f), UDim(1.0f, -40.0f)));
    backButton->setText("Back");

    startGameButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    startGameButton->setPosition(UVector2(UDim(1.0f, -150.0f), UDim(1.0f, -40.0f)));
    startGameButton->setText("Start Game");
} // createWidgets

void NewPlayerMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "NewPlayerMenu/root");
    
    mRoot->addChild(textLabel);
    mRoot->addChild(playerNameTextField);
    mRoot->addChild(backButton);
    mRoot->addChild(startGameButton);
} // createRootWindow

void NewPlayerMenu::registerEvents() {
    using namespace CEGUI;

    backButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&NewPlayerMenu::backEvent, this));
    startGameButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&NewPlayerMenu::startGameEvent, this));
} // registerEvents

void NewPlayerMenu::show() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
} // show

void NewPlayerMenu::hide() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
} // hide

bool NewPlayerMenu::backEvent(const CEGUI::EventArgs &e) {
    GUIManager::getInstance().mainMenu->show();
    return false;
} // backEvent

bool NewPlayerMenu::startGameEvent(const CEGUI::EventArgs &e) {
    GUIManager::getInstance().loadingMenu->show();
    World::getInstance().setCurrentPlayer(new Player(1, playerNameTextField->getText().c_str()));
	World::getInstance().spawnCurrentPlayer(0, 0, 0);

	World::getInstance().loadZone();
    return false;
} // startGameEvent
