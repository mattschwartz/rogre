/**
 * Included files
 */
#include "InfoLogPanel.h"
#include "src/entities/player/Player.h"

InfoLogPanel::InfoLogPanel() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    registerEvents();
    visible = true;
} // constructor

void InfoLogPanel::createWidgets() {
    using namespace CEGUI;

    textLog = static_cast<MultiLineEditbox*>(
        windowManager.createWindow("OgreTray/MultiLineEditbox", "InfoLogPanel/textLog"));
    toggleLogButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InfoLogPanel/toggleLogButton"));
    clearButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "InfoLogPanel/clearButton"));

#if USE_OGRE_LEGACY
    textLog->setSize(UVector2(UDim(0.5f, 0.0f), UDim(0.20f, 0.0f)));
    toggleLogButton->setSize(UVector2(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    clearButton->setSize(UVector2(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
#else
    textLog->setSize(USize(UDim(0.5f, 0.0f), UDim(0.20f, 0.0f)));
    toggleLogButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    clearButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
#endif

    textLog->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.80f, -5.0f)));
    textLog->setText("Welcome to ROgre v0.1.0!");
    textLog->setWordWrapping(true);
    textLog->setReadOnly(true);

    toggleLogButton->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.80f, -45.0f)));
    toggleLogButton->setText("Hide log");

    clearButton->setPosition(UVector2(UDim(0.0f, 110.0f), UDim(0.80f, -45.0f)));
    clearButton->setText("Clear log");
} // createWidgets

void InfoLogPanel::registerEvents() {
    using namespace CEGUI;
    
    toggleLogButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&InfoLogPanel::toggleLogEvent, this));
    clearButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&InfoLogPanel::clearEvent, this));
} // registerEvents

bool InfoLogPanel::toggleLogEvent(const CEGUI::EventArgs &e) {
    using namespace CEGUI;
    visible = !visible;

    if (visible) {
#if USE_OGRE_LEGACY
        mRoot->addChildWindow(textLog);
        mRoot->addChildWindow(clearButton);
#else
        mRoot->addChild(textLog);
        mRoot->addChild(clearButton);
#endif
        toggleLogButton->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.80f, -45.0f)));
        toggleLogButton->setText("Hide log");
    } // if
    else {
#if USE_OGRE_LEGACY
        mRoot->removeChildWindow(textLog);
        mRoot->removeChildWindow(clearButton);
#else
        mRoot->removeChild(textLog);
        mRoot->removeChild(clearButton);
#endif
        toggleLogButton->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(1.0f, -45.0f)));
        toggleLogButton->setText("Show log");
    } // else

    return true;
} // toggleLogEvent

bool InfoLogPanel::clearEvent(const CEGUI::EventArgs &e) {
    textLog->setText("Log cleared.");
    return true;
} // clearEvent

void InfoLogPanel::append(std::string text) {
    textLog->appendText(text);
    textLog->setCaretIndex(INT_MAX);
    textLog->ensureCaretIsVisible();
} // append

void InfoLogPanel::appendLine(std::string text) {
    textLog->appendText(text);
} // append

void InfoLogPanel::addPanelTo(CEGUI::Window *mRoot) {
    this->mRoot = mRoot;

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(textLog);
    mRoot->addChildWindow(toggleLogButton);
    mRoot->addChildWindow(clearButton);
#else
    mRoot->addChild(textLog);
    mRoot->addChild(toggleLogButton);
    mRoot->addChild(clearButton);
#endif
} // addPanelTo

void InfoLogPanel::loadPlayer(Player *player) {
    textLog->setText("Welcome to ROgre v0.1.0, " + player->getName() + "!");
} // loadPlayer
