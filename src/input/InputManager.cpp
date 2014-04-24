/**
 * Included files
 */
#include "src/gameobjects/ObjectManager.h"
#include "InputManager.h"
#include "KeyHandler.h"
#include "CEGUI/CEGUI.h"

/**
 * Data
 */
void InputManager::keyPressed(const OIS::KeyEvent &arg) {
    KeyHandler::getInstance().invoke(arg.key);
} // keyPressed

void InputManager::keyReleased(const OIS::KeyEvent &arg) {

} // keyReleased

void InputManager::mouseMoved(const OIS::MouseEvent &arg) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	ObjectManager::getInstance().mouseMoved(arg);
} // mouseMoved

void InputManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
	ObjectManager::getInstance().mousePressed(arg, id);
} // mousePressed

void InputManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
    ObjectManager::getInstance().mouseReleased(arg, id);
} // mouseReleased
