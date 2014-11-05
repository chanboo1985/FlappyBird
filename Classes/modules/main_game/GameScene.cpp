#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vect(0,-900));
	auto bgLayer = BackGroundLayer::create();
	if (bgLayer)
	{
		this->addChild(bgLayer);
	}

	auto statusLayer = StatusLayer::create();

	auto gameLayer = GameLayer::create();
	if (gameLayer)
	{
		gameLayer->setPhysicalWorld(this->getPhysicsWorld());
		gameLayer->setDelegator(statusLayer);
		this->addChild(gameLayer);
	}

	if (statusLayer)
	{
		this->addChild(statusLayer);
	}

	auto optionLayer = OptionLayer::create();
	if (optionLayer)
	{
		optionLayer->setDelegator(gameLayer);
		this->addChild(optionLayer);
	}

	return true;
}

void GameScene::restart()
{
	this->removeAllChildrenWithCleanup(true);
	this->init();
}