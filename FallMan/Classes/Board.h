#ifndef _BOARD_H__
#define _BOARD_H__

#include "cocos2d.h"
#include "Bob.h"

USING_NS_CC;

typedef enum{
	kNormalBoard,      //0
	kRollingBoard,     //1
	kRotateLeftBoard,  //2
	kRotateRightBoard, //3
	kStarBoard,        //4
	kSpringBoard       //5
}BoardType;

 class Board : public GameSprite{

public:
	Board(BoardType type);
	~Board();
	CC_SYNTHESIZE(BoardType, _type, Type);
	CC_SYNTHESIZE(bool,_isCanRunAction,IsCanRunAction);

	static Board* create(BoardType type);
	bool checkCollision(Bob *bob);
	virtual bool init(void);
	virtual void collisionWithBob(Bob *bob);
};



#endif