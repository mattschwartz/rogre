#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

/**
 * Included files
 */
#include <Ogre.h>

class Player;

/**
 * Data
 */
class MainMenu {
private:
    bool visible;
    MainMenu() {}
    MainMenu(MainMenu const&);
    void operator=(MainMenu const&);

public:
    static MainMenu &getInstance() {
        static MainMenu instance;
        return instance;
    } // getInstance

    void init();
    void update();
    bool isVisible();
    void show();
    void hide();
    void loadPlayer(Player *player);
};

#endif
