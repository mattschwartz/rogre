#ifndef _INFO_LOG_PANEL_H_
#define _INFO_LOG_PANEL_H_

/**
 * Included files
 */
#include "CEGUI/CEGUI.h"
#include "src/main/BaseApplication.h"

class Player;

class InfoLogPanel {
private:
    bool visible;
    CEGUI::Window *mRoot;
    CEGUI::WindowManager &windowManager;
    CEGUI::MultiLineEditbox *textLog;
    CEGUI::PushButton *toggleLogButton;
    CEGUI::PushButton *clearButton;
    void createWidgets();
    void registerEvents();
    bool toggleLogEvent(const CEGUI::EventArgs &e);
    bool clearEvent(const CEGUI::EventArgs &e);

public:
    InfoLogPanel();
    ~InfoLogPanel();
    void append(std::string text);
    void appendLine(std::string text);
    void addPanelTo(CEGUI::Window *mRoot);
    void loadPlayer(Player *player);
};

#endif
