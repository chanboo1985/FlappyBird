#include "FlappyBird.h"

FlappyBird* FlappyBird::shareFlappyBird = nullptr;

FlappyBird* FlappyBird::getInstance()
{
	if (shareFlappyBird == NULL)
	{
		shareFlappyBird = new FlappyBird();
		if (!shareFlappyBird->init())
		{
			delete shareFlappyBird;
			shareFlappyBird = NULL;
		}
	}
	return shareFlappyBird;
}

bool FlappyBird::init()
{
	this->isFirstTime = 3;
	return true;
}

bool FlappyBird::createFlappyBird()
{
	this->createFlappyBirdByRandom();
	if (Sprite::initWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName(birdName)))
	{
		Animation *animation = this->createAniamtion(this->birdNameFormat.c_str(),3,10);
		Animate *animate = Animate::create(animation);
		this->idleAction = RepeatForever::create(animate);
		ActionInterval *up = CCMoveBy::create(0.4f,Point(0,8));
		ActionInterval *upBack = up->reverse();
		this->swingAction = RepeatForever::create(Sequence::create(up,upBack,NULL));
		return true;
	}
	return false;
}

void FlappyBird::idle()
{
	if (changeState(ACTION_STATE_IDLE)) {
		this->runAction(idleAction);
		this->runAction(swingAction);
	}
}

void FlappyBird::fly()
{
	if(changeState(ACTION_STATE_FLY)) {
		this->stopAction(swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

void FlappyBird::die()
{
	if(changeState(ACTION_STATE_DIE)) {
		this->stopAllActions();
	}
}

Animation* FlappyBird::createAniamtion(const char *fmt, int count ,float fps)
{
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(1/fps);
	for (int i = 0; i < count; i++){
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *frame = ResourceLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

void FlappyBird::createFlappyBirdByRandom()
{
	if (this->isFirstTime & 1)
	{
		this->isFirstTime &= 2;
	} 
	else if(this->isFirstTime & 2)
	{
		this->isFirstTime &= 1;
		return;
	}
	srand((unsigned)time(NULL));
	int type = ((int)rand()) % 3;
	switch (type)
	{
	case 0:
		this->birdName = "bird0_0";
		this->birdNameFormat = "bird0_%d";
		break;
	case 1:
		this->birdName = "bird1_0";
		this->birdNameFormat = "bird1_%d";
		break;
	case 2:
		this->birdName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	default:
		this->birdName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	}
}

bool FlappyBird::changeState(ActionState state)
{
	currentStatus = state;
	return true;
}