#include "Number.h"

bool NumberSeries::init()
{
	this->numberSeries = Vector<SpriteFrame*>(10);
	return true;
}

void NumberSeries::loadNumber(const char *fmt, int base /* = 0 */)
{
	for (int i = base; i < NUMBER_MAX + base; i++)
	{
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *spriteFrame = ResourceLoader::getInstance()->getSpriteFrameByName(filename);
		numberSeries.pushBack(spriteFrame);
	}
}

SpriteFrame* NumberSeries::at(int index)
{
	return numberSeries.at(index);
}

Number* Number::sharedNumber = nullptr;
Number* Number::getInstance()
{
	if (sharedNumber == NULL)
	{
		sharedNumber = new Number();
		if (!sharedNumber->init())
		{
			delete sharedNumber;
			sharedNumber = NULL;
		}
	}
	return sharedNumber;
}

bool Number::init()
{
	return true;
}

bool Number::loadNumber(const char *name, const char *fmt, int base /* = 0 */)
{
	auto numberSeries = NumberSeries::create();
	numberSeries->loadNumber(fmt, base);
	numberContainer.insert(name, numberSeries);
	return true;
}

Node* Number::convert(const char *name, int number, Gravity gravity /* = Gravity::GRAVITY_CENTER */)
{
	auto numbers = numberContainer.at(name);
	if (number == 0)
	{
		auto numberZero = Sprite::createWithSpriteFrame(numbers->at(0));
		numberZero->setAnchorPoint(Point(0.5,0));
		return numberZero;
	}
	auto numberNode = Node::create();
	float totalWidth = 0;
	while (number)
	{
		int temp = number % NUMBER_MAX;
		number /= NUMBER_MAX;
		auto sprite = Sprite::createWithSpriteFrame(numbers->at(temp));
		totalWidth += sprite->getContentSize().width;
		numberNode->addChild(sprite);
	}
	int index;
	float numberWidth,numberHeight,offsetWidth;
	numberHeight = Sprite::createWithSpriteFrame(numbers->at(0))->getContentSize().height;
	numberNode->setContentSize(Size(totalWidth, numberHeight));

	numberWidth = totalWidth / numberNode->getChildrenCount();

	switch (gravity)
	{
	case Gravity::GRAVITY_LEFT:
		index = 0;
		for (auto child : numberNode->getChildren())
		{
			child->setAnchorPoint(Point(0,0));
			offsetWidth = numberWidth*index++;
			child->setPositionX(offsetWidth);
		}
		break;
	case Gravity::GRAVITY_CENTER:
		index = numberNode->getChildrenCount()/2;
		for (auto child : numberNode->getChildren())
		{
			child->setAnchorPoint(Point(0.5,0));
			offsetWidth = numberWidth*index--;
			child->setPositionX(offsetWidth);
		}
		break;
	case Gravity::GRAVITY_RIGHT:
		index = numberNode->getChildrenCount();
		for (auto child : numberNode->getChildren())
		{
			child->setAnchorPoint(Point(1,0));
			offsetWidth = numberWidth*index--;
			child->setPositionX(offsetWidth);
		}
		break;
	default:
		index = numberNode->getChildrenCount()/2;
		for (auto child : numberNode->getChildren())
		{
			child->setAnchorPoint(Point(0.5,0));
			offsetWidth = numberWidth*index--;
			child->setPositionX(offsetWidth);
		}
		break;
	}
	
	return numberNode;
}