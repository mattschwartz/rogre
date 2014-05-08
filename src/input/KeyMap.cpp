#include "KeyHandler.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/OptionsMenu.h"
#include "src/world/World.h"

void KeyMap::openInventory(void) { 
}

void KeyMap::openAttributes(void) {
}

void KeyMap::toggleOptionsMenu(void) {
    if (World::getInstance().getPlayerObject() != NULL) {
        GUIManager::getInstance().optionsMenu->toggle();
    } // if
} // toggleOptionsMenu
