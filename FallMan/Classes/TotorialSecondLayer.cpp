#include "TutorialFirstLayer.h"
#include "TutorialSecondLayer.h"


CCScene* TutorialSecond::scene(){
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		TutorialSecond *layer = TutorialSecond::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TutorialSecond::init()
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
		_tutorialBg = CCSprite::create("help1.png");
		_tutorialBg->setPosition(ccp( size.width / 2,size.height / 2));
		this->addChild(_tutorialBg);

		//left arrow menu
		CCSprite *leftArrowSprite = CCSprite::createWithSpriteFrameName("arrow_left.png");
		CCMenuItemSprite *leftArrowItem = CCMenuItemSprite::create(leftArrowSprite, leftArrowSprite,
			this,menu_selector(TutorialSecond::backTutorial));
		CCMenu *backMenu = CCMenu::create(leftArrowItem,NULL);
		backMenu->setPosition(ccp(32,32));
		this->addChild(backMenu);

		bRet = true;
	} while (0);

	return bRet;
}


void TutorialSecond::backTutorial(CCObject *pSender){
	CCScene *newScene = CCTransitionMoveInL::create(0.2f, TutorialFirst::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}