#include "WelcomeScene.h"

WelcomeScene::WelcomeScene()
{
}

WelcomeScene::~WelcomeScene()
{
}

bool WelcomeScene::init()
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());
		auto layer = WelcomeLayer::create();
		CC_BREAK_IF(!layer);
		this->addChild(layer);
		ret = true;
	} while (0);
	return ret;
}