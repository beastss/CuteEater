#ifndef _SOUNDMGR_H_
#define _SOUNDMGR_H_
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <map>
enum BackGroundMusic
{
	kBackGroundMusicMain
};
enum EffectMusic
{
	kEffectMusicButton,
};

class SoundMgr 
{
public:
	static SoundMgr *theMgr();
	void init();

	void playBackground();
	void playEffect(int effectType);

	void setBackgroundMusic(bool isOn);
	void setEffectMusic(bool isOn);

	bool isBackgroundMusicOn();
	bool isEffectMusicOn();
private:
	SoundMgr() :m_backgroundMusicOn(true), m_effectMusicOn(true){}
	~SoundMgr();
private:
	std::map<int, std::string> m_backgroundMusic;
	std::map<int, std::string> m_effectMusic;
	bool m_backgroundMusicOn;
	bool m_effectMusicOn;
};



#endif