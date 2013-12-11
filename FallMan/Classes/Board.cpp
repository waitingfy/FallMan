#include "Board.h"
#include "AnimationManager.h"

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
	if(bob->getCollisionWithNoThing() == true)
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
			//bob->setPosition(ccp(bob->getPositionX(),bob->getHeight() / 2 + top()));
			bob->setState(kBobOnRollingBoard);
			if(getIsCanRunAction()){
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

bool Board::overLapRectangles(CCRect r1, CCRect r2){
	if(r1.getMinX() < r2.getMinX() + r2.size.width &&
		r1.getMidX() + r1.size.width > r2.getMidX() &&
		r1.getMidY() < r2.getMidY() + r2.size.height &&
		r1.getMidY() + r1.size.height > r2.getMidY())
		return true;
	else
		return false;
}