/**
 * Included files
 */
#include "OptionsMenu.h"
#include "src/input/InputManager.h"
#include "src/gui/GUIManager.h"
#include "MainMenu.h"
#include "src/world/World.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "ingamemenu/InGameMenu.h"

OptionsMenu::OptionsMenu()
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    visible = false;
    createButtons();
    createRootWindow();
    registerEvents();
} // constructor

void OptionsMenu::createButtons() {
    using namespace CEGUI;
    
    titleLabel = windowManager.createWindow("OgreTray/Title", "OptionsMenu/titleLabel");
    gameSoundsLabel = windowManager.createWindow("OgreTray/Title", "OptionsMenu/gameSoundsLabel");
    menuSoundsLabel = windowManager.createWindow("OgreTray/Title", "OptionsMenu/menuSoundsLabel");

    gameSoundsEnabledCheckbox = static_cast<ToggleButton*>(
        windowManager.createWindow("OgreTray/Checkbox", "OptionsMenu/gameSoundsEnabledCheckbox"));
    menuSoundsEnabledCheckbox = static_cast<ToggleButton*>(
        windowManager.createWindow("OgreTray/Checkbox", "OptionsMenu/menuSoundsEnabledCheckbox"));
    
    saveAndResumeButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/saveGameButton"));
    quitToMenuButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitToMenuButton"));
    quitGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitGameButton"));

    titleLabel->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    titleLabel->setPosition(UVector2(UDim(0.5f, -125.0f), UDim(0.5f, -170.0f)));
    titleLabel->setText("Game Paused");

    gameSoundsLabel->setSize(USize(UDim(0.0f, 210.0f), UDim(0.0f, 40.0f)));
    gameSoundsLabel->setPosition(UVector2(UDim(0.5f, -125.0f), UDim(0.5f, -120.0f)));
    gameSoundsLabel->setText("Enable Game Sounds");
    gameSoundsEnabledCheckbox->setSize(USize(UDim(0.0f, 40.0f), UDim(0.0f, 40.0f)));
    gameSoundsEnabledCheckbox->setPosition(UVector2(UDim(0.5f, 85.0f), UDim(0.5f, -120.0f)));
    gameSoundsEnabledCheckbox->setSelected(true);

    menuSoundsLabel->setSize(USize(UDim(0.0f, 210.0f), UDim(0.0f, 40.0f)));
    menuSoundsLabel->setPosition(UVector2(UDim(0.5f, -125.0f), UDim(0.5f, -80.0f)));
    menuSoundsLabel->setText("Enable Menu Sounds");
    menuSoundsEnabledCheckbox->setSize(USize(UDim(0.0f, 40.0f), UDim(0.0f, 40.0f)));
    menuSoundsEnabledCheckbox->setPosition(UVector2(UDim(0.5f, 85.0f), UDim(0.5f, -80.0f)));
    menuSoundsEnabledCheckbox->setSelected(true);
    
    saveAndResumeButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    saveAndResumeButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, -40.0f)));
    saveAndResumeButton->setText("Save Game & Continue");
    
    quitToMenuButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitToMenuButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, 0.0f)));
    quitToMenuButton->setText("Return to Main Menu");
    
    quitGameButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitGameButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, 40.0f)));
    quitGameButton->setText("Exit Game");
} // createButtons

void OptionsMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "OptionsMenu/root");

    mRoot->addChild(titleLabel);
    mRoot->addChild(gameSoundsLabel);
    mRoot->addChild(menuSoundsLabel);
    mRoot->addChild(gameSoundsEnabledCheckbox);
    mRoot->addChild(menuSoundsEnabledCheckbox);
    mRoot->addChild(saveAndResumeButton);
    mRoot->addChild(quitToMenuButton);
    mRoot->addChild(quitGameButton);
} // createRootWindow

void OptionsMenu::registerEvents() {
    using namespace CEGUI;
    
    gameSoundsEnabledCheckbox->subscribeEvent(ToggleButton::EventSelectStateChanged, 
        Event::Subscriber(&OptionsMenu::toggleGameSounds, this));
    menuSoundsEnabledCheckbox->subscribeEvent(ToggleButton::EventSelectStateChanged, 
        Event::Subscriber(&OptionsMenu::toggleMenuSounds, this));
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
    gameSoundsEnabledCheckbox->setSelected(SoundManager::getInstance().isGameSoundEnabled());
    menuSoundsEnabledCheckbox->setSelected(SoundManager::getInstance().isMenuSoundEnabled());
} // show

void OptionsMenu::hide() {
    visible = false;
    GUIManager::getInstance().inGameMenu->show();
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

bool OptionsMenu::toggleGameSounds(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().setGameSoundEnabled(gameSoundsEnabledCheckbox->isSelected());
    return true;
} // toggleGameSounds

bool OptionsMenu::toggleMenuSounds(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().setMenuSoundEnabled(menuSoundsEnabledCheckbox->isSelected());
    return true;
} // toggleMenuSounds

bool OptionsMenu::saveAndResumeEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    hide();
    return true;
} // saveAndResumeEvent

bool OptionsMenu::quitToMenuEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
    GUIManager::getInstance().mainMenu->show();
    World::getInstance().playerQuit();
    return true;
} // quitToMenuEvent

bool OptionsMenu::quitGameEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    InputManager::getInstance().shutDown();
    return true;
} // quitEvent
