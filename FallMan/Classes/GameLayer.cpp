#include "GameLayer.h"
#include "Constants.h"
#include "Board.h"
#include "AnimationManager.h"
#include "MenuLayer.h"
#include <algorithm>

using namespace cocos2d;

//typedef enum{
//	kNormalBoard,      //0
//	kRollingBoard,     //1
//	kRotateLeftBoard,  //2
//	kRotateRightBoard, //3
//	kStarBoard,        //4
//	kSpringBoard       //5
//}BoardType;

int level1[] = {0,0,0,0,0,0,0,1,1,1,1};
int level2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,3,3};
int level3[] = {0,0,0,0,0,0,0,0,0,0,0,0,5,5,1,1,1,2,2,3,3};
int level4[] = {0,0,0,0,0,0,0,0,0,0,0,5,5,5,1,1,1,2,2,3,3};
int level5[] = {0,0,0,0,0,0,0,0,0,4,4,5,5,5,1,1,1,2,2,3,3};
int level6[] = {0,0,0,0,0,0,0,0,4,4,4,5,5,5,1,1,1,2,2,3,3};
int level7[] = {0,0,0,0,0,0,0,4,4,4,4,5,5,5,1,1,1,2,2,3,3};
int level8[] = {0,0,0,0,0,0,4,4,4,4,5,5,5,5,1,1,1,2,2,3,3};
int level9[] = {0,0,0,0,0,4,4,4,4,4,5,5,5,1,1,1,1,2,2,3,3};
int level10[] = {0,0,0,0,4,4,4,4,5,5,5,5,1,1,1,1,2,2,3,3};

vector<int> _level1(level1,level1 + sizeof(level1) / sizeof(int));
vector<int> _level2(level2,level2 + sizeof(level2) / sizeof(int));
vector<int> _level3(level3,level3 + sizeof(level3) / sizeof(int));
vector<int> _level4(level4,level4 + sizeof(level4) / sizeof(int));
vector<int> _level5(level5,level5 + sizeof(level5) / sizeof(int));
vector<int> _level6(level6,level6 + sizeof(level6) / sizeof(int));
vector<int> _level7(level7,level7 + sizeof(level7) / sizeof(int));
vector<int> _level8(level8,level8 + sizeof(level8) / sizeof(int));
vector<int> _level9(level9,level9 + sizeof(level9) / sizeof(int));
vector<int> _level10(level10,level10 + sizeof(level10) / sizeof(int));

GameLayer::GameLayer():_floorPosition(0),_startPosition(250),_levelIndex(0),_gameState(kGameReady)
,_boardSpeed(GoTopSpeed),_changeHighScore(false){

}

GameLayer::~GameLayer(){
	CC_SAFE_RELEASE(_boardObjects);
}


CCScene* GameLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLayer *layer = GameLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		random_shuffle(_level1.begin(),_level1.end());
		random_shuffle(_level2.begin(),_level2.end());
		random_shuffle(_level3.begin(),_level3.end());
		random_shuffle(_level4.begin(),_level4.end());
		random_shuffle(_level5.begin(),_level5.end());
		random_shuffle(_level6.begin(),_level6.end());
		random_shuffle(_level7.begin(),_level7.end());
		random_shuffle(_level8.begin(),_level8.end());
		random_shuffle(_level9.begin(),_level9.end());
		random_shuffle(_level10.begin(),_level10.end());

		srand(unsigned(time(0)));
		// Get window size and place the label upper. 
		_screenSize = CCDirector::sharedDirector()->getWinSize();
		
		_gameBatchNode = CCSpriteBatchNode::create("sprite_sheet.png");

		//background
		CCSprite *bg = CCSprite::create("bg.png");
		bg->setPosition(ccp( _screenSize.width / 2,_screenSize.height / 2));
		this->addChild(bg,kBackground);


		//floor label
		_floorLabel = CCLabelTTF::create("0","Arial",30);
		_floorLabel->setPosition(ccp(30,465));
		this->addChild(_floorLabel,kMiddleground);

		//bob
		_bob = Bob::create(ccp(_screenSize.width / 2,_screenSize.height - 200));
		this->addChild(_bob,kMiddleground);
		
		//boards
		_boardObjects = CCArray::createWithCapacity(BoardCountEveryTimeGenerate);
		_boardObjects->retain();
		generateSomeBoards(_startPosition,BoardCountEveryTimeGenerate);

		//blood count
		_bloodCount = CCSprite::createWithSpriteFrameName("blood_count_12.png");
		_bloodCount->setPosition(ccp( 230,465));
		this->addChild(_bloodCount,kMiddleground);

		// top star board
		_topStarBoard = CCSprite::createWithSpriteFrameName("bloard_top.png");
		_topStarBoard->setPosition(ccp( _screenSize.width / 2,440));
		this->addChild(_topStarBoard,kMiddleground);

		//menus
		initMenus();

		// ready sprite
		_gameReady = CCSprite::createWithSpriteFrameName("ready.png");
		_gameReady->setPosition(ccp(_screenSize.width / 2, _screenSize.height / 2));
		_gameReady->setVisible(false);
		_gameBatchNode->addChild(_gameReady,kMiddleground);

		//gameover sprite
		_gameOver= CCSprite::createWithSpriteFrameName("gameover.png");
		_gameOver->setPosition(ccp(_screenSize.width / 2, _screenSize.height / 2));
		_gameOver->setVisible(false);
		_gameBatchNode->addChild(_gameOver,kForeground);

		this->schedule(schedule_selector(GameLayer::update));
		this->addChild(_gameBatchNode,kBackground);
		this->setTouchEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}


