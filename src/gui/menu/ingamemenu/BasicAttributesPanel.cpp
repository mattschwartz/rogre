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
    
    hitpointsLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    hitpointsLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 85.0f)));
    hitpointsLabel->setText("Hitpoints:");
    
    hitpointsValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    hitpointsValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 85.0f)));
    
    armorLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    armorLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 125.0f)));
    armorLabel->setText("Armor:");
    
    armorValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    armorValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 125.0f)));
    
    strengthLabel->setSize(USize(UDim(0.0f, 200.0f), UDim(0.0f, 40.0f)));
    strengthLabel->setPosition(UVector2(UDim(1.0f, -310.0f), UDim(0.0f, 165.0f)));
    strengthLabel->setText("Strength:");
    
    strengthValue->setSize(USize(UDim(0.0f, 100.0f), UDim(0.0f, 40.0f)));
    strengthValue->setPosition(UVector2(UDim(1.0f, -110.0f), UDim(0.0f, 165.0f)));
} // createWidgets

void BasicAttributesPanel::addPanelTo(CEGUI::Window *mRoot) {
    mRoot->addChild(hitpointsLabel);
    mRoot->addChild(hitpointsValue);
    mRoot->addChild(armorLabel);
    mRoot->addChild(armorValue);
    mRoot->addChild(strengthLabel);
    mRoot->addChild(strengthValue);
} // addPanelTo

void BasicAttributesPanel::removePanelFrom(CEGUI::Window *mRoot) {
    mRoot->removeChild(hitpointsLabel);
    mRoot->removeChild(hitpointsValue);
    mRoot->removeChild(armorLabel);
    mRoot->removeChild(armorValue);
    mRoot->removeChild(strengthLabel);
    mRoot->removeChild(strengthValue);
} // removePanelFrom

void BasicAttributesPanel::updateAttributes(Player *player) {
    using namespace StringHelper;
    std::string armorText = concat<double>("", player->getAttribute(armor));
    std::string strengthText = concat<double>("", player->getAttribute(strength));

    strengthValue->setText(strengthText);
    armorValue->setText(armorText);
} // updateAttributes
