#ifndef __FLAPPY_BIRD_H__
#define __FLAPPY_BIRD_H__
#include <cocos2d.h>
#include "ResourceLoader.h"
using namespace cocos2d;
using namespace std;

typedef enum ActionState
{
	ACTION_STATE_IDLE,//����״̬
	ACTION_STATE_DIE,//����״̬
	ACTION_STATE_FLY//��Ϸ״̬
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
	//����״̬
	void idle();
	//����״̬
	void die();
	//����״̬
	void fly();
protected:
	static cocos2d::Animation* createAniamtion(const char *fmt, int count ,float fps);
	void createFlappyBirdByRandom();
private:
	static FlappyBird* shareFlappyBird;
	bool changeState(ActionState);
	//��򶶶�״̬
	Action *idleAction;
	//������ǧ״̬
	Action *swingAction;
	ActionState currentStatus;
	string birdName;
	string birdNameFormat;
	unsigned int isFirstTime;
};

#endif