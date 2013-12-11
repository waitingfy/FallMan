#include "GameSprite.h"

GameSprite::GameSprite(void)
{
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

GameSprite::~GameSprite(void)
{
}


float GameSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}

CCRect GameSprite::getRect(){
	return CCRectMake(left(), bottom(), getWidth(), getHeight());
}

