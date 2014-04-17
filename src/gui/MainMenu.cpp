/**
 * Included files
 */
#include "MainMenu.h"
#include "src/entities/player/Player.h"

void MainMenu::init() {
    visible = false;
} // init

bool MainMenu::isVisible() {
    return visible;
} // isVisible;

void MainMenu::show() {
    visible = true;
} // show

void MainMenu::hide() {
    visible = false;
} // hide

void MainMenu::loadPlayer(Player *player) {
} // loadPlayer
