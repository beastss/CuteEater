#ifndef _RANKING_DIALOG_H_
#define _RANKING_DIALOG_H_
#include "cocos2d.h"
#include "ScaleDialog.h"
#include "ListSlideView.h"

class UiLayout;
struct RankingData
{
	std::string name;
	int score;
	RankingData(std::string _name, int _score){ name = _name; score = _score; }
};

class RankingDialog
	: public ScaleDialog
{
public:
	CREATE_FUNC(RankingDialog);
private:
	virtual bool init();
	void initData();
	void initMyRanking();
	void addRankingNodes();
	void onBuyBtnClicked(cocos2d::CCObject* pSender);
	void onCloseBtnClicked(cocos2d::CCObject* pSender);
protected:
	RankingDialog();
private:
	UiLayout *m_layout;
	std::vector<RankingData> m_data;
	ListSlideView * m_list;
};
#endif