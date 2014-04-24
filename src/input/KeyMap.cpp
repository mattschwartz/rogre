#include "KeyHandler.h"
#include "src/gui/GUIManager.h"
#include "src/gui/menu/OptionsMenu.h"

void KeyMap::openInventory(void) { 
}

void KeyMap::openAttributes(void) {
}

void KeyMap::toggleSound(void) {
    SoundManager::getInstance().toggleSound();
} // toggleSound

void KeyMap::toggleOptionsMenu(void) {
    GUIManager::getInstance().optionsMenu->toggle();
} // toggleOptionsMenu
