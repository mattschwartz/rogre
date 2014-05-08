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
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().injectKeyDown((CEGUI::Key::Scan)arg.key);
    CEGUI::System::getSingleton().injectChar(arg.text);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)arg.key);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(arg.text);
#endif

    KeyHandler::getInstance().invoke(arg.key);
} // keyPressed

void InputManager::keyReleased(const OIS::KeyEvent &arg) {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().injectKeyUp((CEGUI::Key::Scan)arg.key);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
#endif
} // keyReleased

void InputManager::mouseMoved(const OIS::MouseEvent &arg) {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove((float)arg.state.X.rel, (float)arg.state.Y.rel);
#endif

	ObjectManager::getInstance().mouseMoved(arg);
} // mouseMoved

void InputManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
#else
    if (id == OIS::MB_Left && CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton)) return;
#endif

	ObjectManager::getInstance().mousePressed(arg, id);
} // mousePressed

void InputManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
#else
    if (id == OIS::MB_Left && CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton)) return;
#endif

    ObjectManager::getInstance().mouseReleased(arg, id);
} // mouseReleased

void InputManager::shutDown() {
    mShutDown = true;
} // shutDown

bool InputManager::shouldShutDown() {
    return mShutDown;
} // shouldShutDown
