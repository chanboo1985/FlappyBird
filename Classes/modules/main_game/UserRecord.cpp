#include "UserRecord.h"

bool UserRecord::init()
{
	return true;
}

UserRecord* UserRecord::sharedUserRecord = nullptr;
UserRecord* UserRecord::getInstance()
{
	if (sharedUserRecord == NULL)
	{
		sharedUserRecord = new UserRecord();
		if (!sharedUserRecord->init())
		{
			delete sharedUserRecord;
			sharedUserRecord = NULL;
		}
	}
	return sharedUserRecord;
}

void UserRecord::saveIntegerToUserDefault(const char *key, int score)
{
	UserDefault::getInstance()->setIntegerForKey(key, score);
}

int UserRecord::getIntegerFromUserDefault(const char *key)
{
	return UserDefault::getInstance()->getIntegerForKey(key);
}



