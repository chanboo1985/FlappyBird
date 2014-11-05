#include "LoadingScene.h"

LoadingScene::LoadingScene()
{

}

LoadingScene::~LoadingScene()
{

}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	return true;
}

void LoadingScene::onEnter()
{
	auto director = Director::getInstance();
	Sprite* background = Sprite::create("splash.png");
	cocos2d::Size visibleSize = director->getVisibleSize();
	cocos2d::Point origin = director->getVisibleOrigin();
	background->setPosition(origin.x + visibleSize.width/2,origin.y + visibleSize.height/2);
	this->addChild(background);

	director->getTextureCache()->addImageAsync("atlas.png",CC_CALLBACK_1(LoadingScene::loadingCallBack,this));
}

void LoadingScene::loadingCallBack(Texture2D *texture)
{
	ResourceLoader::getInstance()->loadResource("atlas.txt",texture);

	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");

	auto scene = WelcomeScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}