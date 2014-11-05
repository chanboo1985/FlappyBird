#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__
#include "cocos2d.h"
#include "../ResourceLoader.h"
USING_NS_CC;

class BackGroundLayer : public Layer
{
public:
	BackGroundLayer(){}

	~BackGroundLayer(){}

	virtual bool init();

	CREATE_FUNC(BackGroundLayer);

	static float getLandHeight();
};

#endif