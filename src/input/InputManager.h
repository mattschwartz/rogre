#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

/**
 * Included files
 */
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "src/main/BaseApplication.h"

class InputManager {
private:
    bool mShutDown;
    InputManager() {}
    InputManager(InputManager const&);
    void operator=(InputManager const&);

public:
    static InputManager &getInstance() {
        static InputManager instance;
        return instance;
    } // getInstance
    
    void init();
    void keyPressed(const OIS::KeyEvent &arg);
    void keyReleased(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &arg);
    void mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void shutDown();
    bool shouldShutDown();
};

#endif
