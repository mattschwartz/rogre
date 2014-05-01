/**
 * Included files
 */
#include "PlayerAttributesPanel.h"

PlayerAttributesPanel::PlayerAttributesPanel() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
} // constructor

void PlayerAttributesPanel::createWidgets() {
    using namespace CEGUI;

    palyerAttributesTitle = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/palyerAttributesTitle");
    playerHealthLabel = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerHealthLabel");
    playerHealthValue = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerHealthValue");
    playerDmgReductionLabel = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgReductionLabel");
    playerDmgReductionValue = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgReductionValue");
    playerDmgOutputLabel = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgOutputLabel");
    playerDmgOutputValue = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgOutputValue");
    
    palyerAttributesTitle->setSize(USize(UDim(0.0f, 300.0f), UDim(0.0f, 40.0f)));
    palyerAttributesTitle->setPosition(UVector2(UDim(1.0f, -300.0f), UDim(0.0f, 0.0f)));
    palyerAttributesTitle->setText("Attributes");

    playerHealthLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    playerHealthLabel->setPosition(UVector2(UDim(1.0f, -300.0f), UDim(0.0f, 40.0f)));
    playerHealthLabel->setText("Maximum health:");
    
    playerHealthValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    playerHealthValue->setPosition(UVector2(UDim(1.0f, -100.0f), UDim(0.0f, 40.0f)));
    playerHealthValue->setText("189");
    
    playerDmgReductionLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    playerDmgReductionLabel->setPosition(UVector2(UDim(1.0f, -300.0f), UDim(0.0f, 80.0f)));
    playerDmgReductionLabel->setText("Damage reduced by:");
    
    playerDmgReductionValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    playerDmgReductionValue->setPosition(UVector2(UDim(1.0f, -100.0f), UDim(0.0f, 80.0f)));
    playerDmgReductionValue->setText("17.8%");
    
    playerDmgOutputLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    playerDmgOutputLabel->setPosition(UVector2(UDim(1.0f, -300.0f), UDim(0.0f, 120.0f)));
    playerDmgOutputLabel->setText("Damage dealt:");
    
    playerDmgOutputValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    playerDmgOutputValue->setPosition(UVector2(UDim(1.0f, -100.0f), UDim(0.0f, 120.0f)));
    playerDmgOutputValue->setText("17 - 22");
} // createWidgets

void PlayerAttributesPanel::addPanelTo(CEGUI::Window *mRoot) {
    using namespace CEGUI;

    mRoot->addChild(palyerAttributesTitle);
    mRoot->addChild(playerHealthLabel);
    mRoot->addChild(playerHealthValue);
    mRoot->addChild(playerDmgReductionLabel);
    mRoot->addChild(playerDmgReductionValue);
    mRoot->addChild(playerDmgOutputLabel);
    mRoot->addChild(playerDmgOutputValue);
} // addPanelTo
