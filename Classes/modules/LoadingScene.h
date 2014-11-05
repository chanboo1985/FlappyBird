#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__
#include <cocos2d.h>
#include "ResourceLoader.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
using namespace cocos2d;
using namespace CocosDenshion;

class LoadingScene :public Scene
{
public:
	LoadingScene();
	~LoadingScene();

	virtual bool init();
	CREATE_FUNC(LoadingScene);
	void onEnter() override;
private:
	void loadingCallBack(Texture2D *texture); 
};


#endif