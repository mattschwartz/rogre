/**
 * Included files
 */
#include "BasicAttributesPanel.h"
#include "src/entities/player/Player.h"
#include "src/utility/StringHelper.h"

BasicAttributesPanel::BasicAttributesPanel() : 
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
} // constructor

void BasicAttributesPanel::createWidgets() {
    using namespace CEGUI;

    hitpointsLabel = windowManager.createWindow("OgreTray/Title", "BasicAttributesPanel/hitpointsLabel");
    hitpointsValue = windowManager.createWindow("OgreTray/Title", "BasicAttributesPanel/hitpointsValue");
    armorLabel = windowManager.createWindow("OgreTray/Title", "BasicAttributesPanel/armorLabel");
    armorValue = windowManager.createWindow("OgreTray/Title", "BasicAttributesPanel/armorValue");
    strengthLabel = windowManager.createWindow("OgreTray/Title", "BasicAttributesPanel/strengthLabel");
    strengthValue = windowManager.createWindow("OgreTray/Title", "BasicAttributesPanel/strengthValue");
    
#if USE_OGRE_LEGACY
    hitpointsLabel->setSize(UVector2(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    hitpointsValue->setSize(UVector2(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    armorLabel->setSize(UVector2(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    armorValue->setSize(UVector2(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    strengthLabel->setSize(UVector2(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    strengthValue->setSize(UVector2(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));

#else
    hitpointsLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    hitpointsValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    armorLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    armorValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    strengthLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    strengthValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
#endif

    hitpointsLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 85.0f)));
    hitpointsLabel->setText("Hitpoints:");
    

    hitpointsValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 85.0f)));
    

    armorLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 125.0f)));
    armorLabel->setText("Armor:");
    

    armorValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 125.0f)));
    

    strengthLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 165.0f)));
    strengthLabel->setText("Strength:");
    

    strengthValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 165.0f)));
} // createWidgets

void BasicAttributesPanel::addPanelTo(CEGUI::Window *mRoot) {
#if USE_OGRE_LEGACY
    mRoot->addChildWindow(hitpointsLabel);
    mRoot->addChildWindow(hitpointsValue);
    mRoot->addChildWindow(armorLabel);
    mRoot->addChildWindow(armorValue);
    mRoot->addChildWindow(strengthLabel);
    mRoot->addChildWindow(strengthValue);
#else
    mRoot->addChild(hitpointsLabel);
    mRoot->addChild(hitpointsValue);
    mRoot->addChild(armorLabel);
    mRoot->addChild(armorValue);
    mRoot->addChild(strengthLabel);
    mRoot->addChild(strengthValue);
#endif
} // addPanelTo

void BasicAttributesPanel::removePanelFrom(CEGUI::Window *mRoot) {
#if USE_OGRE_LEGACY
    mRoot->removeChildWindow(hitpointsLabel);
    mRoot->removeChildWindow(hitpointsValue);
    mRoot->removeChildWindow(armorLabel);
    mRoot->removeChildWindow(armorValue);
    mRoot->removeChildWindow(strengthLabel);
    mRoot->removeChildWindow(strengthValue);

#else
    mRoot->removeChild(hitpointsLabel);
    mRoot->removeChild(hitpointsValue);
    mRoot->removeChild(armorLabel);
    mRoot->removeChild(armorValue);
    mRoot->removeChild(strengthLabel);
    mRoot->removeChild(strengthValue);
#endif
} // removePanelFrom

void BasicAttributesPanel::updateAttributes(Player *player) {
    using namespace StringHelper;
    std::string armorText = concat<double>("", player->getAttribute(armor));
    std::string hitpointsText = concat<double>("", player->getAttribute(hitpoints));
    std::string strengthText = concat<double>("", player->getAttribute(strength));

    strengthValue->setText(strengthText);
    armorValue->setText(armorText);
    hitpointsValue->setText(hitpointsText);
} // updateAttributes
