/**
 * Included files
 */
#include "src/gameobjects/ObjectManager.h"
#include "InputManager.h"
#include "KeyHandler.h"
#include "CEGUI/CEGUI.h"

void InputManager::init() {
    mShutDown = false;
} // init

/**
 * Data
 */
void InputManager::keyPressed(const OIS::KeyEvent &arg) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)arg.key);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(arg.text);
    KeyHandler::getInstance().invoke(arg.key);
} // keyPressed

void InputManager::keyReleased(const OIS::KeyEvent &arg) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
} // keyReleased

void InputManager::mouseMoved(const OIS::MouseEvent &arg) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	ObjectManager::getInstance().mouseMoved(arg);
} // mouseMoved

void InputManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    if (id == OIS::MB_Left && CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton)) return;
	ObjectManager::getInstance().mousePressed(arg, id);
} // mousePressed

void InputManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    if (id == OIS::MB_Left && CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton)) return;
    ObjectManager::getInstance().mouseReleased(arg, id);
} // mouseReleased

void InputManager::shutDown() {
    mShutDown = true;
} // shutDown

bool InputManager::shouldShutDown() {
    return mShutDown;
} // shouldShutDown
