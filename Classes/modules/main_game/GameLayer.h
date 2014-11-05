#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include <cocos2d.h>
#include <cstdlib>
#include "OptionLayer.h"
#include "modules/FlappyBird.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"
#include "UserRecord.h"
using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

const int UP_PIP = 21;

const int DOWN_PIP = 12;

const int PIP_PASS = 30;

const int PIP_NEW = 31;

/**
 * The radius of the bird
 */
const int BIRD_RADIUS = 15;

/**
 * The height of the pips
 */
const int PIP_HEIGHT = 320;

/**
 * The width of the pips
 */
const int PIP_WIDTH = 52;

/**
 * The distance between the down pip and up pip
 */
const int PIP_DISTANCE = 100;

/**
 * The distance between the pips vertical
 */
const int PIP_INTERVAL = 180;

/**
 * The distance that the pip will display in the screen, for player to ready
 */
const int WAIT_DISTANCE = 100;

/**
 * The number of pip pairs display in the screen in the same time
 */
const int PIP_COUNT = 2;

typedef enum _game_status
{
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
}GameStatus;

class StatusDelegate
{
public:
	virtual void onGameStart() = 0;

	virtual void onGamePlaying(int score) = 0;

	virtual void onGameEnd(int curScore, int bestScore) = 0;
};

class GameLayer : public Layer, public OptionDelegate
{
public:
	GameLayer(){}

	~GameLayer(){}

	virtual bool init();

	CREATE_FUNC(GameLayer);

	void onTouch() override;

	void setPhysicalWorld(PhysicsWorld *world){	this->world = world;}

	void update(float deta);

	CC_SYNTHESIZE(StatusDelegate *, delegator, Delegator);

private:
	void rotateBird();

	void createPips();

	int getRandomHeight();

	void checkHit();

	void birdSpriteFadeOut();

	void birdSpriteRemove();

	PhysicsWorld *world;

	GameStatus gameStatus;

	int score;

	FlappyBird *bird;

	Node *groundNode;

	vector<Node *> pips;

	Sprite *land_1,*land_2;

	SEL_SCHEDULE shiftLand;

	void scrollLand(float dt);

	bool onContactBegin(const PhysicsContact& contact);

	void gameOver();
};


#endif