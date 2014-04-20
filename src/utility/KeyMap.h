#ifndef _KEY_MAP_H_
#define _KEY_MAP_H_

/**
 * Included files
 */
#include <map>
#include <OISKeyboard.h>
#include "src/sound/SoundManager.h"

namespace KeyMap {
	typedef void (*func)();
	typedef std::map<OIS::KeyCode, func> key_map;
	static key_map keys;

	void openInventory(void);
	void openAttributes(void);
	void toggleSound(void);
};

#endif
