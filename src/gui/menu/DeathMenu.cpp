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
#include "src/utility/StringHelper.h"


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
#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background", "death_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "DeathMenu/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background image:full_image");
#endif
    
#if USE_OGRE_LEGACY    
    titleLabel->setSize(UVector2(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    textLabel->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    scoreTextField->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitToMenuButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitGameButton->setSize(UVector2(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
#else
    titleLabel->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    textLabel->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    scoreTextField->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitToMenuButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
    quitGameButton->setSize(USize(UDim(0.0f, 150.0f), UDim(0.0f, 40.0f)));
#endif

    titleLabel->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -70.0f)));
    titleLabel->setText("You Have Died.");

    textLabel->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -20.0f)));
    textLabel->setText("Final Score: ");

    scoreTextField->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, -20.0f)));
    scoreTextField->setText("0");
    scoreTextField->setEnabled(false);

    quitToMenuButton->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, 20.0f)));
    quitToMenuButton->setText("Main Menu");

    quitGameButton->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, 20.0f)));
    quitGameButton->setText("Quit");
} // createWidgets

void DeathMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "DeathMenu/root");

#if USE_OGRE_LEGACY  
    mRoot->addChildWindow(backgroundWindow); 
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(textLabel);
    mRoot->addChildWindow(scoreTextField);
    mRoot->addChildWindow(quitToMenuButton);
    mRoot->addChildWindow(quitGameButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(textLabel);
    mRoot->addChild(scoreTextField);
    mRoot->addChild(quitToMenuButton);
    mRoot->addChild(quitGameButton);
#endif
} // createRootWindow

void DeathMenu::registerEvents() {
    using namespace CEGUI;
    
    quitToMenuButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&DeathMenu::quitToMenuEvent, this));
    quitGameButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&DeathMenu::quitGameEvent, this));
} // registerEvents

void DeathMenu::show() {
    Player *player = World::getInstance().getCurrentPlayer();
    if (player != NULL) {
        scoreTextField->setText(StringHelper::concat<int>("", 
            player->getScore()));
    } // if

#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif
} // show

void DeathMenu::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif

} // hide

bool DeathMenu::quitToMenuEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();

#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif

    GUIManager::getInstance().mainMenu->show();
    World::getInstance().playerQuit();
    return false;
} // quitToMenuEvent

bool DeathMenu::quitGameEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    InputManager::getInstance().shutDown();
    return false;
} // quitEvent
