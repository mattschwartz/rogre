/**
 * Included files
 */
#include "MainMenu.h"
#include "src/entities/player/Player.h"

MainMenu::MainMenu() {
    using namespace CEGUI;
    WindowManager &windowManager = WindowManager::getSingleton();

    mRoot = windowManager.createWindow("DefaultWindow", "root");
    System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
    FrameWindow *fWnd = static_cast<FrameWindow*>(windowManager.createWindow("OgreTray/FrameWindow", "testWindow"));
    mRoot->addChild(fWnd);
    fWnd->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(0.25f, 0.0f)));
    fWnd->setSize(USize(UDim(0.5f, 0.0f), UDim(0.5f, 0.0f)));
    fWnd->setText("Hello world");
} // constructor
