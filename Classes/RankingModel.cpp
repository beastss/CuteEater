#include "RankingModel.h"
#include <algorithm>
#include "GameConfig.h"
#include "CommonUtil.h"
USING_NS_CC;
using namespace std;
RankingModel *RankingModel::theModel()
{
	static RankingModel model;
	return &model;
}

void RankingModel::updateScore(std::string name, int score)
{
	m_rank[name] = score;
}

std::vector<std::pair<std::string, int>> RankingModel::getCurRank(int topNum)
{
	vector<pair<string, int>> rank;
	for (auto iter = m_rank.begin(); iter != m_rank.end(); ++iter)
	{
		rank.push_back(make_pair(iter->first, iter->second));
	}
	sort(rank.begin(), rank.end(), [=](pair<string, int> v1, pair<string, int> v2)
	{
		return v1.second > v2.second;
	});
	int endIndex = min((int)rank.size() , topNum);	
	if (endIndex > 0)
	{
		//CCLOG("cur_rank size: %d", m_rank.size());
		return vector<pair<string, int>>(rank.begin(), rank.begin() + endIndex);
	}
	else
	{
		//CCLOG("cur_rank size: %d", 0);
		return vector<pair<string, int>>();
	}

}

void RankingModel::removeRank(std::string name)
{
	auto it = find(m_deadname.begin(), m_deadname.end(), name);
	if ( it!= m_deadname.end())
	{
		m_deadname.erase(it);
	}
	else
	{
		m_deadname.push_back(name);
	}

}



void RankingModel::init()
{
	m_rank.clear();
	m_notUsedNames.clear();
	auto keys = GameConfigSelf->allKeys("ranking");
	for (size_t i = 0; i < keys.size(); ++i)
	{
		string name = GameConfigSelf->getStrValue("ranking", keys[i]);
		m_names.push_back(name);
	}
}

void RankingModel::reset()
{
	m_rank.clear();
	m_notUsedNames.clear();
	m_notUsedNames.assign(m_names.begin(), m_names.end());
	m_npcnames.clear();
	m_deadname.clear();


}

std::string RankingModel::applyName()
{
	if (m_notUsedNames.empty())
	{
		assert(false);
		return "skyFly";
	}
	int index = CommonUtil::getRandomValue(0, m_notUsedNames.size() - 1);
	string name = m_notUsedNames[index];
	m_notUsedNames.erase(m_notUsedNames.begin() + index);
	m_rank[name] = 0;
	return name;
}

void RankingModel::addNpcName(std::string name)
{ 
	m_npcnames.push_back(name);
}


std::string RankingModel::getNpcName(int id)
{
	return m_npcnames[id]; 
}