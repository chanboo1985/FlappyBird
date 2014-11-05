#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	this->gameStatus = GAME_STATUS_READY;
	this->score = 0;

	//添加Flappy Bird
	this->bird = FlappyBird::getInstance();
	this->bird->createFlappyBird();
	PhysicsBody *body = PhysicsBody::create();
	body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(false);
	body->setContactTestBitmask(-1);
	this->bird->setPhysicsBody(body);
	this->bird->setPosition(Point(origin.x + visibleSize.width/3 - 5, origin.y + visibleSize.height/2 + 5));
	this->bird->idle();
	this->addChild(this->bird);

	//add ground
	this->groundNode = Node::create();
	float landHeight = BackGroundLayer::getLandHeight();
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(288,landHeight)));
	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	groundBody->setContactTestBitmask(-1);
	this->groundNode->setPhysicsBody(groundBody);
	this->groundNode->setPosition(144,landHeight/2);
	this->addChild(groundNode);

	//add land
	this->land_1 = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("land"));
	this->land_1->setAnchorPoint(Point::ZERO);
	this->land_1->setPosition(Point::ZERO);
	this->addChild(land_1,30);

	this->land_2 = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("land"));
	this->land_2->setAnchorPoint(Point::ZERO);
	this->land_2->setPosition(Point(this->land_2->getContentSize().width - 2.0f, 0));
	this->addChild(this->land_2, 30);

	////add timer
	this->shiftLand = schedule_selector(GameLayer::scrollLand);
	this->schedule(shiftLand, 0.01f);

	this->scheduleUpdate();

	//碰撞监听，所有带有物理属性的必须要加上setContactTestBitmask(-1)，否则监听无效
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool GameLayer::onContactBegin(const PhysicsContact& contact) {
	this->gameOver();
	return true;
}

void GameLayer::onTouch()
{
	if (this->gameStatus == GAME_STATUS_OVER)
	{
		return;
	}

	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if (this->gameStatus == GAME_STATUS_READY)
	{
		this->delegator->onGameStart();
		this->bird->fly();
		this->gameStatus = GAME_STATUS_START;
		this->createPips();
	} 
	else if(this->gameStatus == GAME_STATUS_START)
	{
		this->bird->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

void GameLayer::update(float deta)
{
	if (this->gameStatus == GAME_STATUS_START)
	{
		this->rotateBird();
		this->checkHit();
	}
}

void GameLayer::rotateBird()
{
	float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
	this->bird->setRotation(min(max(-90, (verticalSpeed*0.2 + 60)) ,30));
}

void GameLayer::createPips()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < PIP_COUNT; i++)
	{
		Sprite *pipUp = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		Sprite *pipDown = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("pipe_down"));
		Node *signlePip = Node::create();

		pipDown->setPosition(0,PIP_HEIGHT + PIP_DISTANCE);
		signlePip->addChild(pipUp, 0, UP_PIP);
		signlePip->addChild(pipDown, 0, DOWN_PIP);
		signlePip->setPosition(visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());
		auto body = PhysicsBody::create();
		auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIP_HEIGHT + PIP_DISTANCE));
		body->addShape(shapeBoxDown);
		body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
		body->setDynamic(false);
		body->setContactTestBitmask(-1);
		signlePip->setPhysicsBody(body);
		signlePip->setTag(PIP_NEW);

		this->addChild(signlePip);
		this->pips.push_back(signlePip);
	}
}

int GameLayer::getRandomHeight()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

void GameLayer::checkHit()
{
	for (auto pipe : this->pips)
	{
		if (pipe->getTag() == PIP_NEW)
		{
			if (this->bird->getPositionX() >= pipe->getPositionX() + PIP_WIDTH)
			{
				SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
				this->score++;
				this->delegator->onGamePlaying(score);
				pipe->setTag(PIP_PASS);
			}
		}
	}
}

void GameLayer::birdSpriteFadeOut()
{
	FadeOut* animation = FadeOut::create(1.5);
	CallFunc* animationDone = CallFunc::create(std::bind(&GameLayer::birdSpriteRemove,this));
	Sequence* sequence = Sequence::createWithTwoActions(animation,animationDone);
	this->bird->stopAllActions();
	this->bird->runAction(sequence);
}

void GameLayer::birdSpriteRemove()
{
	this->bird->setRotation(0);
	this->removeChild(this->bird);
}

void GameLayer::scrollLand(float dt)
{
	this->land_1->setPositionX(this->land_1->getPositionX() - 2.0f);
	this->land_2->setPositionX(this->land_1->getPositionX() + this->land_1->getContentSize().width - 2.0f);
	if (this->land_2->getPositionX() == 0)
	{
		this->land_1->setPositionX(0);
	}

	//移动水管
	for (auto pipe : this->pips)
	{
		pipe->setPositionX(pipe->getPositionX() - 2.0f);
		if (pipe->getPositionX() < -PIP_WIDTH)
		{
			pipe->setTag(PIP_NEW);
			pipe->setPositionX(Director::getInstance()->getVisibleSize().width);
			pipe->setPositionY(this->getRandomHeight());
		}
	}
}

void GameLayer::gameOver()
{
	if (this->gameStatus == GAME_STATUS_OVER)
	{
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");

	//record score
	int bestScore = UserRecord::getInstance()->getIntegerFromUserDefault("best_score");
	if (this->score > bestScore)
	{
		UserRecord::getInstance()->saveIntegerToUserDefault("best_score", this->score);
	}
	this->delegator->onGameEnd(this->score, bestScore);

	this->unschedule(shiftLand);
	SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
	this->bird->die();
	this->bird->setRotation(-90);
	this->birdSpriteFadeOut();
	this->gameStatus = GAME_STATUS_OVER;
}