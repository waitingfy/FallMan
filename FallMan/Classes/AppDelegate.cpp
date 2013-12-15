#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "AnimationManager.h"
#include "Constants.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
	sAnimationMgr->release();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	sAnimationMgr->initAnimationMap();

	preloadMusic();
    // create a scene. it's an autorelease object
    CCScene *pScene = MenuLayer::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}


void AppDelegate::preloadMusic(){
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BackGroundMusic);
	SimpleAudioEngine::sharedEngine()->preloadEffect(BuffleEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(ClickEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(CoinEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(DieEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(HighjumpEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(HitEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(JumpEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(NailEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(HitEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(SkateEffect);
	SimpleAudioEngine::sharedEngine()->preloadEffect(SpringEffect);

	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
}