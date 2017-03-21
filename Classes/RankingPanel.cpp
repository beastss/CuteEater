#include "RankingPanel.h"
#include "UiLayout.h"
#include "cocos-ext.h"
#include "CommonUtil.h"
#include <utility>
#include "RankingModel.h"
#include "ActionRunner.h"
#include "PlayerData.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

const int RankingPanel::kRankingNodeNum = 4;
RankingPanel::RankingPanel()
{
	m_runner = ActionRunner::create();
	m_runner->retain();
}

RankingPanel::~RankingPanel()
{
	m_runner->clear();
	m_runner->release();
}

bool RankingPanel::init()
{
	/*
	CCScale9Sprite * scale9 = CCScale9Sprite::create("game_scene/ranking_bk.png");
	scale9->setAnchorPoint(ccp(0, 0));
	addChild(scale9);

	float width = 0;
	float height = 0;
	for (auto iter = m_ranking.begin(); iter != m_ranking.end(); ++iter)
	{
		auto node = UiLayout::create("layout/ranking_node.xml");
		auto name = dynamic_cast<CCLabelTTF *>(node->getChildById(1));
		name->setString((iter->second).c_str());
		auto score = dynamic_cast<CCLabelTTF *>(node->getChildById(2));
		score->setString(CommonUtil::intToStr(iter->first));
		node->setPosition(0, height);
		addChild(node);
		height += node->getContentSize().height;
		width = max(width, node->getContentSize().width);
	}
	scale9->setContentSize(CCSize(width, height));

	height += 10;
	auto title = UiLayout::create("layout/ranking_title.xml");
	CCScale9Sprite * titleBk = CCScale9Sprite::create("game_scene/ranking_bk.png");
	titleBk->setAnchorPoint(ccp(0, 0));
	addChild(titleBk);
	titleBk->setContentSize(ccpAdd(title->getContentSize(), ccp(0, 5)));
	titleBk->setPosition(ccp(0, height));

	title->setPosition(0, height);
	height += title->getContentSize().height;
	width = max(width, title->getContentSize().width);
	addChild(title);

	setContentSize(CCSize(width, height));
	scheduleUpdate();
	*/
	CCSize size = CCSize(250, 135);
	setContentSize(size);
	float height = size.height;

	auto title = UiLayout::create("layout/ranking_title.xml");
	CCScale9Sprite * titleBk = CCScale9Sprite::create("game_scene/ranking_bk.png");
	titleBk->setAnchorPoint(ccp(0, 0));
	addChild(titleBk);
	titleBk->setContentSize(ccpAdd(title->getContentSize(), ccp(0, 5)));
	height -= title->getContentSize().height + 5;
	titleBk->setPosition(ccp(0, height));

	title->setPosition(0, height);
	addChild(title);

	CCScale9Sprite * scale9 = CCScale9Sprite::create("game_scene/ranking_bk.png");
	scale9->setAnchorPoint(ccp(0, 1));
	height -= 4;
	scale9->setPosition(ccp(0, height));
	scale9->setContentSize(size);
	addChild(scale9);

	for (int i = 0; i < kRankingNodeNum; ++i)
	{
		auto node = UiLayout::create("layout/ranking_node.xml");
		auto name = dynamic_cast<CCLabelTTF *>(node->getChildById(1));
		name->setString("");
		auto score = dynamic_cast<CCLabelTTF *>(node->getChildById(2));
		score->setString("");
		auto rankNum = dynamic_cast<CCLabelAtlas *>(node->getChildById(3));
		rankNum->setString(CommonUtil::intToStr(i + 1));
		height -= node->getContentSize().height;
		node->setPosition(0, height);
		addChild(node);
		m_rankNodes.push_back(node);

		auto dimg = dynamic_cast<CCSprite *>(node->getChildById(4));
		dimg->setVisible(false);
	}

	schedule(schedule_selector(RankingPanel::onUpdate), 1.0f);
	onUpdate(0);
	return true;
}

UiLayout* RankingPanel::getRankingNode(int id)
{
	return m_rankNodes[id];

}

void RankingPanel::onUpdate(float dt)
{

	auto ranking = RankingModel::theModel()->getCurRank(kRankingNodeNum);
	m_runner->clear();
	string playerName = PlayerData::theData()->getName();
	for (size_t i = 0; i < ranking.size(); ++i)
	{
		auto data = ranking[i];
		auto dead = RankingModel::theModel()->getDeadName();
		auto dimg = dynamic_cast<CCSprite *>(m_rankNodes[i]->getChildById(4));
		dimg->setVisible(false);
		for (auto isecond = dead.begin(); isecond != dead.end(); isecond++)
		{
			if (data.first.compare(*isecond)==0)
			{

				auto dimg = dynamic_cast<CCSprite *>(m_rankNodes[i]->getChildById(4));
				dimg->setVisible(true);
			}
		}
		m_runner->queueAction(CallFuncAction::withFunctor([=]()
		{
			auto name = dynamic_cast<CCLabelTTF *>(m_rankNodes[i]->getChildById(1));
			name->setString((data.first).c_str());
			auto score = dynamic_cast<CCLabelTTF *>(m_rankNodes[i]->getChildById(2));
			score->setString(CommonUtil::intToStr(data.second));
			if (playerName == data.first)
			{
				name->setColor(ccc3(250, 150, 10));
				score->setColor(ccc3(250, 150, 10));
			}
			else
			{
				name->setColor(ccc3(250, 250, 250));
				score->setColor(ccc3(250, 250, 250));
			}


		}));
		m_runner->queueAction(DelayNFrames::delay(1));
	}
}

void RankingPanel::initData()
{
	/*
	m_ranking.insert(make_pair(350050, "a_kejge"));
	m_ranking.insert(make_pair(305020, "b_sdkf"));
	m_ranking.insert(make_pair(302050, "funny6"));
	m_ranking.insert(make_pair(300220, "april"));
	m_ranking.insert(make_pair(282000, "15jaes"));
	m_ranking.insert(make_pair(273050, "jasony"));
	m_ranking.insert(make_pair(260250, "tonny"));
	m_ranking.insert(make_pair(255400, "_godns"));
	*/
}