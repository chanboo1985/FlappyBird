#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include <cocos2d.h>
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "OptionLayer.h"
#include "StatusLayer.h"
using namespace cocos2d;

class GameScene : public Scene
{
public:
	GameScene(){}

	~GameScene(){}

	virtual bool init();

	CREATE_FUNC(GameScene);

	void restart();
};

#endif