#ifndef __BOB_H__
#define __BOB_H__

#include "cocos2d.h"
#include "GameSprite.h"
USING_NS_CC;




typedef enum{
	kBobJump,
	kBobFall,
	kBobHitTop,
	kBobSuperMan,
	kBobOnBoard,
	kBobOnStarBoard,
	kBobDie,
	kBobOnRightRotateBoard,
	kBobOnLeftRotateBoard,
	kBobOnRollingBoard,
	kBobOnSpringBoard,
	kBobCollisionWithNothing
} BobState;

typedef enum{
	kBobLeft,
	kBobRight
} BobDirection;


class Bob : public GameSprite{
public:
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
	CC_SYNTHESIZE(bool,_isCanRunAction,IsCanRunAction);
	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(bool,_collisionWithNoThing,CollisionWithNoThing); //if true bob will not collide with board
	
	//CC_SYNTHESIZE(BobDirection, _direction, Direction);

	Bob(CCPoint position);
	~Bob(void);

	BobDirection getDirection()const;
	void setDirection(BobDirection direction);
	BobState getState()const;
	void setState(BobState state);
	void checkState();
	static Bob* create(CCPoint position);
	void resetVectorY();
	void changeToFall(float dt);
	void onNormalBoardAction();
	void setBobCollisionWithNothing(float dt,float totalTime);
	void update(float dt);

	inline int getBloodCount()const{
		return _bloodCount;
	}
	void setBloodCount(int bloodCount);

private:
	BobDirection _direction;
	BobState _state;
	int _bloodCount;
	CCRepeatForever *_fallAction;
	CCAction *_onRollingBoardAction;
	CCSpriteFrame *_dieSpriteFrame;
	void bobOnRollingBoardTimeOut();
};






#endif