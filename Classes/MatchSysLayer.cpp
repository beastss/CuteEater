#include "MatchSysLayer.h"
#include "CommonUtil.h"
#include "PlayerData.h"
#include "RankingModel.h"
#include "MainScene.h"
using namespace CommonUtil;
float waittime[] = { 2.98, 1.229, 1.596, 0.82, 2.33, 2.425, 1.77 };
MatchSysLayer::MatchSysLayer() :icount(0)
{
	RankingModel::theModel()->reset();
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_matchlayer = UiLayout::create("layout/match_layer.xml");
	m_matchlayer->setPosition(ccp(0,0));
	addChild(m_matchlayer);
	m_characterid=buildRandomSequence(3);
	for (int i = 0; i < 3; i++)
	{
		npcmatchtime.push_back(waittime[getRandomValue(0, 6)]);
		CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>(m_matchlayer->getChildById(13 + i));
		nameLabel->setColor(ccc3(72, 49, 32));


	}
	initPlayer();
	scheduleUpdate();

		CCSprite *dian1 = dynamic_cast<CCSprite *>(m_matchlayer->getChildById(19 ));
		dian1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0), CCDelayTime::create(0.4),CCFadeIn::create(0.7), CCDelayTime::create(1.4), NULL)));
		CCSprite *dian2 = dynamic_cast<CCSprite *>(m_matchlayer->getChildById(20));
		dian2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0), CCDelayTime::create(1.1), CCFadeIn::create(0.7), CCDelayTime::create(0.7), NULL)));
		CCSprite *dian3 = dynamic_cast<CCSprite *>(m_matchlayer->getChildById(21));
		dian3->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0), CCDelayTime::create(1.8), CCFadeIn::create(0.7), CCDelayTime::create(0), NULL)));
		



	
}

MatchSysLayer::~MatchSysLayer()
{

}

void MatchSysLayer::update(float dt)
{
	if (icount < 3){

		for (auto it = npcmatchtime.begin(); it != npcmatchtime.end();)
		{

			*it -= dt;
			if (*it <= 0&&*it!=6.6)
			{
				int res = it - npcmatchtime.begin();
				switchOn(res);
				icount++;
				//it = npcmatchtime.erase(it);
				*it = 6.6;
				++it;
			}

			else
			{
				++it;
			}

		}

	}
	else
	{
		CCSprite *img = dynamic_cast<CCSprite *>(m_matchlayer->getChildById(18));
		img->initWithFile("match/starting.png");
		scheduleOnce(schedule_selector(MatchSysLayer::starGame),2.1);
			

	}
	
}

void MatchSysLayer::starGame(float dt)
{
	PlayerData::theData()->setNpcData(m_npcname, m_characterid);
	MainScene::theScene()->showPanel(kPanelIdGamePanel);
	removeFromParent();
}

void MatchSysLayer::switchOn(int id)
{

	auto name = RankingModel::theModel()->applyName();
	RankingModel::theModel()->addNpcName(name);
	CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>(m_matchlayer->getChildById(13+id));
	nameLabel->setColor(ccc3(72, 49, 32));
	nameLabel->setString(name.c_str());
	CCSprite *t_img = dynamic_cast<CCSprite *>(m_matchlayer->getChildById(10 + id));
	char str[100] = { 0 };
	sprintf(str, "sprite_frames/pic_%d-1.png", m_characterid[id+1]);
	t_img->initWithFile(str);

}

void MatchSysLayer::initPlayer()
{
	/*auto name = PlayerData::theData()->getName();
	CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>(m_matchlayer->getChildById(6));
	nameLabel->setColor(ccc3(0, 0, 0));
	nameLabel->setString(name.c_str());
	CCSprite *t_img = dynamic_cast<CCSprite *>(m_matchlayer->getChildById(9));
	char str[100] = { 0 };
	sprintf(str, "sprite_frames/pic_%d-1.png", m_characterid[0]);
	t_img->initWithFile(str);*/
}