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
	//����ģʽ
	static ResourceLoader* getInstance();
	//����
	static void destroyInstance();
	//�����ļ����Ƽ�����Դ
	void loadResource(string filename);
	//�����ļ����ƺ����������Դ
	void loadResource(string filename,Texture2D *textture);
	//ͨ����Դ�����ƻ�ȡ��Դ
	SpriteFrame* getSpriteFrameByName(string name);
protected:
	ResourceLoader();
	//��ʼ��
	virtual bool init();
	void loadingCallBack(Texture2D *texture);
	//��Դ������
	static ResourceLoader* sharedResourceLoader;
	//��Դ����
	Map<std::string, SpriteFrame*> spriteFrames;
};
#endif

