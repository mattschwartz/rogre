/**
 * Included files
 */
#include "LoadPlayerMenu.h"
#include "src/utility/GUIHelper.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/MainMenu.h"
#include "src/sound/SoundEffect.h"
#include "src/sound/SoundManager.h"
#include "src/utility/filesys/FileManager.h"

LoadPlayerMenu::LoadPlayerMenu() :
    windowManager(CEGUI::WindowManager::getSingleton()) {
    createWidgets();
    createRootWindow();
    registerEvents();
} // constructor

void LoadPlayerMenu::createWidgets() {
    using namespace CEGUI;

    titleLabel = windowManager.createWindow("OgreTray/Title", "LoadPlayerMenu/titleLabel");
    playerSaveListbox = static_cast<Listbox*>(
        windowManager.createWindow("OgreTray/Listbox", "LoadPlayerMenu/playerSaveListbox"));
    backButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "LoadPlayerMenu/backButton"));
    deleteSaveButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "LoadPlayerMenu/deleteSaveButton"));
    loadSaveButton = static_cast<PushButton*>(
        windowManager.createWindow("OgreTray/Button", "LoadPlayerMenu/loadSaveButton"));

#if USE_OGRE_LEGACY
    Imageset& MenuImage =ImagesetManager::getSingleton().createFromImageFile("Background", "main_menu_bg.jpg");
    backgroundWindow = windowManager.createWindow("OgreTray/StaticImage", "LoadPlayerMenu/backgroundWindow");
    backgroundWindow->setProperty("Image", "set:Background image:full_image");
#endif

    titleLabel->setSize(SIZE(0.0f, 300.0f, 0.0f, 40.0f));
    titleLabel->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -250.0f)));
    titleLabel->setText("Load Player");
    titleLabel->setAlwaysOnTop(true);

    playerSaveListbox->setSize(SIZE(0.0f, 300.0f, 0.0f, 400.0f));
    playerSaveListbox->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, -200.0f)));
    playerSaveListbox->setAlwaysOnTop(true);

    backButton->setSize(SIZE(0.0f, 100.0f, 0.0f, 40.0f));
    backButton->setPosition(UVector2(UDim(0.5f, -150.0f), UDim(0.5f, 200.0f)));
    backButton->setText("Back");
    backButton->setAlwaysOnTop(true);

    deleteSaveButton->setSize(SIZE(0.0f, 100.0f, 0.0f, 40.0f));
    deleteSaveButton->setPosition(UVector2(UDim(0.5f, -50.0f), UDim(0.5f, 200.0f)));
    deleteSaveButton->setText("Delete");
    deleteSaveButton->setEnabled(false);
    deleteSaveButton->setAlwaysOnTop(true);

    loadSaveButton->setSize(SIZE(0.0f, 100.0f, 0.0f, 40.0f));
    loadSaveButton->setPosition(UVector2(UDim(0.5f, 50.0f), UDim(0.5f, 200.0f)));
    loadSaveButton->setText("Load");
    loadSaveButton->setEnabled(false);
    loadSaveButton->setAlwaysOnTop(true);
} // createWidgets

void LoadPlayerMenu::createRootWindow() {
    using namespace CEGUI;

    mRoot = windowManager.createWindow("DefaultWindow", "LoadPlayerMenu/root");

#if USE_OGRE_LEGACY
    mRoot->addChildWindow(backgroundWindow);
    mRoot->addChildWindow(titleLabel);
    mRoot->addChildWindow(playerSaveListbox);
    mRoot->addChildWindow(backButton);
    mRoot->addChildWindow(deleteSaveButton);
    mRoot->addChildWindow(loadSaveButton);
#else
    mRoot->addChild(backgroundWindow);
    mRoot->addChild(titleLabel);
    mRoot->addChild(playerSaveListbox);
    mRoot->addChild(backButton);
    mRoot->addChild(deleteSaveButton);
    mRoot->addChild(loadSaveButton);
#endif
} // createRootWindow

void LoadPlayerMenu::registerEvents() {
    using namespace CEGUI;
    
    playerSaveListbox->subscribeEvent(Listbox::EventMouseClick,
        Event::Subscriber(&LoadPlayerMenu::saveListSelectionChanged, this));
    backButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&LoadPlayerMenu::backEvent, this));
    deleteSaveButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&LoadPlayerMenu::loadSaveEvent, this));
    loadSaveButton->subscribeEvent(PushButton::EventClicked, 
        Event::Subscriber(&LoadPlayerMenu::deleteSaveEvent, this));
} // registerEvents

void LoadPlayerMenu::show() {
    using namespace CEGUI;

    std::set<std::string> savefiles = FileManager::getInstance().getLoadablePlayers();

    for (std::string str : savefiles) {
        ListboxTextItem *lbi = new ListboxTextItem(str);

#if USE_OGRE_LEGACY
        lbi->setTextColours(colour(0.0f, 0.0f, 0.0f));
#else
        lbi->setTextColours(Colour(0.0f, 0.0f, 0.0f));
#endif
        playerSaveListbox->addItem(lbi);
        playerSaveListbox->setItemSelectState(lbi, false);
        playerSaveListbox->ensureItemIsVisible(lbi);
    } // for

    playerSaveListbox->setMultiselectEnabled(false);

#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(mRoot);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
#endif
} // show

void LoadPlayerMenu::hide() {
#if USE_OGRE_LEGACY
    CEGUI::System::getSingleton().setGUISheet(NULL);
#else
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(NULL);
#endif
} // hide

bool LoadPlayerMenu::backEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    GUIManager::getInstance().mainMenu->show();
    return false;
} // backEvent

bool LoadPlayerMenu::saveListSelectionChanged(const CEGUI::EventArgs &e) {
    using namespace CEGUI;
    
    deleteSaveButton->setEnabled(false);
    loadSaveButton->setEnabled(false);
    for (int i = 0, len = playerSaveListbox->getItemCount(); i < len; i++) {
        ListboxTextItem *lbti = (ListboxTextItem*)playerSaveListbox->getListboxItemFromIndex(i);

        if (lbti != NULL) {
            if (lbti->isSelected()) {
                deleteSaveButton->setEnabled(true);
                loadSaveButton->setEnabled(true);
#if USE_OGRE_LEGACY
                lbti->setTextColours(colour(1.0f, 1.0f, 0.0f));
#else
                lbti->setTextColours(Colour(1.0f, 1.0f, 0.0f));
#endif
            } // if
            else {
#if USE_OGRE_LEGACY
                lbti->setTextColours(colour(0.0f, 0.0f, 0.0f));
#else
                lbti->setTextColours(Colour(0.0f, 0.0f, 0.0f));
#endif
            } // else
        } // if
    } // for

    playerSaveListbox->invalidate(true);
    return false;
} // saveListSelectionChanged

bool LoadPlayerMenu::deleteSaveEvent(const CEGUI::EventArgs &e) {
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    return false;
} // deleteSaveEvent

bool LoadPlayerMenu::loadSaveEvent(const CEGUI::EventArgs &e) {
    std::string str;
    Player *player;
    
    SoundManager::getInstance().MENU_SELECT_SOUND->play();
    if (playerSaveListbox->getFirstSelectedItem() == NULL) {
        return false;
    } // if
    
    str = playerSaveListbox->getFirstSelectedItem()->getText().c_str();

    player = FileManager::getInstance().loadPlayer(str);
    return false;
} // loadSaveEvent
