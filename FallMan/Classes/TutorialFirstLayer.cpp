#include "TutorialFirstLayer.h"
#include "TutorialSecondLayer.h"
#include "MenuLayer.h"


CCScene* TutorialFirst::scene(){
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		TutorialFirst *layer = TutorialFirst::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TutorialFirst::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//help
		_tutorialBg = CCSprite::create("help.png");
		_tutorialBg->setPosition(ccp( size.width / 2,size.height / 2));
		this->addChild(_tutorialBg);

		//left arrow menu
		CCSprite *leftArrowSprite = CCSprite::createWithSpriteFrameName("arrow_left.png");
		CCMenuItemSprite *leftArrowItem = CCMenuItemSprite::create(leftArrowSprite, leftArrowSprite,
			this,menu_selector(TutorialFirst::backToMenuLayer));
		CCMenu *backMenu = CCMenu::create(leftArrowItem,NULL);
		backMenu->setPosition(ccp(32,32));
		this->addChild(backMenu);

		//right arrow menu
		CCSprite *rightArrowSprite = CCSprite::createWithSpriteFrameName("arrow_right.png");
		CCMenuItemSprite *rightArrowItem = CCMenuItemSprite::create(rightArrowSprite, rightArrowSprite,
			this,menu_selector(TutorialFirst::nextTutorial));
		CCMenu *nextTutorialMenu = CCMenu::create(rightArrowItem,NULL);
		nextTutorialMenu->setPosition(ccp(288,32));
		this->addChild(nextTutorialMenu);

		bRet = true;
	} while (0);

	return bRet;
}

void TutorialFirst::backToMenuLayer(CCObject *pSender){
	CCScene *newScene = CCTransitionMoveInL::create(0.2f, MenuLayer::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}

void TutorialFirst::nextTutorial(CCObject *pSender){
	CCScene *newScene = CCTransitionMoveInR::create(0.2f, TutorialSecond::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}