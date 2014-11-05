#ifndef __NUMBER_H__
#define __NUMBER_H__
#include "cocos2d.h"
#include "../ResourceLoader.h"
using namespace cocos2d;
using namespace std;

typedef enum _gravity
{
	GRAVITY_CENTER = 1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT
}Gravity;

/**
* The distance between two number
*/
const int NumberInterval = 4;

const int NUMBER_MAX = 10;

class NumberSeries : public Object
{
public:
	NumberSeries(){}

	~NumberSeries(){}

	virtual bool init();

	CREATE_FUNC(NumberSeries);

	void loadNumber(const char *fmt, int base = 0);

	SpriteFrame* at(int index);
private:
	Vector<SpriteFrame*> numberSeries;
};

class Number
{
public:
	Number(){}

	~Number(){}

	static Number* getInstance();

	virtual bool loadNumber(const char *name, const char *fmt, int base = 0);

	virtual bool init();

	Node* convert(const char *name, int number, Gravity gravity = Gravity::GRAVITY_CENTER);
private:
	Map<string, NumberSeries*> numberContainer;
	static Number* sharedNumber;
};


#endif