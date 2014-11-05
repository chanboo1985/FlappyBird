#include "HelloWorldScene.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
#include <vector>
#include <map>
#include <string>

//��������PATH��windows�º�linux�µķָ������
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif // _DEBUG

USING_NS_CC;
USING_NS_UM_SOCIAL;

// layer tag
int layerTag = 123;
// label tag
int labelTag = 456;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "../cocos2d/cocos/2d/platform/android/jni/JniHelper.h" //�����·��Ҫ�����㹤�̵�ʵ��������и���
#include <android/log.h>

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif

#endif


Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();
	layer->setTag(layerTag);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

/*
 *��Ȩ�ص�
 * @param platform Ҫ��Ȩ��ƽ̨
 * @param stCode ������, 200������Ȩ�ɹ�, 100����ʼ��Ȩ, 0������Ȩ����, -1����ȡ����Ȩ
 * @param data ��Ȩʱ���ص�����
 */
void authCallback(int platform, int stCode, map<string, string>& data) {
	if (stCode == 100) {
		CCLog("#### ��Ȩ��ʼ");
	} else if (stCode == 200) {
		CCLog("#### ��Ȩ���");
	} else if (stCode == 0) {
		CCLog("#### ��Ȩ����");
	} else if (stCode == -1) {
		CCLog("#### ȡ����Ȩ");
	}

	// ������Ȩ����, �����Ȩʧ��,������������Ϣ
	map<string, string>::iterator it = data.begin();
	for (; it != data.end(); ++it) {
		CCLog("#### data  %s -> %s.", it->first.c_str(), it->second.c_str());
	}
}

/*
 * ����ص�
 * @param platform Ҫ������Ŀ��ƽ̨
 * @param stCode ������, 200�������ɹ�, 100����ʼ����
 * @param errorMsg ����ʧ��ʱ�Ĵ�����Ϣ,androidƽ̨û�д�����Ϣ
 */
void shareCallback(int platform, int stCode, string& errorMsg) {
	HelloWorld* hwLayer =
			(HelloWorld*) CCDirector::sharedDirector()->getRunningScene()->getChildByTag(
					layerTag);
	CCLabelTTF* item = (CCLabelTTF*) hwLayer->getChildByTag(labelTag);
	string result = "";
	if (stCode == 100) {
		result = "��ʼ����";
		CCLog("#### HelloWorld ��ʼ����");
	} else if (stCode == 200) {
		result = "����ɹ�";
		CCLog("#### HelloWorld ����ɹ� --> Cocos2d-x SDK ");
	} else {
		result = "����ʧ��";
		CCLog("#### HelloWorld ������� --> Cocos2d-x SDK ");
	}

	istringstream is ;
	is>>platform;
	result.append(is.str());
	item->setString(result.c_str());
	CCLog("platform num is : %d, %d", platform, stCode);

}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//// ********************  �������˵�app key�Լ���ص���Ϣ  ***********************************
	//// ��ȡCCUMSocialSDK����, ���ʹ�õ�UMShareButton, ��ͨ��UMShareButton�����getSocialSDK()������ȡ.
	//CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	//sdk->setTargetUrl("http://www.umeng.com/social");
	////    // ��������app key
	////    sdk->setAppKey("507fcab25270157b37000010");
	//sdk->setQQAppIdAndAppKey("100424468", "c7394704798a158208a74ab60104f0ba");
	//sdk->setWeiXinAppId("wx485ab7ca6a7e02d1");
	//sdk->setYiXinAppKey("yx52dd5c14bbb3430b93e6f2dafcbcc68d");
	//sdk->setLaiwangAppInfo("����������������̬��app id", "����������������̬��app key", "�ҵ�Ӧ����");
	//sdk->setFacebookAppId("567261760019884");
	//sdk->openTwitterForiOS();
	//// �����û����һ��ͼ�ķ���ʱ�û���ת����Ŀ��ҳ��, һ��Ϊapp��ҳ��������ҳ��


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// �򿪷������
	CCMenuItemFont *shareTextButton = CCMenuItemFont::create("OpenShared", this,
		menu_selector(HelloWorld::menuShareCallback));
	shareTextButton->setPosition(ccp(150, 480));

	// �ײ�API����
	CCMenuItemFont *directTextButton = CCMenuItemFont::create("DiShared", this,
		menu_selector(HelloWorld::directShareCallback));
	directTextButton->setPosition(ccp(150, 400));

	// ��Ȩĳƽ̨
	CCMenuItemFont *authTextButton = CCMenuItemFont::create("Shouquan", this,
		menu_selector(HelloWorld::authorizeCallback));
	authTextButton->setPosition(ccp(150, 320));

	// ɾ��ĳƽ̨��Ȩ
	CCMenuItemFont *delAuthTextButton = CCMenuItemFont::create("Delete", this,
		menu_selector(HelloWorld::deleteAuthorizeCallback));
	delAuthTextButton->setPosition(ccp(150, 240));

	// �ж�ĳƽ̨�Ƿ���Ȩ
	CCMenuItemFont *isAuthTextButton = CCMenuItemFont::create("Check", this,
		menu_selector(HelloWorld::isAuthorizedShareCallback));
	isAuthTextButton->setPosition(ccp(150, 160));


	// ********************************************************************************

	// �򿪻��߹ر�log
	//sdk->setLogEnable(true);

	// �رհ�ť
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
		"CloseSelected.png", this,
		menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(
		ccp(
		origin.x + visibleSize.width
		- pCloseItem->getContentSize().width / 2,
		origin.y + pCloseItem->getContentSize().height / 2));

