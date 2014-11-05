#include "WelcomeLayer.h"

bool WelcomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void WelcomeLayer::onEnter()
{
	Layer::onEnter();
	auto director = Director::getInstance();
	Size visibleSize = director->getVisibleSize();
	Point origin = director->getVisibleOrigin();
	//计算时间
	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;
	//增加背景层
	Sprite *bg;
	if (hour >= 6 && hour <= 17)
	{
		bg = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("bg_day"));
	} 
	else
	{
		bg = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(Point::ZERO);
	this->addChild(bg);
	//增加游戏名称
	Sprite *title = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("title"));
	title->setPosition(Point(origin.x + visibleSize.width/2,(visibleSize.height*5)/7));
	this->addChild(title);
	//开始按钮
	Sprite *btn_normal = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite *btn_active = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("button_play"));
	btn_active->setPositionY(5);
	auto menuItem = MenuItemSprite::create(btn_normal,btn_active,CC_CALLBACK_1(WelcomeLayer::menuStartCallback,this));
	menuItem->setPosition(Point(origin.x + visibleSize.width/2,visibleSize.height*2/5));
	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(origin.x,origin.y));
	this->addChild(menu,1);
	//增加鸟
	this->bird = FlappyBird::getInstance();
	this->bird->createFlappyBird();
	this->bird->setTag(BIRD_SPRITE_TAG);
	this->bird->setPosition(Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height*3/5 - 10));
	this->bird->idle();
	this->addChild(this->bird);

	//add land_1
	this->land_1 = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("land"));
	this->land_1->setAnchorPoint(Point::ZERO);
	this->land_1->setPosition(Point::ZERO);
	this->addChild(land_1);
	//add land_2
	this->land_2 = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("land"));
	this->land_2->setAnchorPoint(Point::ZERO);
	this->land_2->setPosition(Point(this->land_1->getContentSize().width - 2.0f, 0));
	this->addChild(land_2);

	//计时器
	this->schedule(schedule_selector(WelcomeLayer::scrollLand),0.01f);

	Sprite *copyright = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
	copyright->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/6));
	this->addChild(copyright);
}

void WelcomeLayer::menuStartCallback(Object *sender)
{
	CCLOG("------------start game--------------");
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	//开始游戏
	auto gameScene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, gameScene);
	Director::getInstance()->replaceScene(transition);
}

void WelcomeLayer::scrollLand(float dt)
{
	this->land_1->setPositionX(this->land_1->getPositionX() - 2.0f);
	this->land_2->setPositionX(this->land_1->getPositionX() + this->land_1->getContentSize().width - 2.0f);

	if(this->land_2->getPositionX() == 0) {
		this->land_1->setPositionX(0);
	}
}