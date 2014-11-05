#ifndef __USER_RECORD_H__
#define __USER_RECORD_H__
#include <cocos2d.h>
using namespace cocos2d;

//保存玩家数据
class UserRecord : public Object
{
public:
	UserRecord(){}

	~UserRecord(){}

	static UserRecord* getInstance();

	virtual bool init();

	void saveIntegerToUserDefault(const char *key, int score);

	int getIntegerFromUserDefault(const char *key);

private:
	static UserRecord* sharedUserRecord;
};


#endif