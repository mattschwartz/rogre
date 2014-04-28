/**
 * Included files
 */
#include "LoadingMenu.h"

LoadingMenu::LoadingMenu()
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
} // constructor

void LoadingMenu::createWidgets() {
    using namespace CEGUI;
    loadingBar = static_cast<ProgressBar*>(
        windowManager.createWindow("OgreTray/ProgressBar", "LoadingMenu/progressBar"));
    loadingBar->setSize(USize(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
    loadingBar->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(1.0f, -40.0f)));
    loadingBar->setText("Loading Zone...");
} // createWidgets

void LoadingMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "LoadingMenu/root");
    mRoot->addChild(loadingBar);
} // createRootWindow

void LoadingMenu::setProgress(float progress) {
    loadingBar->setProgress(progress);
} // setProgress

void LoadingMenu::show() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
} // show

void LoadingMenu::hide() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
} // hide
