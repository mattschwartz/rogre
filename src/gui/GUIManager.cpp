/**
 * Included files
 */
#include <Ogre.h>
#include "GUIManager.h"
#include "src/main/BaseApplication.h"
#include "menu/MainMenu.h"
#include "menu/NewPlayerMenu.h"
#include "menu/LoadPlayerMenu.h"
#include "menu/OptionsMenu.h"
#include "menu/LoadingMenu.h"
#include "menu/DeathMenu.h"
#include "menu/ingamemenu/InGameMenu.h"
#include "menu/HiScoresMenu.h"
#include "menu/CreditPage.h"

void GUIManager::init() {
    initCEGUI();
    mainMenu = new MainMenu();
    newPlayerMenu = new NewPlayerMenu();
    loadPlayerMenu = new LoadPlayerMenu();
    optionsMenu = new OptionsMenu();
    loadingMenu = new LoadingMenu();
    deathMenu = new DeathMenu();
    inGameMenu = new InGameMenu();
    hiScoresMenu = new HiScoresMenu();
    creditPage = new CreditPage();
} // init

void GUIManager::initCEGUI() {
    using namespace CEGUI;

    mRenderer = &OgreRenderer::bootstrapSystem();
    WindowManager &windowManager = WindowManager::getSingleton();

    setResourceGroups();
    setLookNFeel();
} // initCEGUI

void GUIManager::hideCurrentMenu() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hideCurrentMenu

void GUIManager::setResourceGroups() {
    using namespace CEGUI;

#if USE_OGRE_LEGACY
    Imageset::setDefaultResourceGroup("Imagesets");
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

#if USE_OGRE_LEGACY
   SchemeManager::getSingleton().create("OgreTray.scheme");
   System::getSingleton().setDefaultMouseCursor("OgreTrayImages", "MouseArrow");
   System::getSingleton().setDefaultFont("DejaVuSans-10");
#else
    SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
    System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
    System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");
#endif
} // setLookNFeel
