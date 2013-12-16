#ifndef __MENULAYER_H__
#define __MENULAYER_H__

#include "cocos2d.h"
USING_NS_CC;



class MenuLayer : public CCLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(MenuLayer);
	void beginningGame(CCObject* pSender);
	void goToHighScore(CCObject* pSender);
	void goToHelp(CCObject* pSender);
	void quitGame(CCObject* pSender);
	void goToMoreApplication(CCObject* pSender);
	void soundOnMenuPress(CCObject* pSender);
	void soundOffMenuPress(CCObject* pSender);
private:
	CCSpriteBatchNode *_gameBatchNode;
	CCMenu *_mainMenu;
	CCMenu *_soundOnMenu;
	CCMenu *_soundOffMenu;
	bool _soundEnable;
	
};


#endif