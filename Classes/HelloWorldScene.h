#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	// 打开分享面板的按钮回调
	void menuShareCallback(cocos2d::Ref* pSender);
	// 直接分享的按钮回调
	void directShareCallback(cocos2d::Ref* pSender);
	// 授权某个平台的按钮回调
	void authorizeCallback(cocos2d::Ref* pSender);
	// 删除某个平台的按钮回调
	void deleteAuthorizeCallback(cocos2d::Ref* pSender);
	// 判断某个平台的按钮回调
	void isAuthorizedShareCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	void saveScreenshot();
};

#endif // __HELLOWORLD_SCENE_H__
