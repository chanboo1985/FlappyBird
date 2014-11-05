#ifndef __RESOURCE_LOADER_H__
#define __RESOURCE_LOADER_H__
#include <cocos2d.h>

#define SIZE_NUM 1024

using namespace cocos2d;
using namespace std;

typedef struct resourceStruct
{
	char name[255];
	int width;
	int height;
	Point start;
	Point end;
}Resource;

class ResourceLoader
{
public:
	//单例模式
	static ResourceLoader* getInstance();
	//销毁
	static void destroyInstance();
	//根据文件名称加载资源
	void loadResource(string filename);
	//根据文件名称和纹理加载资源
	void loadResource(string filename,Texture2D *textture);
	//通过资源的名称获取资源
	SpriteFrame* getSpriteFrameByName(string name);
protected:
	ResourceLoader();
	//初始化
	virtual bool init();
	void loadingCallBack(Texture2D *texture);
	//资源加载器
	static ResourceLoader* sharedResourceLoader;
	//资源容器
	Map<std::string, SpriteFrame*> spriteFrames;
};
#endif

