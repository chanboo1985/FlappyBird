#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__
#include <cocos2d.h>
#include "WelcomeLayer.h"
using namespace cocos2d;

class WelcomeScene :public Scene
{
public:
	WelcomeScene();
	~WelcomeScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
};

#endif