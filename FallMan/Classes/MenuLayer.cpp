#include "MenuLayer.h"
#include "GameLayer.h"
#include "HighScoreLayer.h"
#include "TutorialFirstLayer.h"
#include "Constants.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

CCScene* MenuLayer::scene(){
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MenuLayer *layer = MenuLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuLayer::init()
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
		
		/*CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite_sheet.plist");
		_gameBatchNode = CCSpriteBatchNode::create("sprite_sheet.png");
		this->addChild(_gameBatchNode);*/

		//background
		CCSprite *bg = CCSprite::create("bg.png");
		bg->setPosition(ccp( size.width / 2,size.height / 2));
		this->addChild(bg);

		//logo
		CCSprite *logo = CCSprite::createWithSpriteFrameName("logo.png");
		logo->setPosition(ccp(160,399));
		this->addChild(logo);

		//menus

		//beginning game
		CCSprite *beginning_game_item_on = CCSprite::createWithSpriteFrameName("menu_beginning_game_on.png");
		CCSprite *beginning_game_item_off = CCSprite::createWithSpriteFrameName("menu_beginning_game_on.png");
		CCMenuItemSprite *beginning_game_item = CCMenuItemSprite::create(beginning_game_item_on,
			beginning_game_item_off,
			this,
			menu_selector(MenuLayer::beginningGame));

		//high scores
		CCSprite *high_scores_item_on = CCSprite::createWithSpriteFrameName("menu_high_scores_on.png");
		CCSprite *high_scores_item_off = CCSprite::createWithSpriteFrameName("menu_high_scores_on.png");
		CCMenuItemSprite *high_scores_item = CCMenuItemSprite::create(high_scores_item_on,
			high_scores_item_off,
			this,
			menu_selector(MenuLayer::goToHighScore));

		//help
		CCSprite *help_item_on = CCSprite::createWithSpriteFrameName("menu_help_on.png");
		CCSprite *help_item_off = CCSprite::createWithSpriteFrameName("menu_help_on.png");
		CCMenuItemSprite *help_item = CCMenuItemSprite::create(help_item_on,
			help_item_off,
			this,
			menu_selector(MenuLayer::goToHelp));

		//quit game
		CCSprite *quit_game_item_on = CCSprite::createWithSpriteFrameName("menu_quit_on.png");
		CCSprite *quit_game_item_off = CCSprite::createWithSpriteFrameName("menu_quit_on.png");

		CCMenuItemSprite *quit_game_item = CCMenuItemSprite::create(quit_game_item_on,
			quit_game_item_off,
			this,
			menu_selector(MenuLayer::quitGame));
		//more application
		CCSprite *more_application_item_on = CCSprite::createWithSpriteFrameName("menu_more_application_on.png");
		CCSprite *more_application_item_off = CCSprite::createWithSpriteFrameName("menu_more_application_on.png");

		CCMenuItemSprite *more_application_item = CCMenuItemSprite::create(more_application_item_on,
			more_application_item_off,
			this,
			menu_selector(MenuLayer::goToMoreApplication));

		_mainMenu=CCMenu::create(beginning_game_item,high_scores_item,help_item,quit_game_item,more_application_item,NULL);
		_mainMenu->alignItemsVerticallyWithPadding(10);
		_mainMenu->setPosition(ccp(160, 200));
		this->addChild(_mainMenu);

		//sound on
		CCSprite *sound_item_on = CCSprite::createWithSpriteFrameName("sound_on.png");

		CCMenuItemSprite *sound_on_item = CCMenuItemSprite::create(sound_item_on,
			sound_item_on,
			this,
			menu_selector(MenuLayer::soundOnMenuPress));
		_soundOnMenu = CCMenu::create(sound_on_item,NULL);
		_soundOnMenu->setPosition(ccp(32, 32));
		this->addChild(_soundOnMenu);

		//sound off
		CCSprite *sound_item_off = CCSprite::createWithSpriteFrameName("sound_off.png");

		CCMenuItemSprite *sound_off_item = CCMenuItemSprite::create(sound_item_off,
			sound_item_off,
			this,
			menu_selector(MenuLayer::soundOffMenuPress));
		_soundOffMenu = CCMenu::create(sound_off_item,NULL);
		_soundOffMenu->setPosition(ccp(32, 32));
		this->addChild(_soundOffMenu);


		//set menus' visibility due to "save data"
		_soundEnable = CCUserDefault::sharedUserDefault()->getBoolForKey(SoundEnableKey,true);
		
		if(_soundEnable){
			_soundOnMenu->setVisible(true);
			_soundOffMenu->setVisible(false);
			if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BackGroundMusic,true);
			}		
		}else{
			_soundOnMenu->setVisible(false);
			_soundOffMenu->setVisible(true);
			
		}

		bRet = true;
	} while (0);

	return bRet;
}

void MenuLayer::beginningGame(CCObject* pSender){
	PlayEffect(ClickEffect);
	CCScene *newScene = CCTransitionMoveInR::create(0.2f,GameLayer::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}

void MenuLayer::goToHighScore(CCObject* pSender){
	PlayEffect(ClickEffect);
	CCScene *newScene = CCTransitionMoveInR::create(0.2f,HighScore::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}

void MenuLayer::goToHelp(CCObject* pSender){
	PlayEffect(ClickEffect);
	CCScene *newScene = CCTransitionMoveInR::create(0.2f,TutorialFirst::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}

void MenuLayer::quitGame(CCObject* pSender){
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void MenuLayer::goToMoreApplication(CCObject* pSender){

}

void MenuLayer::soundOnMenuPress(CCObject* pSender){
	CCUserDefault::sharedUserDefault()->setBoolForKey(SoundEnableKey,false);
	_soundOnMenu->setVisible(false);
	_soundOffMenu->setVisible(true);
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void MenuLayer::soundOffMenuPress(CCObject* pSender){
	CCUserDefault::sharedUserDefault()->setBoolForKey(SoundEnableKey,true);
	_soundOnMenu->setVisible(true);
	_soundOffMenu->setVisible(false);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BackGroundMusic,true);
}