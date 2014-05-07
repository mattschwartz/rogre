/**
 * Included files
 */
#include "HiScoresMenu.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/MainMenu.h"
#include "src/sound/SoundEffect.h"
#include "src/sound/SoundManager.h"
#include "src/utility/GUIHelper.h"

HiScoresMenu::HiScoresMenu() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor

void HiScoresMenu::createWidgets() {
    using namespace CEGUI;

    titleLabel = windowManager.createWindow("OgreTray/Title", "HiScoresMenu/titleLabel");
    backButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "HiScoresMenu/backButton"));
    resetScoresButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "HiScoresMenu/resetScoresButton"));
    scores = windowManager.createWindow("OgreTray/MultiLineEditbox", "HiScoresMenu/scores");
    
    titleLabel->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    titleLabel->setPosition(POS(0.5f, -150.0f, 0.5f, -175.0f));
    titleLabel->setText("Graveyard");
    titleLabel->setAlwaysOnTop(true);

    scores->setSize(SIZE(0.0f, 600.0f, 0.0f, 250.0f));
    scores->setPosition(POS(0.5f, -300.0f, 0.5f, -125.0f));
    scores->setText("Player 1 died with a score of 19843 on 05.07.2014.");
    ((MultiLineEditbox*)scores)->setReadOnly(true);
    scores->setAlwaysOnTop(true);

    backButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    backButton->setPosition(POS(0.5f, -150.0f, 0.5f, 125.0f));
    backButton->setText("Back");
    backButton->setAlwaysOnTop(true);

    resetScoresButton->setSize(SIZE(0.0f, 150.0f, 0.0f, 40.0f));
    resetScoresButton->setPosition(POS(0.5f, 0.0f, 0.5f, 125.0f));
    resetScoresButton->setText("Reset All Scores");
    resetScoresButton->setAlwaysOnTop(true);
} // createWidgets

void HiScoresMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "HiScoresMenu/root");

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(scores);
    mRoot->addChildWindow(backButton);
    mRoot->addChildWindow(resetScoresButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(scores);
    mRoot->addChild(backButton);
    mRoot->addChild(resetScoresButton);
#endif
} // createRootWindow

void HiScoresMenu::registerEvents() {
    using namespace CEGUI;

    backButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&HiScoresMenu::backEvent, this));
    resetScoresButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&HiScoresMenu::resetScoresEvent, this));
} // registerEvents

bool HiScoresMenu::backEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().mainMenu->show();
    return false;
} // backEvent

bool HiScoresMenu::resetScoresEvent(const CEGUI::EventArgs &e) {
    return false;
} // resetScoresEvent

void HiScoresMenu::show() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif
} // show

void HiScoresMenu::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hide
