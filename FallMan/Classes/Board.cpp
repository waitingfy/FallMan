#include "Board.h"
#include "AnimationManager.h"
#include "Constants.h"

Board::Board(BoardType type){
	_width = 68;
	_height = 18;
	_type = type;
}

Board::~Board(){

}

Board* Board::create(BoardType type){
	Board *sprite = new Board(type);
	if(sprite && sprite->init()){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}


bool Board::init(){
	bool result;
	switch(getType()){
	case kNormalBoard:
		result = this->initWithSpriteFrameName("board.png");
		break;
	case kRollingBoard:
		result = this->initWithSpriteFrameName("rolling_board_0.png");
		setIsCanRunAction(true);
		break;
	case kRotateLeftBoard:
		result = this->initWithSpriteFrameName("rotate_left_board_0.png");
		this->stopAllActions();
		this->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRotateLeftBoard)));
		break;
	case kRotateRightBoard:
		result = this->initWithSpriteFrameName("rotate_right_board_0.png");
		this->stopAllActions();
		this->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRotateRightBoard)));
		break;
	case kStarBoard:
		result = this->initWithSpriteFrameName("stab_board.png");
		break;
	case kSpringBoard:
		result = this->initWithSpriteFrameName("spring_board_0.png");
		break;
	}
	return result;
}



bool Board::checkCollision(Bob *bob){
	if(bob->getState() == kBobColliteWithNothing || bob->getState() == kBobDie)
		return false;

	if(bob->left() <= this->right() && bob->right() >= this->left()
		&& bob->bottom() <= this->top() && bob->top() >= this->bottom()){
			return true;
	}else{
		return false;
	}
}

void Board::collisionWithBob(Bob *bob){
	if(checkCollision(bob)){
		switch(getType()){
		case kNormalBoard:
			bob->setPosition(ccp(bob->getPositionX(),bob->getHeight() / 2 + top()));
			bob->setState(kBobOnBoard);
			break;
		case kRollingBoard:
			bob->setPosition(ccp(bob->getPositionX(),bob->getHeight() / 2 + top()));
			bob->setState(kBobOnRollingBoard);
			if(getIsCanRunAction()){
				PlayEffect(SkateEffect);
				this->stopAllActions();
				this->runAction(sAnimationMgr->createAnimate(aRollingBoard));
				setIsCanRunAction(false);
			}
			break;
		case kRotateLeftBoard:
			bob->setPosition(ccp(bob->getPositionX(),bob->getHeight() / 2 + top()));
			bob->setState(kBobOnLeftRotateBoard);
			break;
		case kRotateRightBoard:
			bob->setPosition(ccp(bob->getPositionX(),bob->getHeight() / 2 + top()));
			bob->setState(kBobOnRightRotateBoard);
			break;
		case kStarBoard:
			bob->setPosition(ccp(bob->getPositionX(),bob->getHeight() / 2 + top()));
			bob->setState(kBobOnStarBoard);
			break;
		case kSpringBoard:
			bob->setState(kBobOnSpringBoard);
			this->stopAllActions();
			this->runAction(sAnimationMgr->createAnimate(aSpringBoard));
			break;
		}
	}

	
}

