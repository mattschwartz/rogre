/**
 *  Note: Code modified from the Ogre Tutorial Framework
 *  http://www.ogre3d.org/tikiwiki/
 */
#ifndef _MAIN_H_
#define _MAIN_H_

#include "BaseApplication.h"

class MainApplication : public BaseApplication
{
public:
    MainApplication();
    virtual ~MainApplication();

protected:
    virtual void createScene();
};

#endif // #ifndef __TutorialApplication_h_
