#ifndef _GAMESPRITE_H_
#define _GAMESPRITE_H_

#include "cocos2d.h"

USING_NS_CC;


class GameSprite : public CCSprite{
public:
	CCSize _screenSize;
	CC_SYNTHESIZE(float, _width, Width);
	CC_SYNTHESIZE(float, _height, Height);
	GameSprite(void);
	~GameSprite(void);
	float radius();
	CCRect getRect();

	inline int left() {
		return this->getPositionX() - _width * 0.5f;
	}
	inline int right() {
		return this->getPositionX() + _width * 0.5f;
	}
	inline int top() {
		return this->getPositionY() + _height * 0.5f ;
	}
	inline int bottom() {
		return this->getPositionY() - _height * 0.5f ;
	}
};

#endif