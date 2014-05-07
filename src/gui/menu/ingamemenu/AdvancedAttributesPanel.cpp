/**
 * Included files
 */
#include "AdvancedAttributesPanel.h"
#include "src/entities/player/Player.h"
#include "src/utility/StringHelper.h"
#include "src/utility/GUIHelper.h"

AdvancedAttributesPanel::AdvancedAttributesPanel() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
} // constructor

void AdvancedAttributesPanel::createWidgets() {
    using namespace CEGUI;

    playerHealthLabel = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerHealthLabel");
    playerHealthValue = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerHealthValue");
    playerDmgReductionLabel = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgReductionLabel");
    playerDmgReductionValue = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgReductionValue");
    playerDmgOutputLabel = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgOutputLabel");
    playerDmgOutputValue = windowManager.createWindow("OgreTray/Title", "PlayerAttributesPanel/playerDmgOutputValue");

    playerHealthLabel->setSize(SIZE(0.0f, 200.0f, 0.0f, 40.0f));
    playerHealthLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 85.0f)));
    playerHealthLabel->setText("Health regen:");

    playerHealthValue->setSize(SIZE(0.0f, 100.0f, 0.0f, 40.0f));
    playerHealthValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 85.0f)));

    playerDmgReductionLabel->setSize(SIZE(0.0f, 200.0f, 0.0f, 40.0f));
    playerDmgReductionLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 125.0f)));
    playerDmgReductionLabel->setText("Damage reduced by:");

    playerDmgReductionValue->setSize(SIZE(0.0f, 100.0f, 0.0f, 40.0f));
    playerDmgReductionValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 125.0f)));
    
    playerDmgOutputLabel->setSize(SIZE(0.0f, 200.0f, 0.0f, 40.0f));
    playerDmgOutputLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 165.0f)));
    playerDmgOutputLabel->setText("Damage multiplier:");
    
    playerDmgOutputValue->setSize(SIZE(0.0f, 100.0f, 0.0f, 40.0f));
    playerDmgOutputValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 165.0f)));
} // createWidgets

void AdvancedAttributesPanel::addPanelTo(CEGUI::Window *mRoot) {

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(playerHealthLabel);
    mRoot->addChildWindow(playerHealthValue);
    mRoot->addChildWindow(playerDmgReductionLabel);
    mRoot->addChildWindow(playerDmgReductionValue);
    mRoot->addChildWindow(playerDmgOutputLabel);
    mRoot->addChildWindow(playerDmgOutputValue);
#else
    mRoot->addChild(playerHealthLabel);
    mRoot->addChild(playerHealthValue);
    mRoot->addChild(playerDmgReductionLabel);
    mRoot->addChild(playerDmgReductionValue);
    mRoot->addChild(playerDmgOutputLabel);
    mRoot->addChild(playerDmgOutputValue);
#endif
} // getRoot

void AdvancedAttributesPanel::removePanelFrom(CEGUI::Window *mRoot) {

#if USE_OGRE_LEGACY
    mRoot->removeChildWindow(playerHealthLabel);
    mRoot->removeChildWindow(playerHealthValue);
    mRoot->removeChildWindow(playerDmgReductionLabel);
    mRoot->removeChildWindow(playerDmgReductionValue);
    mRoot->removeChildWindow(playerDmgOutputLabel);
    mRoot->removeChildWindow(playerDmgOutputValue);

#else
    mRoot->removeChild(playerHealthLabel);
    mRoot->removeChild(playerHealthValue);
    mRoot->removeChild(playerDmgReductionLabel);
    mRoot->removeChild(playerDmgReductionValue);
    mRoot->removeChild(playerDmgOutputLabel);
    mRoot->removeChild(playerDmgOutputValue);
#endif
} // removePanelFrom

void AdvancedAttributesPanel::updateAttributes(Player *player) {
    using namespace StringHelper;
    std::string damageReduction;
    std::string damageOutput;

    damageReduction = concat<double>("-", (double)(1 + (player->getAttribute(armor) / 10.0)));
    damageReduction = concat<std::string>(damageReduction, "%");
    damageOutput = concat<double>("+", (double)(1 + (player->getAttribute(strength) / 100.0)));
    damageOutput = concat<std::string>(damageOutput, "%");

    playerHealthValue->setText(StringHelper::concat<double>("+", player->getRegen()));
    playerDmgReductionValue->setText(damageReduction);
    playerDmgOutputValue->setText(damageOutput);
} // updateAttributes
