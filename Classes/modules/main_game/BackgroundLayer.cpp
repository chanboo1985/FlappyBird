#include "BackgroundLayer.h"

bool BackGroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	time_t t = time(nullptr);
	tm *lt = localtime(&t);
	int hour = lt->tm_hour;
	Sprite *bg;
	if (hour >= 6 && hour <= 17)
	{
		bg = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("bg_day"));
	}else
	{
		bg = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(Point::ZERO);
	this->addChild(bg);

	return true;
}

float BackGroundLayer::getLandHeight()
{
	return Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}