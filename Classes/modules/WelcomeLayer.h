#ifndef __WELCOME_LAYER_H__
#define __WELCOME_LAYER_H__
#include <cocos2d.h>
#include "ResourceLoader.h"
#include "FlappyBird.h"
#include "SimpleAudioEngine.h"
#include "main_game/GameScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

const int START_BUTTON_TAG = 100;

class WelcomeLayer:public Layer
{
public:
	WelcomeLayer(){}
	~WelcomeLayer(){}
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	void onEnter() override;
private:
	void menuStartCallback(Object *sender);
	void scrollLand(float dt);
	Sprite *land_1;
	Sprite *land_2;
	FlappyBird *bird;
};


#endif