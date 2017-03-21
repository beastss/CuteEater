#include "HelpPanel.h"
#include "CommonUtil.h"
#include "CommonMacro.h"
#include "MainScene.h"
#include "SoundMgr.h"
USING_NS_CC;
using namespace std;
void HelpPanel::onEnter()
{
	BasePanel::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityPanel, true);
}

void HelpPanel::onExit()
{
	BasePanel::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool HelpPanel::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	initPanel();
	return true;
}

void HelpPanel::initPanel()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_helpTips = CCSprite::create("help/guide_1.png");
	m_helpTips->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_helpTips);

	CCMenuItem *backBtn = CommonUtil::getScaleMenuItemSpr("help/back.png");
	backBtn->setTarget(this, menu_selector(HelpPanel::onBackBtnClicked));
	backBtn->setPosition(ccp(winSize.width * 0.4f, -winSize.height * 0.4f));

	auto pMenu = CCMenu::create();
	pMenu->setTouchPriority(kTouchPriorityPanel - 1);
	pMenu->addChild(backBtn);
	addChild(pMenu);
}

void HelpPanel::onBackBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
}

void HelpPanel::onBackKeyTouched()
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
}

bool HelpPanel::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void HelpPanel::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	const float kDistance = 100;
	auto curPos = pTouch->getLocation();
	auto startPos = pTouch->getStartLocation();
	char str[100] = { 0 };
	if (curPos.x - startPos.x > kDistance)//ÏòÓÒ
	{
		if (m_curIndex > 1)
		{
			m_curIndex--;
			sprintf(str, "help/guide_%d.png", m_curIndex);
			m_helpTips->initWithFile(str);
		}
	}
	else if (startPos.x - curPos.x > kDistance)//Ïò×ó
	{
		if (m_curIndex < 3)
		{
			m_curIndex++;
			sprintf(str, "help/guide_%d.png", m_curIndex);
			m_helpTips->initWithFile(str);
		}
	}
}