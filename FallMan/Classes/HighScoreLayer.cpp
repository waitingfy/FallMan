#include "HighScoreLayer.h"
#include "MenuLayer.h"
#include "Constants.h"

CCScene* HighScore::scene(){
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HighScore *layer = HighScore::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HighScore::init()
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

		//background
		CCSprite *bg = CCSprite::create("bg.png");
		bg->setPosition(ccp( size.width / 2,size.height / 2));
		this->addChild(bg);

		//left arrow menu
		CCSprite *leftArrowSprite = CCSprite::createWithSpriteFrameName("arrow_left.png");
		CCMenuItemSprite *leftArrowItem = CCMenuItemSprite::create(leftArrowSprite, leftArrowSprite,
			this,menu_selector(HighScore::backToMenuLayer));
		CCMenu *backMenu = CCMenu::create(leftArrowItem,NULL);
		backMenu->setPosition(ccp(32,32));
		this->addChild(backMenu);


		//title
		CCSprite *titleSprite = CCSprite::createWithSpriteFrameName("high_scores.png");
		titleSprite->setPosition(ccp(size.width / 2, size.height - 100));
		this->addChild(titleSprite);

		//high score
		int highFloor = CCUserDefault::sharedUserDefault()->getIntegerForKey(HighScoreKey);
		CCString *highFloorString = CCString::createWithFormat("%d",highFloor);
		CCLabelTTF *highScoreLabel = CCLabelTTF::create(highFloorString->getCString(),"Arial",30);
		highScoreLabel->setPosition(ccp(size.width / 2, size.height - 130));
		this->addChild(highScoreLabel);

		bRet = true;
	} while (0);

	return bRet;
}

void HighScore::backToMenuLayer(CCObject *pSender){
	PlayEffect(ClickEffect);
	CCScene *newScene = CCTransitionMoveInL::create(0.2f, MenuLayer::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}