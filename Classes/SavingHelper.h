#ifndef __SAVING_HELPER_H__
#define __SAVING_HELPER_H__
#include "cocos2d.h"
class SavingHelper
{
public:
	static SavingHelper *theHelper();
public:
	void saveName(std::string name);
	void setBackgroundMusic(bool isOn);
	void setEffectMusic(bool isOn);
public:
	std::string getName();
	bool isBackgroundMusicOn();
	bool isEffectMusicOn();
};

#define	SAVING SavingHelper::theHelper()
#endif