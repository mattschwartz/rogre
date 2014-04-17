#ifndef _PLAYER_GUI_H_
#define _PLAYER_GUI_H_

/**
 * Included files
 */
#include <Ogre.h>

class InventoryPanel;
class AttributesPanel;
class EquipmentPanel;
class MessageLogPanel;

/**
 * Data
 */
class PlayerGUI {
private:
    InventoryPanel *inventoryPanel;
    AttributesPanel *attributesPanel;
    EquipmentPanel *equipmentPanel;
    MessageLogPanel *messageLogPanel;
    PlayerGUI() {}
    PlayerGUI(PlayerGUI const&);
    void operator=(PlayerGUI const&);

public:
    static PlayerGUI &getInstance() {
        static PlayerGUI instance;
        return instance;
    } // getInstance

    void init();
    void update();
};

#endif
