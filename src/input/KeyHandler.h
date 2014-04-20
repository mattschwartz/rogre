#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

/**
 * Included files
 */
#include <map>
#include "src/utility/KeyMap.h"

class KeyHandler {
private:
    KeyHandler() {}
    KeyHandler(KeyHandler const&);
    void operator=(KeyHandler const&);

public:
    static KeyHandler &getInstance() {
        static KeyHandler instance;
        return instance;
    } // getInstance

	void init() {
		using namespace KeyMap;
		
		//keys.insert(std::make_pair(OIS::KC_I, &openInventory));
		//keys.insert(std::make_pair(OIS::KC_C, &openAttributes));
		//keys.insert(std::make_pair(OIS::KC_F12, &toggleSound));
		
		keys[OIS::KC_I] = &openInventory;
		keys[OIS::KC_C] = &openAttributes;
		keys[OIS::KC_F12] = &toggleSound;
	} // init

	void invoke(OIS::KeyCode c) {
		using namespace KeyMap;

		func f = keys[c];
		(*f)();

		/*
		key_map::iterator iter = keys.find(c);

		if (iter != keys.end()) {
			((iter->second))();
		} // if
		*/
	} // invoke
};

#endif