//	// ����share button, ����1Ϊ��������µ�ͼƬ, ����2Ϊ�û�������ͼƬ, ����3Ϊ����app key, ������Ϊ����ص�.
//	UMShareButton *shareButton = UMShareButton::create("share.png",
//		"CloseSelected.png", "4eaee02c527015373b000003",
//		share_selector(shareCallback));
//	vector<int>* platforms = new vector<int>();
//	platforms->push_back(SINA);
//	platforms->push_back(FACEBOOK);
//	//	platforms->push_back(INSTAGRAM);
//	platforms->push_back(QZONE);
//	platforms->push_back(QQ);
//	platforms->push_back(YIXIN_CIRCLE);
//	platforms->push_back(YIXIN);
//	platforms->push_back(WEIXIN);
//	shareButton->setPlatforms(platforms) ;
//	shareButton->setShareContent("���Ǻܳ������������Ǹ����պ��Ƿ����Ǵ�Ҹ���ʦ�����˶Է�����");
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//
//	shareButton->setShareImage(NULL);
//
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//
//	shareButton->setShareImage("share.png");
//
//#endif
//
//	// ���÷���ص�
//	shareButton->setShareCallback(share_selector(shareCallback));
//	shareButton->setPosition(ccp(480, 150));

	/*CCMenuItemFont *umshareTextButton = CCMenuItemFont::create("����ShareButton");
	umshareTextButton->setPosition(ccp(480, 60));*/

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create();
	pMenu->addChild(pCloseItem, 1);
	// ����share button
	/*pMenu->addChild(shareButton, 1);
	pMenu->addChild(umshareTextButton, 1);*/

	// ���ְ�ť
	pMenu->addChild(shareTextButton, 1);
	pMenu->addChild(directTextButton, 1);
	pMenu->addChild(authTextButton, 1);
	pMenu->addChild(delAuthTextButton, 1);
	pMenu->addChild(isAuthTextButton, 1);

	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	CCLabelTTF* pLabel = CCLabelTTF::create("Umeng Social Cocos2d-x SDK",
		"Arial", 34);
	pLabel->setTag(labelTag);
	// position the label on the center of the screen
	pLabel->setPosition(
		ccp(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height
		- pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(
		ccp(visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
    
    return true;
}

// ֱ�ӷ���İ�ť�ص�
void HelloWorld::directShareCallback(Ref* pSender) {

	/*CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sdk->directShare(QQ,
		"Umeng Social Cocos2d-x SDK -->  directShare   testing",
		"sdfsd", share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sdk->directShare(FACEBOOK, "Umeng Social Cocos2d-x SDK -->  directShare   testing", "http://www.baidu.com/img/bdlogo.gif", share_selector(shareCallback));
#endif*/
}

// ��Ȩĳ��ƽ̨�İ�ť�ص�
void HelloWorld::authorizeCallback(Ref* pSender) {

	/*static int count = 0;
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	CCLog("��Ȩ");
	sdk->authorize(TENCENT_WEIBO, auth_selector(authCallback));*/
}

// ɾ��ĳ��ƽ̨�İ�ť�ص�
void HelloWorld::deleteAuthorizeCallback(Ref* pSender) {
	/*CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	CCLog("ɾ����Ѷ΢����Ȩ");
	sdk->deleteAuthorization(SINA, auth_selector(authCallback));*/
}

// �ж�ĳ��ƽ̨�İ�ť�ص�
void HelloWorld::isAuthorizedShareCallback(Ref* pSender) {
	/*CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	CCLog("@@@@ �ж�����΢���Ƿ���Ȩ");
	bool isAuthorized = sdk->isAuthorized(SINA);
	if (isAuthorized) {
	CCLog("@@ ����΢���Ѿ���Ȩ");
	} else {
	CCLog("@@ ����΢����û����Ȩ");
	}*/
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	//��ȡUmengGameActivity�ľ�̬����openShareBoard
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "openShareBoard", "()V");
	if(isHave){
		LOGD("is have static method!!!!!!!!");
		//ʵ�ʵ���UmengGameActivity�д�umeng����ƽ̨ѡ�����
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}


void HelloWorld::menuShareCallback(Ref* pSender)
{

//	CCUMSocialSDK *sdk = CCUMSocialSDK::create("54258b8afd98c5944700cfd9");
//	vector<int> *platforms = new vector<int>();
//	platforms->push_back(SINA);
//	platforms->push_back(RENREN);
//	platforms->push_back(TENCENT_WEIBO);
//	platforms->push_back(QZONE);
//	platforms->push_back(QQ);
//	platforms->push_back(YIXIN_CIRCLE);
//	platforms->push_back(YIXIN);
//	platforms->push_back(WEIXIN);
//	platforms->push_back(TWITTER);
//	platforms->push_back(FACEBOOK);
//	//����ƽ̨
//	sdk->setPlatforms(platforms);
//	// �򿪷������, ע�����ص�, android �� IOS��ͼƬ��ַ��ʽ��һ�£���˷ֿ�����
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	sdk->openShare("Umeng Social Cocos2d-x SDK V1.0 -->  openShare",
//		"http://www.umeng.com/images/pic/banner_module_social.png",
//		share_selector(shareCallback));
//#endif
}

/**
 * ��ͼ����
 */
void HelloWorld::saveScreenshot() {
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	//CCRenderTexture* texture = CCRenderTexture::create((int) size.width,
	//		(int) size.height);
	//texture->setPosition(ccp(size.width / 2, size.height / 2));
	//texture->begin();
	//CCDirector::sharedDirector()->getRunningScene()->visit();
	//texture->end();
	//string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath().c_str();
	//CCLog("imagePath:%s",imagePath.c_str());
	////����Ϊpng
	//bool result = texture->saveToFile("screenshot.png", kCCImageFormatPNG);
	//if (result) {
	//	imagePath += "screenshot.png";
	//	CCLog("imagePath:%s",imagePath.c_str());
	//}

}
