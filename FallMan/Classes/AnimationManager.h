#ifndef _ANIMATION_MANAGER_H_
#define _ANIMATION_MANAGER_H_

#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;

enum{
	aFall,
	aOnNormalBoardLeft,
	aOnNormalBoardRight,
	aOnStarBoardLeft,
	aOnStarBoardRight,
	aRollingBoard,
	aRotateLeftBoard,
	aRotateRightBoard,
	aSpringBoard,
	aOnRollingBoard
};


class AnimationManager : public Singleton<AnimationManager>{
public:
	AnimationManager();
	~AnimationManager();
	//初始化动画模版缓存表
	bool initAnimationMap();
	//根据名字得到一个动画模板
	CCAnimation* getAnimation(int key);
	//创建一个动画实例
	CCAnimate* createAnimate(int key);
	//创建一个动画实例
	CCAnimate* createAnimate(const char* key);
private:
	CCSpriteBatchNode *_gameBatchNode;
	CCAnimation* createBobFallAnimation();
	CCAnimation* createBobOnNormalBoardLeftAnimation();
	CCAnimation* createBobOnNormalBoardRightAnimation();
	CCAnimation* createBobOnStarBoardLeftAnimation();
	CCAnimation* createBobOnStarBoardRightAnimation();
	CCAnimation* createRollingBoardAnimation();
	CCAnimation* createRotateLeftBoardAnimation();
	CCAnimation* createRotateRightBoardAnimation();
	CCAnimation* createSpringBoardAnimation();
};

//定义动画管理器实例的别名
#define sAnimationMgr AnimationManager::instance()

#endif