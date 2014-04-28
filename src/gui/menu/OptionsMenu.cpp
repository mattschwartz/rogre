/**
 * Included files
 */
#include "OptionsMenu.h"
#include "src/input/InputManager.h"
#include "src/gui/GUIManager.h"
#include "MainMenu.h"
#include "src/world/World.h"

OptionsMenu::OptionsMenu()
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    visible = false;
    createButtons();
    createRootWindow();
    registerEvents();
} // constructor

void OptionsMenu::createButtons() {
    using namespace CEGUI;
    
    saveAndResumeButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/saveGameButton"));
    quitToMenuButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitToMenuButton"));
    quitGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitGameButton"));
    
    saveAndResumeButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    saveAndResumeButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, -40.0f)));
    saveAndResumeButton->setText("Save Game & Continue");
    
    quitToMenuButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitToMenuButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, 0.0f)));
    quitToMenuButton->setText("Return to Main Menu");
    
    quitGameButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitGameButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, +40.0f)));
    quitGameButton->setText("Exit Game");
} // createButtons

void OptionsMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "MainMenu/root");

    mRoot->addChild(saveAndResumeButton);
    mRoot->addChild(quitToMenuButton);
    mRoot->addChild(quitGameButton);
} // createRootWindow

void OptionsMenu::registerEvents() {
    using namespace CEGUI;
    
    saveAndResumeButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::saveAndResumeEvent, this));
    quitToMenuButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::quitToMenuEvent, this));
    quitGameButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::quitGameEvent, this));
} // registerEvents

void OptionsMenu::show() {
    visible = true;
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
    World::getInstance().pauseGame();
} // show

void OptionsMenu::hide() {
    visible = false;
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
    World::getInstance().resumeGame();
} // hide

void OptionsMenu::toggle() {
    visible = !visible;

    if (visible) {
        show();
    } // if
    else {
        hide();
    } // else
} // toggle

bool OptionsMenu::saveAndResumeEvent(const CEGUI::EventArgs &e) {
    hide();
    return false;
} // saveAndResumeEvent

bool OptionsMenu::quitToMenuEvent(const CEGUI::EventArgs &e) {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
    GUIManager::getInstance().mainMenu->show();
    World::getInstance().playerQuit();
    return false;
} // quitToMenuEvent

bool OptionsMenu::quitGameEvent(const CEGUI::EventArgs &e) {
    InputManager::getInstance().shutDown();
    return false;
} // quitEvent
