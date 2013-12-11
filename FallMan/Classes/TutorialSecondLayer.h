#ifndef _TUTORIALSECOND_H_
#define _TUTORIALSECOND_H_

#include "cocos2d.h"

USING_NS_CC;

class TutorialSecond : public CCLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(TutorialSecond);
	void backTutorial(CCObject *pSender);
private:
	CCSprite *_tutorialBg;
};


#endif