#ifndef _NEW_PLAYER_MENU_H_
#define _NEW_PLAYER_MENU_H_

/**
 * Included files
 */
#include "CEGUI/CEGUI.h"
#include <string>

#if !USE_OGRE_LEGACY
    #include <boost/thread/thread.hpp>
    #include <boost/thread/mutex.hpp>
    #include <boost/shared_ptr.hpp>
#endif

class NewPlayerMenu {
private:
    std::string playerName;
    CEGUI::WindowManager &windowManager;
    CEGUI::Window *mRoot;
    CEGUI::Window *titleLabel;
    CEGUI::Window *textLabel;
    CEGUI::Window *playerNameTextField;
    CEGUI::PushButton *backButton;
    CEGUI::PushButton *startGameButton;
    void createWidgets();
    void createRootWindow();
    void registerEvents();
    bool backEvent(const CEGUI::EventArgs &e);
    bool startGameEvent(const CEGUI::EventArgs &e);

#if !USE_OGRE_LEGACY
    void runThread();
#endif

public:
#if !USE_OGRE_LEGACY
    boost::shared_ptr<boost::thread> mThread;
#endif

    NewPlayerMenu();
    ~NewPlayerMenu();
    void show();
    void hide();
};

#endif
