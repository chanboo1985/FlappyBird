#include "StatusLayer.h"

bool StatusLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->bestScore = 0;
	this->currentScore = 0;
	this->isNewRecord = false;
	Number::getInstance()->loadNumber(NUMBER_FONT.c_str(),"font_0%02d",48);
	Number::getInstance()->loadNumber(NUMBER_SCORE.c_str(),"number_score_%02d");
	this->showReadyStatus();
	this->loadWhiteSprite();
	return true;
}

void StatusLayer::onGameStart()
{
	this->showStartStatus();
}

void StatusLayer::onGamePlaying(int score)
{
	this->removeChild(scoreSprite);
	scoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_FONT.c_str(), score);
	scoreSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*5/6));
	this->addChild(scoreSprite);
}

void StatusLayer::onGameEnd(int curScore, int bestScore)
{
	this->showOverStatus(curScore,bestScore);
}

void StatusLayer::showReadyStatus()
{
	scoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_FONT.c_str(), 0);
	scoreSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*5/6));
	this->addChild(scoreSprite);

	getreadySprite = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("text_ready"));
	getreadySprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*2/3));
	this->addChild(getreadySprite);

	tutorialSprite = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("tutorial"));
	tutorialSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*1/2));
	this->addChild(tutorialSprite);
}

void StatusLayer::loadWhiteSprite()
{
	whiteSprite = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("white"));
	whiteSprite->setScale(100);
	whiteSprite->setOpacity(0);
	this->addChild(whiteSprite,10000);
}

void StatusLayer::showStartStatus()
{
	this->getreadySprite->runAction(FadeOut::create(0.4f));
	this->tutorialSprite->runAction(FadeOut::create(0.04f));
}

void StatusLayer::showOverStatus(int curScore, int bScore)
{
	this->currentScore = curScore;
	this->bestScore = bScore;
	if (curScore > bScore)
	{
		this->bestScore = curScore;
		this->isNewRecord = true;
	}else
	{
		this->isNewRecord = false;
	}
	this->removeChild(scoreSprite);
	this->blinkFullScreen();
}

void StatusLayer::blinkFullScreen()
{
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn,fadeOut,NULL);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
	auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
	whiteSprite->stopAllActions();
	whiteSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver()
{
	// create the game over panel
	Sprite* gameoverSprite = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameoverSprite->setPosition(Point(this->origin.x + this->visibleSize.width / 2, this->origin.y + this->visibleSize.height *2/3));
	this->addChild(gameoverSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);

	// Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
	auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
	gameoverSprite->stopAllActions();
	gameoverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel()
{
	// create the score panel
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorepanelSprite->setPosition(Point(this->origin.x + this->visibleSize.width / 2, this->origin.y - scorepanelSprite->getContentSize().height));
	this->addChild(scorepanelSprite);

	//display the  best score on the score panel
	auto bestScoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->bestScore, Gravity::GRAVITY_RIGHT);
	bestScoreSprite->setAnchorPoint(Point(1, 1));
	bestScoreSprite->setPosition(scorepanelSprite->getContentSize().width - 28 ,50);
	scorepanelSprite->addChild(bestScoreSprite);

	string medalsName = this->getMedalsName(currentScore);
	if(medalsName != "") {
		Sprite* medalsSprite = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName(medalsName));
		medalsSprite->addChild(this->blink);
		medalsSprite->setPosition(54, 58);
		scorepanelSprite->addChild(medalsSprite);
	}

	if(this->isNewRecord){
		Sprite* newTagSprite = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("new"));
		newTagSprite->setPosition(-16, 12);
		bestScoreSprite->addChild(newTagSprite);
	}

	// Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f ,Point(this->origin.x + this->visibleSize.width / 2,this->origin.y + this->visibleSize.height/2 - 10.0f));
	// add variable motion for the action
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
	scorepanelSprite->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	scorepanelSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn()
{
	Node * tmpNode = Node::create();

	//create the restart menu;
	Sprite* restartBtn = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* restartBtnActive = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("button_play"));
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(this->origin.x + this->visibleSize.width / 2 - restartBtn->getContentSize().width / 2, this->origin.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(menu);


	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("button_score"));
	rateBtn->setPosition(Point(this->origin.x + this->visibleSize.width / 2 + rateBtn->getContentSize().width / 2, this->origin.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(rateBtn);
	this->addChild(tmpNode);

	//fade in the two buttons
	auto fadeIn = FadeIn::create(0.1f);
	//tmpNode->stopAllActions();
	//tmpNode->runAction(fadeIn);

	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::refreshScoreCallback,this));
	auto sequence = Sequence::createWithTwoActions(fadeIn,actionDone);
	tmpNode->stopAllActions();
	tmpNode->runAction(sequence);
}

void StatusLayer::menuRestartCallback(Object* pSender){
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void StatusLayer::refreshScoreCallback(){
	this->tmpScore = 0;
	schedule(schedule_selector(StatusLayer::refreshScoreExecutor),0.1f);
}

void StatusLayer::refreshScoreExecutor(float dt){
	if(this->getChildByTag(CURRENT_SCORE_SPRITE_TAG)){
		this->removeChildByTag(CURRENT_SCORE_SPRITE_TAG);
	}
	scoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->tmpScore, Gravity::GRAVITY_RIGHT);
	scoreSprite->setAnchorPoint(Point(1,0));
	scoreSprite->setPosition(Point(this->origin.x + this->visibleSize.width * 3 / 4 + 20.0f, this->origin.y + this->visibleSize.height *  1 / 2));
	scoreSprite->setTag(CURRENT_SCORE_SPRITE_TAG);
	this->addChild(scoreSprite,1000);
	this->tmpScore++;
	if(this->tmpScore > this->currentScore){
		unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
	}
}

string StatusLayer::getMedalsName(int cScore)
{
	this->setBlinkSprite();
	string medalsName = "";
	if (cScore >= 50)
	{
		medalsName = "medals_3";
	}else if(cScore >= 30)
	{
		medalsName = "medals_2";
	}else if(cScore >= 20)
	{
		medalsName = "medals_1";
	}else if(cScore >= 10)
	{
		medalsName = "medals_0";
	}
	return medalsName;
}

void StatusLayer::setBlinkSprite() {
	this->blink = Sprite::createWithSpriteFrame(ResourceLoader::getInstance()->getSpriteFrameByName("blink_00"));
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i < 3; i++){
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = ResourceLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--){
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = ResourceLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	auto animate = Animate::create(animation);
	auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction,this));
	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	blink->runAction(RepeatForever::create(sequence));
}

void StatusLayer::blinkAction()
{
	if(this->blink && this->blink->getParent()) {
		Size activeSize = this->blink->getParent()->getContentSize();
		this->blink->setPosition(rand()%((int)(activeSize.width)), rand()%((int)(activeSize.height)));
	}
}