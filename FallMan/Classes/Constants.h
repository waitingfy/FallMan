#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

//using namespace CocosDenshion;

const char HighScoreKey[] = "highscore";
const char SoundEnableKey[] = "soundEnable";
const int BoardCountEveryTimeGenerate = 20;
const int SmallestCountBoard = 10;            //when we reach this count, we will generate some boards
const int BoardWillDisppearHigherThisNumber = 440;
const float GoTopSpeed = 0.9f;
const int PerBoardHeight = 80;

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
const char BackGroundMusic[] = "background.ogg";
const char BuffleEffect[] = "buffle.ogg";
const char ClickEffect[] = "click.ogg";
const char CoinEffect[] = "coin.ogg";
const char DieEffect[] = "die.ogg";
const char HighjumpEffect[] = "highjump.ogg";
const char HitEffect[] = "hit.ogg";
const char JumpEffect[] = "jump.ogg";
const char NailEffect[] = "nail.ogg";
const char SkateEffect[] = "skate.ogg";
const char SpringEffect[] = "spring.ogg";

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
const char BackGroundMusic[] = "background.mp3";
const char BuffleEffect[] = "buffle.wav";
const char ClickEffect[] = "click.wav";
const char CoinEffect[] = "coin.wav";
const char DieEffect[] = "die.wav";
const char HighjumpEffect[] = "highjump.wav";
const char HitEffect[] = "hit.wav";
const char JumpEffect[] = "jump.wav";
const char NailEffect[] = "nail.wav";
const char SkateEffect[] = "skate.wav";
const char SpringEffect[] = "spring.wav";

#endif

#define PlayEffect(varName) \
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(SoundEnableKey,true)){ \
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(varName);}\

#endif