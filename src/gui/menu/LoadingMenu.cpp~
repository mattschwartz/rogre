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


#if USE_OGRE_LEGACY
    textLabel->setSize(UVector2(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
    tipLabel->setSize(UVector2(UDim(1.0f, -10.0f), UDim(0.0f, 40.0f)));
    loadingBar->setSize(UVector2(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
#else
    textLabel->setSize(USize(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
    tipLabel->setSize(USize(UDim(1.0f, -10.0f), UDim(0.0f, 40.0f)));
    loadingBar->setSize(USize(UDim(0.5f, 0.0f), UDim(0.0f, 40.0f)));
#endif

    textLabel->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(1.0f, -80.0f)));
    textLabel->setText("Loading...");


    tipLabel->setPosition(UVector2(UDim(0.0f, 5.0f), UDim(0.0f, 5.0f)));
    tipLabel->setText("Tips");



    loadingBar->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(1.0f, -40.0f)));
} // createWidgets

void LoadingMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "LoadingMenu/root");
#if USE_OGRE_LEGACY 
    mRoot->addChildWindow(textLabel);
    mRoot->addChildWindow(tipLabel);
    mRoot->addChildWindow(loadingBar);
#else
    mRoot->addChild(textLabel);
    mRoot->addChild(tipLabel);
    mRoot->addChild(loadingBar);
#endif

} // createRootWindow

void LoadingMenu::setProgress(float progress) {
    loadingBar->setProgress(progress);
} // setProgress

void LoadingMenu::show() {
    tipLabel->setText(TipsUtility::getRandomTip());
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif

} // show

void LoadingMenu::hide() {
    GUIManager::getInstance().inGameMenu->show();
} // hide

void LoadingMenu::setText(std::string title) {
    textLabel->setText(title);
} // setText
