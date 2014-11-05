#ifndef __STATUS_LAYER_H__
#define __STATUS_LAYER_H__
#include <cocos2d.h>
#include "GameLayer.h"
#include "Number.h"
#include "GameScene.h"
using namespace cocos2d;

const string NUMBER_SCORE = "number_score";
const string NUMBER_FONT = "font";
const int CURRENT_SCORE_SPRITE_TAG = 10001;

class StatusLayer : public Layer , public StatusDelegate
{
public:
	StatusLayer(){}

	~StatusLayer(){}

	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void onGameStart();

	void onGamePlaying(int score);

	void onGameEnd(int curScore, int bestScore);

private:
	void showReadyStatus();

	void loadWhiteSprite();

	void showStartStatus();

	void showOverStatus(int, int);

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	string getMedalsName(int);

	void setBlinkSprite();

	void blinkAction();

	void fadeInRestartBtn();

	void refreshScoreCallback();

	void refreshScoreExecutor(float);

	void menuRestartCallback(Object *sender);

	Sprite* scoreSprite;

	Sprite* getreadySprite;

	Sprite* tutorialSprite;

	Sprite* whiteSprite;

	Sprite* blink;

	Size visibleSize;

	Point origin;

	int tmpScore;

	int bestScore;

	int currentScore;

	bool isNewRecord;
};


#endif