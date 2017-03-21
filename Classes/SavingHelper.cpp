#include "SavingHelper.h"
USING_NS_CC;
using namespace std;

SavingHelper *SavingHelper::theHelper()
{
	static SavingHelper helper;
	return &helper;
}

void SavingHelper::saveName(std::string name)
{
	CCUserDefault::sharedUserDefault()->setStringForKey("name", name.c_str());
}

std::string SavingHelper::getName()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("name", "");
}

void SavingHelper::setBackgroundMusic(bool isOn)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("background_music", isOn);
}

bool SavingHelper::isBackgroundMusicOn()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("background_music", true);
}

void SavingHelper::setEffectMusic(bool isOn)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("effect_music", isOn);
}

bool SavingHelper::isEffectMusicOn()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("effect_music", true);
}
