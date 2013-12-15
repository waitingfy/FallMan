#include "Bob.h"
#include "AnimationManager.h"

const int WORLD_Y_GRAVITY = -45;


Bob::Bob(CCPoint position):_state(kBobFall){
	setPosition(position);
	resetVectorY();
	setIsCanRunAction(true);
	_width = 20;//change from 26,because bob's two feet size is smaller
	_height = 30;
	_bloodCount = 12;

	_onRollingBoardAction = CCSequence::create(
		CCDelayTime::create(0.5f),
		CCCallFunc::create(this,callfunc_selector(Bob::changeToCollideNothing)),
		CCDelayTime::create(0.8f),
		CCCallFunc::create(this,callfunc_selector(Bob::changeToFall)),
		NULL
		);
	_onRollingBoardAction->retain();

	_dieSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bob_die.png");
	_dieSpriteFrame->retain();
}

Bob::~Bob(void){
	CC_SAFE_RELEASE(_onRollingBoardAction);
	CC_SAFE_RELEASE(_dieSpriteFrame);
}

BobDirection Bob::getDirection() const{
	return _direction;
}

void Bob::setDirection(BobDirection direction){
	setIsCanRunAction(true);
	if(direction == kBobLeft){
		setVector(ccp(-60,this->getVector().y));
	}else{
		setVector(ccp(60,this->getVector().y));
	}
	
	_direction = direction;
}

BobState Bob::getState()const{
	return _state;
}

void Bob::setState(BobState newState){
	bool isANewState = getState() != newState;

	if(isANewState){
		setIsCanRunAction(true);
	}
	if(isANewState && (newState == kBobOnStarBoard || newState == kBobHitTop)){
		setBloodCount(getBloodCount() - 5);
	}
	if(isANewState && (newState == kBobOnBoard || newState == kBobOnLeftRotateBoard ||
		newState == kBobOnRightRotateBoard || newState == kBobOnRollingBoard || newState == kBobOnSpringBoard)){
		setBloodCount(getBloodCount() + 1);
	}
	_state = newState;
	
}


Bob* Bob::create(CCPoint position){
	Bob* sprite = new Bob(position);
	if(sprite && sprite->initWithSpriteFrameName("bob_fall_0.png") ){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Bob::resetVectorY(){
	setVector(ccp(getVector().x,WORLD_Y_GRAVITY));
}

void Bob::checkState(){
	CCLog("checkState:%d",(int)getState());

	switch(getState()){
	case kBobJump:
		break;
	case kBobFall:
		resetVectorY();
		if(getIsCanRunAction()){
			this->stopAllActions();
			_fallAction = CCRepeatForever::create((CCActionInterval*)sAnimationMgr->createAnimate(aFall));
			this->runAction(_fallAction);
			setIsCanRunAction(false);
		}
		
		break;
	case kBobHitTop:
		this->setVector(ccp(getVector().x, getVector().y - 1000));
		break;
	case kBobSuperMan:
		break;
	case kBobOnBoard:
		this->setVector(ccp(getVector().x, 0));
		onNormalBoardAction();
		break;
	case kBobOnStarBoard:
		this->setVector(ccp(getVector().x, 0));
		if(getIsCanRunAction()){
			this->stopAllActions();	
		   if(this->getVector().x < 0){
			  this->runAction(sAnimationMgr->createAnimate(aOnStarBoardLeft));
		   }else{
			  this->runAction(sAnimationMgr->createAnimate(aOnStarBoardRight));
		   }
		   setIsCanRunAction(false);
		}
		break;
	case kBobDie:
		this->setDisplayFrame(_dieSpriteFrame);
		setVector(ccp(getVector().x,WORLD_Y_GRAVITY * 4));
		break;
	case kBobOnRightRotateBoard:
		this->setVector(ccp(getVector().x + 3, 0));
		onNormalBoardAction();
		break;
	case kBobOnLeftRotateBoard:
		this->setVector(ccp(getVector().x - 3, 0));
		onNormalBoardAction();
		break;
	case kBobOnRollingBoard:
		this->setVector(ccp(getVector().x, 0));
		if(getIsCanRunAction()){
			this->stopAllActions();	
			this->runAction(_onRollingBoardAction);
			setIsCanRunAction(false);
		}
		break;
	case kBobOnSpringBoard:
		this->setVector(ccp(getVector().x,getVector().y + 1000));
		break;
	case kBobColliteWithNothing:
		resetVectorY();
		break;
	}
}

void Bob::setBloodCount(int bloodCount){
	if(bloodCount > 12){
		bloodCount = 12;
	}
	if(bloodCount <= 0){
		CCLOG("bob die!!!!!!!!");
		setState(kBobDie);
		bloodCount = 0;
	}
	_bloodCount = bloodCount;
}

void Bob::onNormalBoardAction(){
	if(getIsCanRunAction()){
		this->stopAllActions();
		if(this->getVector().x < 0){
			this->runAction(sAnimationMgr->createAnimate(aOnNormalBoardLeft));
		}else{
			this->runAction(sAnimationMgr->createAnimate(aOnNormalBoardRight));
		}
		setIsCanRunAction(false);
	}
}


void Bob::update(float dt){
	
	checkState();

	setVector(ccp(getVector().x * 0.90,getVector().y ));

	setNextPosition(ccp(getPositionX() + getVector().x * dt,
		             getPositionY() + getVector().y * dt));

	setPosition(getNextPosition());

}

void Bob::changeToFall(){
	setState(kBobFall);
}

void Bob::changeToCollideNothing(){
	CCLOG("changeToCollideNothing");
	setState(kBobColliteWithNothing);
}
