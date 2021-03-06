/**
 * Included files
 */
#include "MainMenu.h"
#include "NewPlayerMenu.h"
#include "LoadingMenu.h"
#include "CreditPage.h"
#include "DeathMenu.h"
#include "LoadPlayerMenu.h"
#include "src/entities/player/Player.h"
#include "src/input/InputManager.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/HiScoresMenu.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "src/utility/GUIHelper.h"

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
    creditButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/creditButton"));
#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background", "main_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "MainMenu/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background image:full_image");
#endif
    
    titleLabel->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    titleLabel->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, -110.0f)));
    titleLabel->setText("Main Menu");
    titleLabel->setAlwaysOnTop(true);
    
    newPlayerButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    newPlayerButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, -60.0f)));
    newPlayerButton->setText("New Player");
    newPlayerButton->setAlwaysOnTop(true);
    
    loadPlayerButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    loadPlayerButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, -20.0f)));
    loadPlayerButton->setText("Load Player");
    loadPlayerButton->setAlwaysOnTop(true);
    
    hiScoresButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    hiScoresButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, 20.0f)));
    hiScoresButton->setText("Graveyard");
    hiScoresButton->setAlwaysOnTop(true);
    
    creditButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    creditButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, 60.0f)));
    creditButton->setText("Credits");
    creditButton->setAlwaysOnTop(true);
    
    quitButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    quitButton->setPosition(UVector2(UDim(0.5f, -(150.0f / 2)), UDim(0.5f, 100.0f)));
    quitButton->setText("Quit");
    quitButton->setAlwaysOnTop(true);
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
    mRoot->addChildWindow(creditButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(newPlayerButton);
    mRoot->addChild(loadPlayerButton);
    mRoot->addChild(hiScoresButton);
    mRoot->addChild(quitButton);
    mRoot->addChild(creditButton);
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
    creditButton->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&MainMenu::creditEvent,this));
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

bool MainMenu::creditEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().creditPage->show();
	return false;
} // quitEvent
