#include "ResourceLoader.h"

ResourceLoader* ResourceLoader::sharedResourceLoader = nullptr;

bool ResourceLoader::init()
{
	return true;
}

ResourceLoader::ResourceLoader()
{
	CCLOG("INFO:Start Constructor ResourceLoader");
}

ResourceLoader* ResourceLoader::getInstance()
{
	if (sharedResourceLoader == NULL)
	{
		sharedResourceLoader = new ResourceLoader();
		if (!sharedResourceLoader->init())
		{
			delete sharedResourceLoader;
			sharedResourceLoader = NULL;
			CCLOG("ERROR: Could not init ResourceLoader ");
		}
	}
	CCLOG("INFO:Create ResourceLoader Success!");
	return sharedResourceLoader;
}

void ResourceLoader::destroyInstance()
{
	CC_SAFE_DELETE(sharedResourceLoader);
}

void ResourceLoader::loadResource(string filename)
{
	/*auto textureImg = Director::getInstance()->getTextureCache()->addImage("atlas.png");
	this->loadResource(filename, textureImg);*/

	Director::getInstance()->getTextureCache()->addImageAsync(filename, CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
}

void ResourceLoader::loadingCallBack(Texture2D *texture)
{
	this->loadResource("atlas.txt",texture);
}

void ResourceLoader::loadResource(string filename,Texture2D *textture)
{
	string data = FileUtils::getInstance()->getStringFromFile(filename);
	unsigned pos;
	Resource resource;
	pos = data.find_first_of("\n");
	string line = data.substr(0,pos);
	data = data.substr(pos + 1);
	while (line != "")
	{
		sscanf(line.c_str(),"%s %d %d %f %f %f %f",
			resource.name,&resource.width,&resource.height
			,&resource.start.x,&resource.start.y
			,&resource.end.x,&resource.end.y);
		resource.start.x = SIZE_NUM*resource.start.x;
		resource.start.y = SIZE_NUM*resource.start.y;
		resource.end.x = SIZE_NUM*resource.end.x;
		resource.end.y = SIZE_NUM*resource.end.y;

		pos = data.find_first_of("\n");
		line = data.substr(0,pos);
		data = data.substr(pos + 1);

		if (resource.name == string("land"))
		{
			resource.start.x += 1;
		}
		Rect rect = Rect(resource.start.x,resource.start.y,resource.width,resource.height);
		auto frame = SpriteFrame::createWithTexture(textture, rect);
		this->spriteFrames.insert(string(resource.name),frame);
		//CCLOG("%s Load Success",string(resource.name).c_str());
	}
}

SpriteFrame* ResourceLoader::getSpriteFrameByName(string name)
{
	return this->spriteFrames.at(name);
}



