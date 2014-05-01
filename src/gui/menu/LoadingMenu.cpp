/**
 * Included files
 */
#include "LoadingMenu.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/ingamemenu/InGameMenu.h"

LoadingMenu::LoadingMenu()
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
} // constructor

void LoadingMenu::createWidgets() {
    using namespace CEGUI;
    textLabel = windowManager.createWindow("OgreTray/Title", "LoadingMenu/textLabel");
    loadingBar = static_cast<ProgressBar*>(
        windowManager.createWindow("OgreTray/ProgressBar", "LoadingMenu/progressBar"));

    textLabel->setSize(USize(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
    textLabel->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(1.0f, -80.0f)));
    textLabel->setText("Loading...");

    loadingBar->setSize(USize(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
    loadingBar->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(1.0f, -40.0f)));
} // createWidgets

void LoadingMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "LoadingMenu/root");
    mRoot->addChild(textLabel);
    mRoot->addChild(loadingBar);
} // createRootWindow

void LoadingMenu::setProgress(float progress) {
    loadingBar->setProgress(progress);
} // setProgress

void LoadingMenu::show() {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
} // show

void LoadingMenu::hide() {
    GUIManager::getInstance().inGameMenu->show();
} // hide

void LoadingMenu::setText(std::string title) {
    textLabel->setText(title);
} // setText