void GameLayer::update(float dt){

	switch(_gameState){
	case kGameReady:
		_gameReady->setVisible(true);
		break;
	case kGameRunning:
		_gameReady->setVisible(false);
		_navigationMenu->setVisible(true);
		updateBobAndBoard(dt);
		changeSpeedWithFloorCount();  //we will add difficult when the floor count going larger
		displayFloorNum();
		displayBloodCount();
		checkGameOver();
		break;
	case kGamePause:
		_navigationMenu->setVisible(false);
		break;
	case kGameOver:
		_gameOver->setVisible(true);
		_navigationMenu->setVisible(false);
		break;
	}
	
}


void GameLayer::leftMove(CCObject* pSender){
	_bob->setDirection(kBobLeft);
}

void GameLayer::rightMove(CCObject* pSender){
	_bob->setDirection(kBobRight);
}


int GameLayer::getFloorCount(){
	return _floorPosition / _screenSize.height;
}

void GameLayer::generateSomeBoards(int startPosition,int count){
	CCLOG("generateSomeBoard:startPosition:%d",startPosition);
	if(_boardObjects->count() <= 10){
		int randomPositionX;
		for(int i = 0; i < count; ++i){
			_boardItem = Board::create((BoardType)getLevelDueToFloorNum()[_levelIndex]);
			getNextBoardIndex(_levelIndex,getLevelDueToFloorNum());
			_gameBatchNode->addChild(_boardItem);
			randomPositionX = CCRANDOM_0_1() * (_screenSize.width - _boardItem->getWidth())
				+ _boardItem->getWidth() / 2;
			_boardItem->setPosition(ccp(randomPositionX,startPosition));
			_boardObjects->addObject(_boardItem);
			startPosition -= PerBoardHeight;

		}
		
	}
	
}

void GameLayer::getNextBoardIndex(int &levelIndex,vector<int> &levelVector){
	++levelIndex;
	if(levelIndex == levelVector.size()){
		levelIndex = 0;
		random_shuffle(levelVector.begin(),levelVector.end());
	}
}

void GameLayer::initMenus(){
	//left and right menu
	CCMenuItemFont *leftMenuItem = CCMenuItemFont::create("Left",this,menu_selector(GameLayer::leftMove));
	CCMenuItemFont *rightMenuItem = CCMenuItemFont::create("right",this,menu_selector(GameLayer::rightMove));

	_navigationMenu = CCMenu::create(leftMenuItem,rightMenuItem,NULL);
	_navigationMenu->setPosition(ccp(_screenSize.width / 2, 100));
	_navigationMenu->alignItemsHorizontallyWithPadding(20);
	_navigationMenu->setVisible(false);
	this->addChild(_navigationMenu,kForeground);

	// pause menu
	CCSprite *pauseSprite = CCSprite::createWithSpriteFrameName("pause.png");
	CCMenuItemSprite *pauseMenuItem = CCMenuItemSprite::create(pauseSprite,pauseSprite,
		this,menu_selector(GameLayer::pauseGame));
	_pauseMenu = CCMenu::create(pauseMenuItem,NULL);
	_pauseMenu->setPosition(ccp( 300,465));
	this->addChild(_pauseMenu,kMiddleground);

	// resume menu
	CCSprite *resumeSprite = CCSprite::createWithSpriteFrameName("resume_menu.png");
	CCMenuItemSprite *resumeMenuItem = CCMenuItemSprite::create(resumeSprite,resumeSprite,
		this,menu_selector(GameLayer::resumeGame));
	CCSprite *backToMenuLayerSprite = CCSprite::createWithSpriteFrameName("back_to_menu_menu.png");
	CCMenuItemSprite *backToMenuLayerMenuItem = CCMenuItemSprite::create(backToMenuLayerSprite,
		backToMenuLayerSprite,this,menu_selector(GameLayer::backToMenuLayer));
	_resumeMenu = CCMenu::create(resumeMenuItem,backToMenuLayerMenuItem,NULL);
	_resumeMenu->alignItemsVertically();
	_resumeMenu->setPosition(ccp(_screenSize.width / 2, _screenSize.height / 2));
	_resumeMenu->setVisible(false);
	this->addChild(_resumeMenu,kForeground);

	
}

