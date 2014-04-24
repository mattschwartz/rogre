/**
 * Included files
 */
#include <Ogre.h>
#include "GUIManager.h"
#include "src/main/BaseApplication.h"

void GUIManager::initCEGUI() {
    using namespace CEGUI;
    mRenderer = &OgreRenderer::bootstrapSystem();
    WindowManager &windowManager = WindowManager::getSingleton();

    setResourceGroups();
    setLookNFeel();
} // initCEGUI

void GUIManager::setResourceGroups() {
    using namespace CEGUI;

#if USE_OGRE_LEGACY
    Image::setDefaultResourceGroup("Imagesets");
#else
    ImageManager::setImagesetDefaultResourceGroup("Imagesets");
#endif

    Font::setDefaultResourceGroup("Fonts");
    Scheme::setDefaultResourceGroup("Schemes");
    WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    WindowManager::setDefaultResourceGroup("Layouts");
} // setResourceGroups

void GUIManager::setLookNFeel() {
    using namespace CEGUI;

    SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
    System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");

#if USE_OGRE_LEGACY
    System::getSingleton().setDefaultMouseCursor("OgreTray", "MouseArrow");
#else
    System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");
#endif
} // setLookNFeel
