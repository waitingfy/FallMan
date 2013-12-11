#ifndef _TUTORIALFIRST_H_
#define _TUTORIALFIRST_H_

#include "cocos2d.h"

USING_NS_CC;

class TutorialFirst : public CCLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(TutorialFirst);
	void backToMenuLayer(CCObject *pSender);
	void nextTutorial(CCObject *pSender);
private:
	CCSprite *_tutorialBg;
};


#endif