#include "PlayerData.h"
#include "CommonMacro.h"
#include "GameConfig.h"
#include "SavingHelper.h"
#include "CommonUtil.h"
USING_NS_CC;
using namespace std;

PlayerData *PlayerData::theData()
{
	static PlayerData mgr;
	return &mgr;
}

void PlayerData::reset()
{
	m_data = SnakeData();
	m_rebornid.clear();
}

std::string PlayerData::getName()
{
	auto userId = AndroidIter::getIter()->getUserId();
	if (userId.empty())
	{
		auto name = SAVING->getName();
		if (name.empty())
		{
			name = GameConfigSelf->getStrValue("common", "player_name");
			for (int i = 0; i < 5; ++i)
			{
				name += CommonUtil::intToStr(CommonUtil::getRandomValue(0, 9));
			}
			SAVING->saveName(name.c_str());
		}
		return name;
	}
	else
	{
		auto name = GameConfigSelf->getStrValue("common", "player_name");
		name += userId;
		SAVING->saveName(name.c_str());
		name = SAVING->getName();
		return name;


	}
	
}