vector<int> GameLayer::getLevelDueToFloorNum(){
	int floorCount = getFloorCount();
	if(floorCount <= 5){
		return _level1;
	}else if(floorCount > 5 && floorCount <= 10){
		return _level2;
	}else if(floorCount > 10 && floorCount <=15){
		return _level3;
	}else if(floorCount > 15 && floorCount <=20){
		return _level4;
	}else if(floorCount > 20 && floorCount <=25){
		return _level5;
	}else if(floorCount > 25 && floorCount <=30){
		return _level6;
	}else if(floorCount > 30 && floorCount <=35){
		return _level7;
	}else if(floorCount > 35 && floorCount <=40){
		return _level8;
	}else if(floorCount > 40 && floorCount <=45){
		return _level9;
	}else{
		return _level10;
	}
}


void GameLayer::changeSpeedWithFloorCount(){
	if(getFloorCount() >= 10){
		setBoardSpeed(GoTopSpeed * 1.1);
	}else if(getFloorCount() >= 20){
		setBoardSpeed(GoTopSpeed * 1.2);
	}else if(getFloorCount() >= 30){
		setBoardSpeed(GoTopSpeed * 1.3);
	}else if(getFloorCount() >= 40){
		setBoardSpeed(GoTopSpeed * 1.4);
	}else if(getFloorCount() >= 50){
		setBoardSpeed(GoTopSpeed * 1.5);
	}
}

void GameLayer::displayFloorNum(){
	_floorPosition += getBoardSpeed();
	CCString *floorString = CCString::createWithFormat("%d",getFloorCount());
	_floorLabel->setString(floorString->getCString());

}

void GameLayer::displayBloodCount(){
	CCString *bloodCountString;
	bloodCountString = CCString::createWithFormat("blood_count_%d.png",_bob->getBloodCount());
	CCSpriteFrame* bloodFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(bloodCountString->getCString());
	_bloodCount->setDisplayFrame(bloodFrame);
}

void GameLayer::updateBobAndBoard(float dt){
	_bob->update(dt);

	CCObject *objectItem;

	_isSomeBoardHitBob = false;

	CCARRAY_FOREACH(_boardObjects, objectItem){
		Board *board = (Board*)objectItem;
		board->setPosition(ccp(board->getPositionX(),board->getPositionY() + getBoardSpeed()));//boards move up every time
		if(board->getPositionY() >= BoardWillDisppearHigherThisNumber){//board gone if it higher than this number
			board->stopAllActions();
			board->setVisible(false);
			_boardObjects->removeObject(board,true);
			if(_boardObjects->count() <= SmallestCountBoard){//generate some boards if we only have few boards
				Board *lastBoard =(Board*)_boardObjects->objectAtIndex(_boardObjects->count() - 1);
				generateSomeBoards(lastBoard->getPositionY() - PerBoardHeight,BoardCountEveryTimeGenerate - SmallestCountBoard);
			}
		}else{//check board collide bobs
			if(board->getPositionY() >=0 && board->getPositionY() <= _bob->getPositionY()){
				board->collisionWithBob(_bob);
				if(board->checkCollision(_bob)){
					_isSomeBoardHitBob = true;
				}
			}

		}

	}
	if(!_isSomeBoardHitBob && _bob->getState() != kBobDie && _bob->getState() != kBobColliteWithNothing){// if no board hit bob, bob's state set to kBobFall
		_bob->setState(kBobFall);
	}
	//check hit the top star
	bool isHitTop = _topStarBoard->boundingBox().intersectsRect(_bob->getRect());
	if(isHitTop){
		_bob->setState(kBobHitTop);
	}
}

void GameLayer::checkGameOver(){
	if(_bob->getBloodCount() == 0){
		_bob->setState(kBobDie);
	}

	if(_bob->getPositionY() <= - (_bob->getHeight() / 2) ){
		_gameState = kGameOver;	
		saveHighestScore();// when game over, save the highest score	
	}
}

void GameLayer::saveHighestScore(){
	if(_changeHighScore == false){//save highest score
		PlayEffect(DieEffect);
		int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(HighScoreKey);
		if(getFloorCount() > highScore){
			CCUserDefault::sharedUserDefault()->setIntegerForKey(HighScoreKey,getFloorCount());
		}
		_changeHighScore = true;
	}
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	if(_gameState == kGameReady){
		_gameState = kGameRunning;
	}else if(_gameState == kGameOver){
		CCScene *newScene = CCTransitionMoveInL::create(0.2f,MenuLayer::scene());
		CCDirector::sharedDirector()->replaceScene(newScene);
	}
}

void GameLayer::pauseGame(CCObject *pSender){
	if(_gameState == kGameRunning){
		_gameState = kGamePause;
		_resumeMenu->setVisible(true);
		_pauseMenu->setVisible(false);
	}
	
}

void GameLayer::resumeGame(CCObject *pSender){
	_gameState = kGameRunning;
	_resumeMenu->setVisible(false);
	_pauseMenu->setVisible(true);
}

void GameLayer::backToMenuLayer(CCObject *pSender){
	CCScene *newScene = CCTransitionMoveInL::create(0.2f,MenuLayer::scene());
	CCDirector::sharedDirector()->replaceScene(newScene);
}