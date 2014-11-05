#ifndef __OPTION_LAYER_H__
#define __OPTION_LAYER_H__
#include <cocos2d.h>
using namespace cocos2d;
//�������������ʵ�������������ݽ���
class OptionDelegate
{
public:
	virtual void onTouch() = 0;
};

class OptionLayer : public Layer
{
public:
	OptionLayer(){}

	~OptionLayer(){}

	virtual bool init();

	CREATE_FUNC(OptionLayer);

	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;

	CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};

#endif