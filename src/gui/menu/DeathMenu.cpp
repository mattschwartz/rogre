/**
 * Included files
 */
#include "DeathMenu.h"
#include "MainMenu.h"
#include "src/input/InputManager.h"
#include "src/gui/GUIManager.h"
#include "src/world/World.h"
#include "src/entities/player/Player.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"

DeathMenu::DeathMenu() 
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor

void DeathMenu::createWidgets() {
    using namespace CEGUI;
    
    titleLabel = windowManager.createWindow("OgreTray/Title", "DeathMenu/titleLabel");
    textLabel = windowManager.createWindow("OgreTray/Title", "DeathMenu/textLabel");
    scoreTextField = windowManager.createWindow("OgreTray/Editbox", "DeathMenu/scoreTextField");
    quitToMenuButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "DeathMenu/quitToMenuButton"));
    quitGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "DeathMenu/quitGameButton"));
    
    titleLabel->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    titleLabel->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -70.0f)));
    titleLabel->setText("You Have Died.");
    
    textLabel->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    textLabel->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -20.0f)));
    textLabel->setText("Final Score: ");
    
    scoreTextField->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    scoreTextField->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, -20.0f)));
    //scoreTextField->setText(World::getInstance().getCurrentPlayer()->getScore());
    scoreTextField->setText("45,844");
    scoreTextField->setEnabled(false);
    
    quitToMenuButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitToMenuButton->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, 20.0f)));
    quitToMenuButton->setText("Main Menu");

    quitGameButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitGameButton->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, 20.0f)));
    quitGameButton->setText("Quit");
} // createWidgets

void DeathMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "DeathMenu/root");
    mRoot->addChild(titleLabel);
    mRoot->addChild(textLabel);
    mRoot->addChild(scoreTextField);
    mRoot->addChild(quitToMenuButton);
    mRoot->addChild(quitGameButton);
} // createRootWindow

void DeathMenu::registerEvents() {
    using namespace CEGUI;
    
    quitToMenuButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&DeathMenu::quitToMenuEvent, this));
    quitGameButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&DeathMenu::quitGameEvent, this));
} // registerEvents

void DeathMenu::show() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
} // show

void DeathMenu::hide() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
} // hide

bool DeathMenu::quitToMenuEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
    GUIManager::getInstance().mainMenu->show();
    World::getInstance().playerQuit();
    return false;
} // quitToMenuEvent

bool DeathMenu::quitGameEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    InputManager::getInstance().shutDown();
    return false;
} // quitEvent
