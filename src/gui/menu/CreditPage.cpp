/**
 * Included files
 */
#include "CreditPage.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/MainMenu.h"
#include "src/sound/SoundEffect.h"
#include "src/sound/SoundManager.h"
#include "src/utility/GUIHelper.h"
#include "src/utility/filesys/FileManager.h"

CreditPage::CreditPage() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor



void CreditPage::createWidgets() {
    using namespace CEGUI;

    titleLabel = windowManager.createWindow("OgreTray/Title", "CreditPage/titleLabel");
    backButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "CreditPage/backButton"));
    credits = windowManager.createWindow("OgreTray/MultiLineEditbox", "CreditPage/credits");

#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background", "main_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "CreditPage/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background image:full_image");
#endif
    
    titleLabel->setSize(SIZE(0.0f, (450.0f / 2), 0.0f, 40.0f));
    titleLabel->setPosition(POS(0.58f, -(450.0f / 2), 0.5f, -300.0f));
    titleLabel->setText("Credits");
    titleLabel->setAlwaysOnTop(true);

    credits->setSize(SIZE(0.0f, 900.0f, 0.0f, 425.0f));
    credits->setPosition(POS(0.35f, -(450.0f / 2), 0.5f, -250.0f));
    credits->setText("Credits");
    ((MultiLineEditbox*)credits)->setReadOnly(true);
    credits->setAlwaysOnTop(true);

    backButton->setSize(SIZE(0.0f, (450.0f / 2), 0.0f, 40.0f));
    backButton->setPosition(POS(0.58f, -(450.0f / 2), 0.5f, 185.0f));
    backButton->setText("Back");
    backButton->setAlwaysOnTop(true);

} //createWidgets

void CreditPage::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "CreditPage/root");

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(backgroundWindow);
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(credits);
    mRoot->addChildWindow(backButton);
#else
    mRoot->addChild(titleLabel);
    mRoot->addChild(credits);
    mRoot->addChild(backButton);
#endif
} // createRootWindow


void CreditPage::registerEvents() {
    using namespace CEGUI;

    backButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&CreditPage::backEvent, this));
} // registerEvents


void CreditPage::show() {
    ((CEGUI::MultiLineEditbox*)credits)->setText("Credits: \n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("Matt Schwartz: Game designer, Interface manager, world creator, and game architect.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("Alexander Ip: Linux porter, Game tester, Sound wrangler.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("Nicholas Carter: Linux porter, Mesh wrangler and converter.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("We would like to thank the wonderful individuals at blendswap.org for creating the wide array models that we used in the program. So thanks to:\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("Adriana.chiabrera for providing the chest model.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("Anonymous for providing the sack for items.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("DennlsH2010 for providing the big iron doors.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("XGhostx7 for providing the goblin model.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("ScoutingNinja for providing the shield model that would be used for the waypoint.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("Thanks to the staff of Ragnorok online for there sound effect files.\n");
    ((CEGUI::MultiLineEditbox*)credits)->appendText("And finally thanks to Professor Don Fussell for giving us the opportunity and knowledge needed to create this game.\n");


#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif
} // show

void CreditPage::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hide

bool CreditPage::backEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().mainMenu->show();
    return false;
} // backEvent



