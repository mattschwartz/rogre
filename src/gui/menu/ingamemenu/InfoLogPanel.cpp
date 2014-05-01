/**
 * Included files
 */
#include "InfoLogPanel.h"

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

    textLog->setSize(USize(UDim(0.5f, 0.0f), UDim(0.20f, 0.0f)));
    textLog->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.80f, -5.0f)));
    textLog->setText("Welcome to ROgre v0.1.0");
    textLog->setEnabled(false);

    toggleLogButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    toggleLogButton->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.80f, -45.0f)));
    toggleLogButton->setText("Hide log");

    clearButton->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
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
        mRoot->addChild(textLog);
        mRoot->addChild(clearButton);
        toggleLogButton->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(0.80f, -45.0f)));
        toggleLogButton->setText("Hide log");
    } // if
    else {
        mRoot->removeChild(textLog);
        mRoot->removeChild(clearButton);
        toggleLogButton->setPosition(UVector2(UDim(0.0f, 10.0f), UDim(1.0f, -45.0f)));
        toggleLogButton->setText("Show log");
    } // else

    return true;
} // toggleLogEvent

bool InfoLogPanel::clearEvent(const CEGUI::EventArgs &e) {
    textLog->setText("");
    return true;
} // clearEvent

void InfoLogPanel::append(std::string text) {
    textLog->appendText(text);
} // append

void InfoLogPanel::appendLine(std::string text) {
    textLog->appendText(text);
    textLog->appendText("\n");
} // append

void InfoLogPanel::addPanelTo(CEGUI::Window *mRoot) {
    this->mRoot = mRoot;
    mRoot->addChild(textLog);
    mRoot->addChild(toggleLogButton);
    mRoot->addChild(clearButton);
} // addPanelTo
