/**
 * Included files
 */
#include "OptionsMenu.h"
#include "src/input/InputManager.h"
#include "src/gui/GUIManager.h"
#include "MainMenu.h"

OptionsMenu::OptionsMenu()
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    visible = false;
    createButtons();
    createRootWindow();
    registerEvents();
} // constructor

void OptionsMenu::createButtons() {
    using namespace CEGUI;
    
    saveButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/saveGameButton"));
    quitToMenuButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitToMenuButton"));
    quitGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitGameButton"));
    
    saveButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    saveButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, -40.0f)));
    saveButton->setText("Save Game");
    
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

    mRoot->addChild(saveButton);
    mRoot->addChild(quitToMenuButton);
    mRoot->addChild(quitGameButton);
} // createRootWindow

void OptionsMenu::registerEvents() {
    using namespace CEGUI;
    
    saveButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::saveGameEvent, this));
    quitToMenuButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::quitToMenuEvent, this));
    quitGameButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::quitGameEvent, this));
} // registerEvents

void OptionsMenu::show() {
    visible = true;
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
} // show

void OptionsMenu::hide() {
    visible = false;
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
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

bool OptionsMenu::saveGameEvent(const CEGUI::EventArgs &e) {
    return false;
} // saveGameEvent

bool OptionsMenu::quitToMenuEvent(const CEGUI::EventArgs &e) {
    hide();
    GUIManager::getInstance().mainMenu->show();
    return false;
} // quitToMenuEvent

bool OptionsMenu::quitGameEvent(const CEGUI::EventArgs &e) {
    InputManager::getInstance().shutDown();
    return false;
} // quitEvent
