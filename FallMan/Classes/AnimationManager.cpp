#include "AnimationManager.h"
#include "Bob.h"

DECLARE_SINGLETON_MEMBER(AnimationManager);

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
	//CCDirector会自己清除AnimationCache
	//CCAnimationCache::purgeSharedAnimationCache();
	CC_SAFE_RELEASE(_gameBatchNode);
}


bool AnimationManager::initAnimationMap()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite_sheet.plist");
	_gameBatchNode = CCSpriteBatchNode::create("sprite_sheet.png");
	_gameBatchNode->retain();
	char temp[20];
	sprintf(temp, "%d", aFall);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createBobFallAnimation(),temp);
	sprintf(temp, "%d", aOnNormalBoardLeft);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createBobOnNormalBoardLeftAnimation(),temp);
	sprintf(temp, "%d", aOnNormalBoardRight);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createBobOnNormalBoardRightAnimation(),temp);
	sprintf(temp, "%d", aOnStarBoardLeft);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createBobOnStarBoardLeftAnimation(),temp);
	sprintf(temp, "%d", aOnStarBoardRight);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createBobOnStarBoardRightAnimation(),temp);
	sprintf(temp, "%d", aRollingBoard);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createRollingBoardAnimation(),temp);
	sprintf(temp, "%d", aRotateLeftBoard);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createRotateLeftBoardAnimation(),temp);
	sprintf(temp, "%d", aRotateRightBoard);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createRotateRightBoardAnimation(),temp);
	sprintf(temp, "%d", aSpringBoard);
	CCAnimationCache::sharedAnimationCache()->addAnimation(createSpringBoardAnimation(),temp);
	return true;
}

//获取指定动画模版
CCAnimation* AnimationManager::getAnimation(int key){
	char temp[20];
	sprintf(temp, "%d", key);
	return CCAnimationCache::sharedAnimationCache()->animationByName(temp);
}

//获取一个指定动画模版的实例
CCAnimate* AnimationManager::createAnimate(int key){
	//获取指定动画模版
	CCAnimation* anim = getAnimation(key);
	if(anim){
		//根据动画模版生成一个动画实例
		return cocos2d::CCAnimate::create(anim);
	}
	return NULL;
}

//获取一个指定动画模版的实例
CCAnimate* AnimationManager::createAnimate(const char* key){
	//获取指定动画模版
	CCAnimation* anim = CCAnimationCache::sharedAnimationCache()->animationByName(key);
	if(anim){
		//根据动画模版生成一个动画实例
		return cocos2d::CCAnimate::create(anim);
	}
	return NULL;
}



CCAnimation* AnimationManager::createBobFallAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 3; ++i){
		name = CCString::createWithFormat("bob_fall_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.05f);	
	return animation;
}

CCAnimation* AnimationManager::createBobOnNormalBoardLeftAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 3; ++i){
		name = CCString::createWithFormat("bob_walk_left_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.1f);
	return animation;
}

CCAnimation* AnimationManager::createBobOnNormalBoardRightAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 3; ++i){
		name = CCString::createWithFormat("bob_walk_right_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.1f);
	return animation;
}

CCAnimation* AnimationManager::createBobOnStarBoardLeftAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 3; ++i){
		name = CCString::createWithFormat("bob_on_star_left_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.1f);
	return animation;
}

CCAnimation* AnimationManager::createBobOnStarBoardRightAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 3; ++i){
		name = CCString::createWithFormat("bob_on_star_right_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.1f);
	return animation;
}


CCAnimation* AnimationManager::createRollingBoardAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 6; ++i){
		name = CCString::createWithFormat("rolling_board_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.08f);
	animation->setRestoreOriginalFrame(true);
	return animation;
}

CCAnimation* AnimationManager::createRotateLeftBoardAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 4; ++i){
		name = CCString::createWithFormat("rotate_left_board_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.08f);
	return animation;
}

CCAnimation* AnimationManager::createRotateRightBoardAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 4; ++i){
		name = CCString::createWithFormat("rotate_right_board_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.08f);
	return animation;
}

CCAnimation* AnimationManager::createSpringBoardAnimation(){
	CCAnimation *animation;
	animation = CCAnimation::create();
	CCSpriteFrame *frame;
	CCString *name;
	for(int i = 0; i < 3; ++i){
		name = CCString::createWithFormat("spring_board_%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.08f);
	animation->setRestoreOriginalFrame(true);
	return animation;
}