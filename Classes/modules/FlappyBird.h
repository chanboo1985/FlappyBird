#ifndef __FLAPPY_BIRD_H__
#define __FLAPPY_BIRD_H__
#include <cocos2d.h>
#include "ResourceLoader.h"
using namespace cocos2d;
using namespace std;

typedef enum ActionState
{
	ACTION_STATE_IDLE,//¿ÕÏÐ×´Ì¬
	ACTION_STATE_DIE,//ËÀÍö×´Ì¬
	ACTION_STATE_FLY//ÓÎÏ·×´Ì¬
};

const int BIRD_SPRITE_TAG = 10003;

class FlappyBird :public Sprite
{
public:
	FlappyBird(){}
	~FlappyBird(){}
	static FlappyBird* getInstance();
	virtual bool init();
	bool createFlappyBird();
	//¿ÕÏÐ×´Ì¬
	void idle();
	//ËÀÍö×´Ì¬
	void die();
	//·ÉÐÐ×´Ì¬
	void fly();
protected:
	static cocos2d::Animation* createAniamtion(const char *fmt, int count ,float fps);
	void createFlappyBirdByRandom();
private:
	static FlappyBird* shareFlappyBird;
	bool changeState(ActionState);
	//³á°ò¶¶¶¯×´Ì¬
	Action *idleAction;
	//ÉÏÏÂÇïÇ§×´Ì¬
	Action *swingAction;
	ActionState currentStatus;
	string birdName;
	string birdNameFormat;
	unsigned int isFirstTime;
};

#endif