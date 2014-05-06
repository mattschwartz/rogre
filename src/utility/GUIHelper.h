#ifndef _GUI_HELPER_H_
#define _GUI_HELPER_H_

/**
 * Included files
 */
#include "CEGUI/CEGUI.h"

/**
 * Defines
 */
#if USE_OGRE_LEGACY
    #define SIZE(x, xf, y, yf) (CEGUI::UVector2(CEGUI::UDim(x, xf), CEGUI::UDim(y, yf)))
#else
    #define SIZE(x, xf, y, yf) (CEGUI::USize(CEGUI::UDim(x, xf), CEGUI::UDim(y, yf)))
#endif
#define POS(x, xf, y, yf) (CEGUI::UVector2(CEGUI::UDim(x, xf), CEGUI::UDim(y, yf)))

#endif
