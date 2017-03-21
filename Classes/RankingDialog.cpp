#include "RankingDialog.h"
#include "SoundMgr.h"
#include "UiLayout.h"
#include "CommonUtil.h"
#include<algorithm>
#include "GameConfig.h"
USING_NS_CC;
using namespace std;

RankingDialog::RankingDialog()
{

}

bool RankingDialog::init()
{
	m_layout = UiLayout::create("layout/ranktitl_panel.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);
	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(4));
	closeBtn->setTarget(this, menu_selector(RankingDialog::onCloseBtnClicked));

	initData();
	addRankingNodes();
	initMyRanking();
	return true;
}

void RankingDialog::initMyRanking()
{
	auto iter = find_if(m_data.begin(), m_data.end(), [=](RankingData data)->bool
	{
		return data.name == "ME";
	});
	
	int myRank = iter - m_data.begin() + 1;
	if (myRank == m_data.size())
	{
		int topScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("PlayerMaxScore",0);
		myRank = 600000 - topScore * 20 + CommonUtil::getRandomValue(0, 500);
	}
	
	CCLabelTTF *curRank = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(6));
	curRank->setColor(ccc3(255, 255, 255));
	char str[100] = { 0 };
	sprintf(str, curRank->getString(), myRank);
	curRank->setString(str);
	CCLabelTTF *score = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(8));
	score->setColor(ccc3(255, 255, 255));
	char strs[100] = { 0 };
	sprintf(strs, score->getString(), CCUserDefault::sharedUserDefault()->getIntegerForKey("PlayerMaxScore", 0));
	score->setString(strs);

}

void RankingDialog::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
}

void RankingDialog::onCloseBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	removeFromParent();
}

void RankingDialog::initData()
{
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name1"), GameConfigSelf->getIntValue("ranktitle", "player_score1")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name2"), GameConfigSelf->getIntValue("ranktitle", "player_score2")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name3"), GameConfigSelf->getIntValue("ranktitle", "player_score3")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name4"), GameConfigSelf->getIntValue("ranktitle", "player_score4")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name5"), GameConfigSelf->getIntValue("ranktitle", "player_score5")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name6"), GameConfigSelf->getIntValue("ranktitle", "player_score6")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name7"), GameConfigSelf->getIntValue("ranktitle", "player_score7")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name8"), GameConfigSelf->getIntValue("ranktitle", "player_score8")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name9"), GameConfigSelf->getIntValue("ranktitle", "player_score9")));
	m_data.push_back(RankingData(GameConfigSelf->getStrValue("ranktitle", "player_name10"), GameConfigSelf->getIntValue("ranktitle", "player_score10")));
	m_data.push_back(RankingData("ME", CCUserDefault::sharedUserDefault()->getIntegerForKey("PlayerMaxScore", 0)));

	sort(m_data.begin(), m_data.end(), [=](RankingData data1, RankingData data2)->bool
	{
		return data1.score > data2.score;
	});
}

void RankingDialog::addRankingNodes()
{
	const float kSpacing = 3;
	float curHeight = 650;
	auto size = getContentSize();
	const int rankNum = 10;
	m_list = ListSlideView::create(ccp(500,270));
	m_list->setTouchPriority(-256);
	m_list->setAnchorPoint(ccp(0.51f, 1));
	m_list->setPosition(ccp(size.width*0.5, size.height*0.75));
	m_list->setSpacing(0, 10);
	m_list->setColumnSize(1);
	for (int i = 0; i < rankNum; ++i)
	{
		auto node = UiLayout::create("layout/ranktitl_node.xml");
		CCLabelAtlas *rankingNum = dynamic_cast<CCLabelAtlas *>(node->getChildById(2));
		rankingNum->setString(CommonUtil::intToStr(i + 1));
		CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>(node->getChildById(3));
		nameLabel->setString(m_data[i].name.c_str());
		CCLabelTTF *scoreLabel = dynamic_cast<CCLabelTTF *>(node->getChildById(4));
		scoreLabel->setString(CommonUtil::intToStr(m_data[i].score));

		//node->setAnchorPoint(ccp(0.5f, 0.5f));
		//m_layout->addChild(node);
		//node->setPosition(ccp(size.width * 0.5f, curHeight));
		curHeight -= node->getContentSize().height + kSpacing;
		m_list->addNode(node);

		bool isPlayer = m_data[i].name == "ME";
		node->getChildById(1)->setVisible(!isPlayer);
		node->getChildById(5)->setVisible(isPlayer);
	}
	m_layout->addChild(m_list);
}