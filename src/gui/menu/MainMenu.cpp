/**
 * Included files
 */
#include "MainMenu.h"
#include "NewPlayerMenu.h"
#include "LoadingMenu.h"
#include "src/entities/player/Player.h"
#include "src/input/InputManager.h"
#include "src/gui/GUIManager.h"

MainMenu::MainMenu() 
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    createButtons();
    createRootWindow();
    registerEvents();
} // constructor

void MainMenu::createButtons() {
    using namespace CEGUI;

    newPlayerButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/newPlayerButton"));
    loadPlayerButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/loadPlayerButton"));
    hiScoresButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/hiScoresButton"));
    quitButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "MainMenu/quitButton"));

#if USE_OGRE_LEGACY
    newPlayerButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    loadPlayerButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    hiScoresButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
#else
    newPlayerButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    loadPlayerButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    hiScoresButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));

    loadPlayerButton->setEnabled(false);
    hiScoresButton->setEnabled(false);
#endif
    
    newPlayerButton->setPosition(UVector2(UDim(1.0f, -150.0f), UDim(1.0f, -160.0f)));
    newPlayerButton->setText("New Player");
    
    loadPlayerButton->setPosition(UVector2(UDim(1.0f, -150.0f), UDim(1.0f, -120.0f)));
    loadPlayerButton->setText("Load Player");
    
    hiScoresButton->setPosition(UVector2(UDim(1.0f, -150.0f), UDim(1.0f, -80.0f)));
    hiScoresButton->setText("Hi Scores");

    quitButton->setPosition(UVector2(UDim(1.0f, -150.0f), UDim(1.0f, -40.0f)));
    quitButton->setText("Quit");
} // createButtons

void MainMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "MainMenu/root");

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(newPlayerButton);
    mRoot->addChildWindow(loadPlayerButton);
    mRoot->addChildWindow(hiScoresButton);
    mRoot->addChildWindow(quitButton);
#else
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
    GUIManager::getInstance().newPlayerMenu->show();
	return false;
} // newPlayerEvent

bool MainMenu::loadPlayerEvent(const CEGUI::EventArgs &e) {
	return false;
} // loadPlayerEvent

bool MainMenu::hiScoresEvent(const CEGUI::EventArgs &e) {
	return false;
} // hiScoresEvent

bool MainMenu::quitEvent(const CEGUI::EventArgs &e) {
    InputManager::getInstance().shutDown();
	return false;
} // quitEvent
