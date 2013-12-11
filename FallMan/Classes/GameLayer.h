#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "Bob.h"
#include "Board.h"
using namespace std;

enum{
	kBackground,
	kMiddleground,
	kForeground
};

typedef enum{
	kGameReady,
	kGameRunning,
	kGamePause,
	kGameOver
} GameState;


class GameLayer : public cocos2d::CCLayer
{
public:
	GameLayer();
	~GameLayer();

	CC_SYNTHESIZE(float, _boardSpeed,BoardSpeed);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
	void leftMove(CCObject* pSender);
	void rightMove(CCObject* pSender);
	int getFloorCount();
	void generateSomeBoard(int startPosition,int count);
	void update(float dt);
	void pauseGame(CCObject *pSender);
	void resumeGame(CCObject *pSender);
	void backToMenuLayer(CCObject *pSender);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	
private:
	GameState _gameState;
	CCSprite *_gameReady;
	CCSprite *_gameOver;
	CCSize _screenSize;
	Bob *_bob;
	CCArray *_boardObjects;
	CCSprite *_bloodCount;
	CCSprite *_topStarBoard;
	CCMenu *_navigationMenu;
	CCMenu *_pauseMenu;
	CCMenu *_resumeMenu;
	int _currentBoardTypeIndex;
	int _startPosition;
	Board *_boardItem;
	CCSpriteBatchNode *_gameBatchNode;
	float _floorPosition;
	int _floor;
	CCLabelTTF *_floorLabel;
	int _levelIndex;
	bool _isSomeBoardHitBob;             //true means some board hit bob

	CCParallaxNode *_rootNode;
	Board *normalBoard;
	Board *starBoard;
	Board *rollingBoard;
	Board *rotateLeftBoard;
	Board *springBoard;
	bool _changeHighScore;
	void changeSpeedWithFloorCount();
	void displayFloorNum();
	void displayBloodCount();
	void updateBobAndBoard();
	void checkGameOver();
	void getNextBoardIndex(int &levelIndex,vector<int> &levelVector);
};

#endif  // __HELLOWORLD_SCENE_H__