#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include "cocos2d.h"

USING_NS_CC;

class HighScore : public CCLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(HighScore);
	void backToMenuLayer(CCObject *pSender);
};


#endif