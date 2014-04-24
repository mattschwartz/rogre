#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

/**
 * Included files
 */
#include <OISKeyboard.h>
#include <OISMouse.h>

class InputManager {
private:
    InputManager() {}
    InputManager(InputManager const&);
    void operator=(InputManager const&);

public:
    static InputManager &getInstance() {
        static InputManager instance;
        return instance;
    } // getInstance
    
    void keyPressed(const OIS::KeyEvent &arg);
    void keyReleased(const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &arg);
    void mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
};

#endif
