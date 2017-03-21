#ifndef __RANKING_PANEL_H__
#define __RANKING_PANEL_H__
#include "cocos2d.h"
class UiLayout;
class ActionRunner;
class RankingPanel
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(RankingPanel);
	~RankingPanel();
private:
	RankingPanel();
	UiLayout* getRankingNode(int id);
	virtual bool init();
	void initData();
	void onUpdate(float dt);
private:
	std::vector<UiLayout *>m_rankNodes;
	static const int kRankingNodeNum;
	ActionRunner *m_runner;
};

#endif