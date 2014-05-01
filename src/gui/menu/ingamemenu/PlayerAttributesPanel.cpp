/**
 * Included files
 */
#include "PlayerAttributesPanel.h"
#include "src/entities/player/Player.h"
#include "src/utility/StringHelper.h"

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
    
    playerDmgReductionLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    playerDmgReductionLabel->setPosition(UVector2(UDim(1.0f, -300.0f), UDim(0.0f, 80.0f)));
    playerDmgReductionLabel->setText("Damage reduced by:");
    
    playerDmgReductionValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    playerDmgReductionValue->setPosition(UVector2(UDim(1.0f, -100.0f), UDim(0.0f, 80.0f)));
    
    playerDmgOutputLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    playerDmgOutputLabel->setPosition(UVector2(UDim(1.0f, -300.0f), UDim(0.0f, 120.0f)));
    playerDmgOutputLabel->setText("Damage multiplier:");
    
    playerDmgOutputValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    playerDmgOutputValue->setPosition(UVector2(UDim(1.0f, -100.0f), UDim(0.0f, 120.0f)));
} // createWidgets

void PlayerAttributesPanel::updateAttributes(Player *player) {
    using namespace StringHelper;
    std::string damageReduction;
    std::string damageOutput;

    damageReduction = concat<double>("-", (double)(1 + (player->getAttribute(armor) / 10.0)));
    damageReduction = concat<std::string>(damageReduction, "%");
    damageOutput = concat<double>("+", (double)(1 + (player->getAttribute(strength) / 100.0)));
    damageOutput = concat<std::string>(damageOutput, "%");

    playerHealthValue->setText(StringHelper::concat<double>("", player->getAttribute(hitpoints)));
    playerDmgReductionValue->setText(damageReduction);
    playerDmgOutputValue->setText(damageOutput);
} // updateAttributes

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
