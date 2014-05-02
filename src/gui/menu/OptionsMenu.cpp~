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
    saveAndResumeButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/saveGameButton"));
    quitToMenuButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitToMenuButton"));
    quitGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "OptionsMenu/quitGameButton"));
#if USE_OGRE_LEGACY
    gameSoundsEnabledCheckbox = static_cast<Checkbox*>(
        windowManager.createWindow("OgreTray/Checkbox", "OptionsMenu/gameSoundsEnabledCheckbox"));
    menuSoundsEnabledCheckbox = static_cast<Checkbox*>(
        windowManager.createWindow("OgreTray/Checkbox", "OptionsMenu/menuSoundsEnabledCheckbox"));
    titleLabel->setSize(UVector2(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    gameSoundsLabel->setSize(UVector2(UDim(0.0f, 210.0f), UDim(0.0f, 40.0f)));
    menuSoundsLabel->setSize(UVector2(UDim(0.0f, 210.0f), UDim(0.0f, 40.0f)));
    saveAndResumeButton->setSize(UVector2(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitToMenuButton->setSize(UVector2(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitGameButton->setSize(UVector2(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    gameSoundsEnabledCheckbox->setSize(UVector2(UDim(0.0f, 40.0f), UDim(0.0f, 40.0f)));
    menuSoundsEnabledCheckbox->setSize(UVector2(UDim(0.0f, 40.0f), UDim(0.0f, 40.0f)));
#else
    gameSoundsEnabledCheckbox = static_cast<ToggleButton*>(
        windowManager.createWindow("OgreTray/Checkbox", "OptionsMenu/gameSoundsEnabledCheckbox"));
    menuSoundsEnabledCheckbox = static_cast<ToggleButton*>(
       windowManager.createWindow("OgreTray/Checkbox", "OptionsMenu/menuSoundsEnabledCheckbox"));
    titleLabel->setSize(UV(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    gameSoundsLabel->setSize(USize(UDim(0.0f, 210.0f), UDim(0.0f, 40.0f)));
    menuSoundsLabel->setSize(USize(UDim(0.0f, 210.0f), UDim(0.0f, 40.0f)));
    saveAndResumeButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitToMenuButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    quitGameButton->setSize(USize(UDim(0.0f, 250.0f), UDim(0.0f, 40.0f)));
    gameSoundsEnabledCheckbox->setSize(USize(UDim(0.0f, 40.0f), UDim(0.0f, 40.0f)));
    menuSoundsEnabledCheckbox->setSize(USize(UDim(0.0f, 40.0f), UDim(0.0f, 40.0f)));
#endif

    
   


    titleLabel->setPosition(UVector2(UDim(0.5f, -125.0f), UDim(0.5f, -170.0f)));
    titleLabel->setText("Game Paused");


    gameSoundsLabel->setPosition(UVector2(UDim(0.5f, -125.0f), UDim(0.5f, -120.0f)));
    gameSoundsLabel->setText("Enable Game Sounds");

    gameSoundsEnabledCheckbox->setPosition(UVector2(UDim(0.5f, 85.0f), UDim(0.5f, -120.0f)));
    gameSoundsEnabledCheckbox->setSelected(true);


    menuSoundsLabel->setPosition(UVector2(UDim(0.5f, -125.0f), UDim(0.5f, -80.0f)));
    menuSoundsLabel->setText("Enable Menu Sounds");

    menuSoundsEnabledCheckbox->setPosition(UVector2(UDim(0.5f, 85.0f), UDim(0.5f, -80.0f)));
    menuSoundsEnabledCheckbox->setSelected(true);
    

    saveAndResumeButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, -40.0f)));
    saveAndResumeButton->setText("Save Game & Continue");
    

    quitToMenuButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, 0.0f)));
    quitToMenuButton->setText("Return to Main Menu");
    

    quitGameButton->setPosition(UVector2(UDim(0.5f, -(250.0f / 2.0f)), UDim(0.5f, 40.0f)));
    quitGameButton->setText("Exit Game");
} // createButtons

void OptionsMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "OptionsMenu/root");
#if USE_OGRE_LEGACY
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(gameSoundsLabel);
    mRoot->addChildWindow(menuSoundsLabel);
    mRoot->addChildWindow(gameSoundsEnabledCheckbox);
    mRoot->addChildWindow(menuSoundsEnabledCheckbox);
    mRoot->addChildWindow(saveAndResumeButton);
    mRoot->addChildWindow(quitToMenuButton);
    mRoot->addChildWindow(quitGameButton);

#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(gameSoundsLabel);
    mRoot->addChild(menuSoundsLabel);
    mRoot->addChild(gameSoundsEnabledCheckbox);
    mRoot->addChild(menuSoundsEnabledCheckbox);
    mRoot->addChild(saveAndResumeButton);
    mRoot->addChild(quitToMenuButton);
    mRoot->addChild(quitGameButton);
#endif
} // createRootWindow

void OptionsMenu::registerEvents() {
    using namespace CEGUI;
    

#if USE_OGRE_LEGACY
    gameSoundsEnabledCheckbox->subscribeEvent(Checkbox::EventCheckStateChanged, 
        Event::Subscriber(&OptionsMenu::toggleGameSounds, this));
    menuSoundsEnabledCheckbox->subscribeEvent(Checkbox::EventCheckStateChanged, 
        Event::Subscriber(&OptionsMenu::toggleMenuSounds, this));
#else
    gameSoundsEnabledCheckbox->subscribeEvent(ToggleButton::EventSelectStateChanged, 
        Event::Subscriber(&OptionsMenu::toggleGameSounds, this));
    menuSoundsEnabledCheckbox->subscribeEvent(ToggleButton::EventSelectStateChanged, 
        Event::Subscriber(&OptionsMenu::toggleMenuSounds, this));
#endif
    saveAndResumeButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::saveAndResumeEvent, this));
    quitToMenuButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::quitToMenuEvent, this));
    quitGameButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&OptionsMenu::quitGameEvent, this));
} // registerEvents

void OptionsMenu::show() {
    visible = true;
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif
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
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
    GUIManager::getInstance().mainMenu->show();
    World::getInstance().playerQuit();
    return true;
} // quitToMenuEvent

bool OptionsMenu::quitGameEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    InputManager::getInstance().shutDown();
    return true;
} // quitEvent
