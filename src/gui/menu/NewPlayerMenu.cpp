/**
 * Included files
 */
#include <thread>
#include "NewPlayerMenu.h"
#include "MainMenu.h"
#include "LoadingMenu.h"
#include "ingamemenu/InGameMenu.h"
#include "src/gui/GUIManager.h"
#include "src/world/World.h"
#include "src/entities/player/Player.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"

NewPlayerMenu::NewPlayerMenu() :
    windowManager(CEGUI::WindowManager::getSingleton()) {

    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor

void NewPlayerMenu::createWidgets() { 
    using namespace CEGUI;
    
    titleLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/titleLabel");
    textLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/textLabel");
    playerNameTextField = windowManager.createWindow("OgreTray/Editbox", "NewPlayerMenu/playerNameTextField");
    backButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "NewPlayerMenu/backButton"));
    startGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "NewPlayerMenu/startGameButton"));
#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background", "main_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "NewPlayerMenu/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background image:full_image");
#endif

#if USE_OGRE_LEGACY
    titleLabel->setSize(UVector2(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    textLabel->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    playerNameTextField->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    backButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    startGameButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
#else
    titleLabel->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    textLabel->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    playerNameTextField->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    backButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    startGameButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
#endif

    titleLabel->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -70.0f)));
    titleLabel->setText("Create a New Player");
    
    textLabel->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -20.0f)));
    textLabel->setText("Player Name");

    playerNameTextField->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, -20.0f)));
    playerNameTextField->setText("player1");

    backButton->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, 20.0f)));
    backButton->setText("Back");

    startGameButton->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, 20.0f)));
    startGameButton->setText("Start Game");
} // createWidgets

void NewPlayerMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "NewPlayerMenu/root");
   
#if USE_OGRE_LEGACY
    mRoot->addChildWindow(backgroundWindow); 
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(textLabel);
    mRoot->addChildWindow(playerNameTextField);
    mRoot->addChildWindow(backButton);
    mRoot->addChildWindow(startGameButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(textLabel);
    mRoot->addChild(playerNameTextField);
    mRoot->addChild(backButton);
    mRoot->addChild(startGameButton);
#endif

} // createRootWindow

void NewPlayerMenu::registerEvents() {
    using namespace CEGUI;

    backButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&NewPlayerMenu::backEvent, this));
    startGameButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&NewPlayerMenu::startGameEvent, this));
} // registerEvents

void NewPlayerMenu::show() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif

} // show

void NewPlayerMenu::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hide

bool NewPlayerMenu::backEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().mainMenu->show();
    return false;
} // backEvent

bool NewPlayerMenu::startGameEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().loadingMenu->show();
    GUIManager::getInstance().loadingMenu->setText("Loading game ...");

#if USE_OGRE_LEGACY
    runThread();
#else
    mThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&NewPlayerMenu::runThread, this)));
#endif

    return false;
} // startGameEvent

void NewPlayerMenu::runThread() {
    Player *player = new Player(1, playerNameTextField->getText().c_str());

	World::getInstance().loadZone();
    World::getInstance().setCurrentPlayer(player);
	World::getInstance().spawnCurrentPlayer();
    GUIManager::getInstance().inGameMenu->loadPlayer(player);
} // runThread
