/**
 * Included files
 */
#include "PlayerAttributesPanel.h"
#include "AdvancedAttributesPanel.h"
#include "BasicAttributesPanel.h"
#include "src/entities/player/Player.h"
#include "src/utility/StringHelper.h"

PlayerAttributesPanel::PlayerAttributesPanel() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    registerEvents();
    pageNumber = 0;
} // constructor

void PlayerAttributesPanel::createWidgets() {
    using namespace CEGUI;

    basicAttributesPanel = new BasicAttributesPanel();
    advancedAttributesPanel = new AdvancedAttributesPanel();

    playerAttributesTitle = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerAttributesTitle");
    togglePageButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "PlayerAttributesPanel/togglePageButton"));
#if USE_OGRE_LEGACY
    playerAttributesTitle->setSize(UVector2(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    togglePageButton->setSize(UVector2(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
#else
    playerAttributesTitle->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    togglePageButton->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
#endif

    playerAttributesTitle->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 5.0f)));
    playerAttributesTitle->setText("Attributes");
    

    togglePageButton->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 45.0f)));
    togglePageButton->setText("Show Advanced Attributes");
} // createWidgets

void PlayerAttributesPanel::registerEvents() {
    using namespace CEGUI;
    
    togglePageButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&PlayerAttributesPanel::togglePageEvent, this));
} // registerEvents

void PlayerAttributesPanel::updateAttributes(Player *player) {
    advancedAttributesPanel->updateAttributes(player);
    basicAttributesPanel->updateAttributes(player);
} // updateAttributes

void PlayerAttributesPanel::addPanelTo(CEGUI::Window *mRoot) {
#if USE_OGRE_LEGACY
    this->mRoot = mRoot;
    mRoot->addChildWindow(playerAttributesTitle);
    basicAttributesPanel->addPanelTo(mRoot);
    mRoot->addChildWindow(togglePageButton);
#else
    this->mRoot = mRoot;
    mRoot->addChild(playerAttributesTitle);
    basicAttributesPanel->addPanelTo(mRoot);
    mRoot->addChild(togglePageButton);
#endif

} // addPanelTo

bool PlayerAttributesPanel::togglePageEvent(const CEGUI::EventArgs &e) {
    pageNumber = (pageNumber + 1) % 2;

    switch (pageNumber) {
        case 0:
            advancedAttributesPanel->removePanelFrom(mRoot);
            basicAttributesPanel->addPanelTo(mRoot);
            togglePageButton->setText("Show Advanced Attributes");
            break;
        case 1:
            basicAttributesPanel->removePanelFrom(mRoot);
            advancedAttributesPanel->addPanelTo(mRoot);
            togglePageButton->setText("Show Basic Attributes");
            break;
    } // switch-case

    return true;
} // togglePageEvent
