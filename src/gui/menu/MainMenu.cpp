/**
 * Included files
 */
#include "MainMenu.h"
#include "NewPlayerMenu.h"
#include "LoadingMenu.h"
#include "DeathMenu.h"
#include "LoadPlayerMenu.h"
#include "src/entities/player/Player.h"
#include "src/input/InputManager.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/HiScoresMenu.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"

MainMenu::MainMenu() 
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    createButtons();
    createRootWindow();
    registerEvents();
} // constructor

void MainMenu::createButtons() {
    using namespace CEGUI;

    titleLabel = windowManager.createWindow("OgreTray/Title", "MainMenu/titleLabel");

    newPlayerButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/newPlayerButton"));
    loadPlayerButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/loadPlayerButton"));
    hiScoresButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/hiScoresButton"));
    quitButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/quitButton"));
#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background", "main_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "MainMenu/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background image:full_image");
#endif

#if USE_OGRE_LEGACY
    titleLabel->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    newPlayerButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    loadPlayerButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    hiScoresButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));

    titleLabel->setAlwaysOnTop(true);
    newPlayerButton->setAlwaysOnTop(true);
    loadPlayerButton->setAlwaysOnTop(true);
    hiScoresButton->setAlwaysOnTop(true);
    quitButton->setAlwaysOnTop(true);
#else
    titleLabel->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    newPlayerButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    loadPlayerButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    hiScoresButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
#endif
    
    titleLabel->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, -110.0f)));
    titleLabel->setText("Main Menu");

    newPlayerButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, -60.0f)));
    newPlayerButton->setText("New Player");
    
    loadPlayerButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, -20.0f)));
    loadPlayerButton->setText("Load Player");
    
    hiScoresButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, 20.0f)));
    hiScoresButton->setText("Graveyard");

    quitButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, 60.0f)));
    quitButton->setText("Quit");
} // createButtons

void MainMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "MainMenu/root");

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(backgroundWindow);
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(newPlayerButton);
    mRoot->addChildWindow(loadPlayerButton);
    mRoot->addChildWindow(hiScoresButton);
    mRoot->addChildWindow(quitButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(newPlayerButton);
    mRoot->addChild(loadPlayerButton);
    mRoot->addChild(hiScoresButton);
    mRoot->addChild(quitButton);
#endif
} // createRootWindow

void MainMenu::registerEvents() {
    using namespace CEGUI;
    
    newPlayerButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&MainMenu::newPlayerEvent, this));
    loadPlayerButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&MainMenu::loadPlayerEvent, this));
    hiScoresButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&MainMenu::hiScoresEvent, this));
    quitButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&MainMenu::quitEvent, this));
} // registerEvents

void MainMenu::show() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif
} // show

void MainMenu::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hide

bool MainMenu::newPlayerEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().newPlayerMenu->show();
	return false;
} // newPlayerEvent

bool MainMenu::loadPlayerEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().loadPlayerMenu->show();
	return false;
} // loadPlayerEvent

bool MainMenu::hiScoresEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().hiScoresMenu->show();
	return false;
} // hiScoresEvent

bool MainMenu::quitEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    InputManager::getInstance().shutDown();
	return false;
} // quitEvent
