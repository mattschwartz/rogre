/**
 * Included files
 */
#include "NewPlayerMenu.h"
#include "MainMenu.h"
#include "LoadingMenu.h"
#include "ingamemenu/InGameMenu.h"
#include "src/gui/GUIManager.h"
#include "src/world/World.h"
#include "src/entities/player/Player.h"
#include "src/sound/SoundManager.h"
#include "src/sound/SoundEffect.h"
#include "src/utility/GUIHelper.h"
#include "src/utility/StringHelper.h"
#include <thread>
#include <string>
#include <climits>

NewPlayerMenu::NewPlayerMenu() :
    windowManager(CEGUI::WindowManager::getSingleton()) {

    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor

void NewPlayerMenu::createWidgets() { 
    using namespace CEGUI;
#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background", "main_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "NewPlayerMenu/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background image:full_image");
    blindModeCheckbox = static_cast<Checkbox*>(
        windowManager.createWindow("OgreTray/Checkbox", "NewPlayerMenu/blindModeCheckbox"));
#else
    blindModeCheckbox = static_cast<ToggleButton*>(
        windowManager.createWindow("OgreTray/Checkbox", "NewPlayerMenu/blindModeCheckbox"));
#endif
    
    titleLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/titleLabel");
    playerNameLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/playerNameLabel");
    playerNameTextField = windowManager.createWindow("OgreTray/Editbox", "NewPlayerMenu/playerNameTextField");
    
    gameSettingsLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/gameSettingsLabel");
    difficultyLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/difficultyLabel");
    difficultyTextField = windowManager.createWindow("OgreTray/Editbox", "NewPlayerMenu/difficultyTextField");
    difficultySlider = static_cast<Slider*>(
        windowManager.createWindow("OgreTray/Slider", "NewPlayerMenu/difficultySlider"));
    seedLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/seedLabel");
    seedTextField = windowManager.createWindow("OgreTray/Editbox", "NewPlayerMenu/seedTextField");
    startingZoneLevelLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/startingZoneLevelLabel");
    startingZoneLevelTextField = static_cast<Spinner*>(
        windowManager.createWindow("OgreTray/Spinner", "NewPlayerMenu/startingZoneLevelTextField"));
    blindModeLabel = windowManager.createWindow("OgreTray/Title", "NewPlayerMenu/blindModeLabel");

    backButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "NewPlayerMenu/backButton"));
    startGameButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "NewPlayerMenu/startGameButton"));

    titleLabel->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    titleLabel->setPosition(POS(0.5f, -150.0f, 0.5f, -170.0f));
    titleLabel->setText("Create a New Player");
    titleLabel->setAlwaysOnTop(true);
    
    playerNameLabel->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    playerNameLabel->setPosition(POS(0.5f, -150.0f, 0.5f, -130.0f));
    playerNameLabel->setText("Player Name");
    playerNameLabel->setAlwaysOnTop(true);

    playerNameTextField->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    playerNameTextField->setPosition(POS(0.5f, 0.0f, 0.5f, -130.0f));
    playerNameTextField->setText("player1");
    playerNameTextField->setAlwaysOnTop(true);

    gameSettingsLabel->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    gameSettingsLabel->setPosition(POS(0.5f, -150.0f, 0.5f, -80.0f));
    gameSettingsLabel->setText("Advanced Game Settings");
    gameSettingsLabel->setAlwaysOnTop(true);

    seedLabel->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    seedLabel->setPosition(POS(0.5f, -150.0f, 0.5f, -40.0f));
    seedLabel->setText("Seed");
    seedLabel->setAlwaysOnTop(true);

    seedTextField->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    seedTextField->setPosition(POS(0.5f, 0.0f, 0.5f, -40.0f));
    seedTextField->setAlwaysOnTop(true);

    // middle mark

    difficultyLabel->setSize(SIZE(0.0f, 150.0f, 0.0f, 80.0f));
    difficultyLabel->setPosition(POS(0.5f, -150.0f, 0.5f, 0.0f));
    difficultyLabel->setText("Monster\nDifficulty");
    difficultyLabel->setAlwaysOnTop(true);

    difficultySlider->setSize(SIZE(0.0f, 150.0f, 0.0f, 20.0f));
    difficultySlider->setPosition(POS(0.5f, 0.0f, 0.5f, 10.0f));
    difficultySlider->setClickStep(10.0f);
    difficultySlider->setCurrentValue(50.0f);
    difficultySlider->setMaxValue(150.0f);
    difficultySlider->setAlwaysOnTop(true);

    difficultyTextField->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    difficultyTextField->setPosition(POS(0.5f, 0.0f, 0.5f, 40.0f));
    difficultyTextField->setEnabled(false);
    difficultyTextField->setText("50%");
    difficultyTextField->setAlwaysOnTop(true);

    startingZoneLevelLabel->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    startingZoneLevelLabel->setPosition(POS(0.5f, -150.0f, 0.5f, 80.0f));
    startingZoneLevelLabel->setText("Monster Level");
    startingZoneLevelLabel->setAlwaysOnTop(true);

    startingZoneLevelTextField->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    startingZoneLevelTextField->setPosition(POS(0.5f, 0.0f, 0.5f, 80.0f));
    startingZoneLevelTextField->setCurrentValue(1.0);
    startingZoneLevelTextField->setMinimumValue(0.0);
    startingZoneLevelTextField->setMaximumValue(20.0);
    startingZoneLevelTextField->setAlwaysOnTop(true);

    blindModeLabel->setSize(SIZE(0.0f, 260.0f, 0.0f, 40.0f));
    blindModeLabel->setPosition(POS(0.5f, -150.0f, 0.5f, 120.0f));
    blindModeLabel->setText("Enable Blind Mode");
    blindModeLabel->setAlwaysOnTop(true);

    blindModeCheckbox->setSize(SIZE(0.0f, 40.0f, 0.0f, 40.0f));
    blindModeCheckbox->setPosition(POS(0.5f, 110.0f, 0.5f, 120.0f));
    blindModeCheckbox->setSelected(false);
    blindModeCheckbox->setAlwaysOnTop(true);

    backButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    backButton->setPosition(POS(0.5f, -150.0f, 0.5f, 170.0f));
    backButton->setText("Back");
    backButton->setAlwaysOnTop(true);

    startGameButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    startGameButton->setPosition(POS(0.5f, 0.0f, 0.5f, 170.0f));
    startGameButton->setText("Start Game");
    startGameButton->setAlwaysOnTop(true);
} // createWidgets

void NewPlayerMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "NewPlayerMenu/root");
   
#if USE_OGRE_LEGACY
    mRoot->addChildWindow(backgroundWindow); 
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(playerNameLabel);
    mRoot->addChildWindow(playerNameTextField);
    mRoot->addChildWindow(gameSettingsLabel);
    mRoot->addChildWindow(seedLabel);
    mRoot->addChildWindow(seedTextField);
    mRoot->addChildWindow(difficultyLabel);
    mRoot->addChildWindow(difficultySlider);
    mRoot->addChildWindow(difficultyTextField);
    mRoot->addChildWindow(startingZoneLevelLabel);
    mRoot->addChildWindow(startingZoneLevelTextField);
    mRoot->addChildWindow(blindModeLabel);
    mRoot->addChildWindow(blindModeCheckbox);
    mRoot->addChildWindow(backButton);
    mRoot->addChildWindow(startGameButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(playerNameLabel);
    mRoot->addChild(playerNameTextField);
    mRoot->addChild(gameSettingsLabel);
    mRoot->addChild(seedLabel);
    mRoot->addChild(seedTextField);
    mRoot->addChild(difficultyLabel);
    mRoot->addChild(difficultySlider);
    mRoot->addChild(difficultyTextField);
    mRoot->addChild(startingZoneLevelLabel);
    mRoot->addChild(startingZoneLevelTextField);
    mRoot->addChild(blindModeLabel);
    mRoot->addChild(blindModeCheckbox);
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
    difficultySlider->subscribeEvent(Slider::EventValueChanged,
        Event::Subscriber(&NewPlayerMenu::difficultyChanged, this));
} // registerEvents

void NewPlayerMenu::show() {
    int seed = rand() % INT_MAX;
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif

    // reset default options
    playerNameTextField->setText("player1");
    startingZoneLevelTextField->setCurrentValue(1.0);
    difficultySlider->setCurrentValue(50.0f);
    blindModeCheckbox->setSelected(false);
    seedTextField->setText(StringHelper::concat<int>("", seed));
} // show

void NewPlayerMenu::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hide

bool NewPlayerMenu::difficultyChanged(const CEGUI::EventArgs &e) {
    difficultyTextField->setText(StringHelper::percent<int>((int)difficultySlider->getCurrentValue() + 50));

    return false;
} // difficultyChanged

bool NewPlayerMenu::backEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().mainMenu->show();
    return false;
} // backEvent

bool NewPlayerMenu::startGameEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().loadingMenu->show();
    GUIManager::getInstance().loadingMenu->setText("Loading game ...");
    
    startNewPlayer();

    return false;
} // startGameEvent

void NewPlayerMenu::startNewPlayer() {
    bool blindModeEnabled;
    int zoneLevel;
    int difficultyLevel;
    size_t seed;
    std::hash<std::string> hsh;
    Player *player = new Player(1, playerNameTextField->getText().c_str());

    seed = hsh(seedTextField->getText().c_str());
    difficultyLevel = (int)difficultySlider->getCurrentValue() + 50;
    zoneLevel = startingZoneLevelTextField->getCurrentValue();
    blindModeEnabled = blindModeCheckbox->isSelected();

	World::getInstance().loadZone(zoneLevel, difficultyLevel, (int)seed, blindModeEnabled);
    World::getInstance().setCurrentPlayer(player);
	World::getInstance().spawnCurrentPlayer();
    GUIManager::getInstance().inGameMenu->loadPlayer(player);
} // startNewPlayer
