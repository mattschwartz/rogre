/**
 * Included files
 */
#include "LoadingMenu.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/ingamemenu/InGameMenu.h"
#include "src/utility/TipsUtility.h"

LoadingMenu::LoadingMenu()
    : windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
    TipsUtility::init();
} // constructor

void LoadingMenu::createWidgets() {
    using namespace CEGUI;
    textLabel = windowManager.createWindow("OgreTray/Title", "LoadingMenu/textLabel");
    tipLabel = windowManager.createWindow("OgreTray/Title", "LoadingMenu/tipLabel");
    loadingBar = static_cast<ProgressBar*>(
        windowManager.createWindow("OgreTray/ProgressBar", "LoadingMenu/progressBar"));

    textLabel->setSize(USize(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
    textLabel->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(1.0f, -80.0f)));
    textLabel->setText("Loading...");

    tipLabel->setSize(USize(UDim(1.0f, -10.0f), UDim(0.0f, 40.0f)));
    tipLabel->setPosition(UVector2(UDim(0.0f, 5.0f), UDim(0.0f, 5.0f)));
    tipLabel->setText("Tips");

    loadingBar->setSize(USize(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
    loadingBar->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(1.0f, -40.0f)));
} // createWidgets

void LoadingMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "LoadingMenu/root");
    mRoot->addChild(textLabel);
    mRoot->addChild(tipLabel);
    mRoot->addChild(loadingBar);
} // createRootWindow

void LoadingMenu::setProgress(float progress) {
    loadingBar->setProgress(progress);
} // setProgress

void LoadingMenu::show() {
    tipLabel->setText(TipsUtility::getRandomTip());
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
} // show

void LoadingMenu::hide() {
    GUIManager::getInstance().inGameMenu->show();
} // hide

void LoadingMenu::setText(std::string title) {
    textLabel->setText(title);
} // setText
