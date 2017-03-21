#include "SoundMgr.h"
#include "cocos2d.h"
#include "SavingHelper.h"
USING_NS_CC;
using namespace CocosDenshion;

SoundMgr *SoundMgr::theMgr()
{
	static SoundMgr mgr;
	return &mgr;
}

void SoundMgr::init()
{
	m_backgroundMusic[kBackGroundMusicMain] = "sounds/background.ogg";
	m_effectMusic[kEffectMusicButton] = "sounds/button.ogg";

	auto audioMgr = SimpleAudioEngine::sharedEngine();
	for (auto iter = m_backgroundMusic.begin(); iter != m_backgroundMusic.end(); ++iter)
	{
		audioMgr->preloadBackgroundMusic(iter->second.c_str());
	}

	for (auto iter = m_effectMusic.begin(); iter != m_effectMusic.end(); ++iter)
	{
		SimpleAudioEngine::sharedEngine()->preloadEffect(iter->second.c_str());
	}
	
	playBackground();
	setBackgroundMusic(SAVING->isBackgroundMusicOn());
	setEffectMusic(SAVING->isEffectMusicOn());
}

void SoundMgr::playBackground()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_backgroundMusic[kBackGroundMusicMain].c_str(), true);
}

void SoundMgr::playEffect(int effectType)
{
	if (m_effectMusicOn)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(m_effectMusic[effectType].c_str());
	}
}

void SoundMgr::setBackgroundMusic(bool isOn)
{
	if (isOn)
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	SAVING->setBackgroundMusic(isOn);
	m_backgroundMusicOn = isOn;
}

void SoundMgr::setEffectMusic(bool isOn)
{
	if (isOn)
	{
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	}
	SAVING->setEffectMusic(isOn);
	m_effectMusicOn = isOn;
}

bool SoundMgr::isBackgroundMusicOn()
{
	return SAVING->isBackgroundMusicOn();
}

bool SoundMgr::isEffectMusicOn()
{
	return SAVING->isEffectMusicOn();
}

SoundMgr::~SoundMgr()
{
	SimpleAudioEngine::sharedEngine()->end();
}
