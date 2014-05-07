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
#include "src/utility/GUIHelper.h"

DeathMenu::DeathMenu() 
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor

void DeathMenu::createWidgets() {
    using namespace CEGUI;
#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background2", "death_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "DeathMenu/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background2 image:full_image");
#endif
    
    titleLabel = windowManager.createWindow("OgreTray/Title", "DeathMenu/titleLabel");
    textLabel = windowManager.createWindow("OgreTray/Title", "DeathMenu/textLabel");
    scoreTextField = windowManager.createWindow("OgreTray/Editbox", "DeathMenu/scoreTextField");
    slayerLabel = windowManager.createWindow("OgreTray/Title", "DeathMenu/slayerLabel");
    slayerTextField = windowManager.createWindow("OgreTray/Editbox", "DeathMenu/slayerTextField");
    quitToMenuButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "DeathMenu/quitToMenuButton"));
    quitGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "DeathMenu/quitGameButton"));

    titleLabel->setSize(SIZE(0.0f, 600.0f, 0.0f, 40.0f));
    titleLabel->setPosition(UVector2(UDim(0.5f, -300.0f), UDim(0.5f, -70.0f)));
    titleLabel->setText("You Have Died.");
    titleLabel->setAlwaysOnTop(true);

    textLabel->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    textLabel->setPosition(UVector2(UDim(0.5f, -300.0f), UDim(0.5f, -20.0f)));
    textLabel->setText("Final Score: ");
    textLabel->setAlwaysOnTop(true);

    scoreTextField->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    scoreTextField->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, -20.0f)));
    scoreTextField->setText("0");
    scoreTextField->setEnabled(false);
    scoreTextField->setAlwaysOnTop(true);

    slayerLabel->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    slayerLabel->setPosition(UVector2(UDim(0.5f, -300.0f), UDim(0.5f, 20.0f)));
    slayerLabel->setText("Slain by");
    slayerLabel->setAlwaysOnTop(true);

    slayerTextField->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    slayerTextField->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, 20.0f)));
    slayerTextField->setText("an act of god");
    slayerTextField->setEnabled(false);
    slayerTextField->setAlwaysOnTop(true);

    quitToMenuButton->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    quitToMenuButton->setPosition(UVector2(UDim(0.5f, -300.0f), UDim(0.5f, 60.0f)));
    quitToMenuButton->setText("Main Menu");
    quitToMenuButton->setAlwaysOnTop(true);
    
    quitGameButton->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    quitGameButton->setPosition(UVector2(UDim(0.5f, 0.0f), UDim(0.5f, 60.0f)));
    quitGameButton->setText("Quit");
    quitGameButton->setAlwaysOnTop(true);
} // createWidgets

void DeathMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "DeathMenu/root");

#if USE_OGRE_LEGACY  
    mRoot->addChildWindow(backgroundWindow); 
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(textLabel);
    mRoot->addChildWindow(scoreTextField);
    mRoot->addChildWindow(slayerLabel);
    mRoot->addChildWindow(slayerTextField);
    mRoot->addChildWindow(quitToMenuButton);
    mRoot->addChildWindow(quitGameButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(textLabel);
    mRoot->addChild(scoreTextField);
    mRoot->addChild(slayerLabel);
    mRoot->addChild(slayerTextField);
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

void DeathMenu::setSlainBy(std::string name) {
    slayerTextField->setText(name);
} // setSlainBy

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
