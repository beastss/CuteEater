#include "MenuPanel.h"
#include "CommonMacro.h"
#include "UiLayout.h"
#include "MainScene.h"
#include "PackageDialog.h"
#include "SettingDialog.h"
#include "SoundMgr.h"
#include "AndroidIter.h"
#include "PlayerData.h"
#include "MatchSysLayer.h"
#include "RankingDialog.h"
#include "RuleDialog.h"
#include "ComplaintDialog.h"
using namespace std;
USING_NS_CC;

bool MenuPanel::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);
	auto bk = CCLayerColor::create(ccc4(175, 175, 175, 255));
	addChild(bk);
	m_layout = UiLayout::create("layout/menu_panel.xml");
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	m_layout->setMenuTouchPriority(kTouchPriorityPanel);
	addChild(m_layout);
	MainScene::theScene()->showDialog(PackageDialog::create());

	CCMenuItem *newGameBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(1));
	newGameBtn->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCScaleTo::create(0.8f, 0.88),
		CCScaleTo::create(0.7f, 1),
		NULL)
		));
	newGameBtn->setTarget(this, menu_selector(MenuPanel::onNewGameBtnClicked));
	CCMenuItem *ruleBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(2));
	ruleBtn->setTarget(this, menu_selector(MenuPanel::onRuleBtnClicked));
	//CCMenuItem *skinBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(3));
	//skinBtn->setTarget(this, menu_selector(MenuPanel::onSkinBtnClicked));
	CCMenuItem *settingBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(4));
	settingBtn->setTarget(this, menu_selector(MenuPanel::onSettingBtnClicked));
	CCMenuItem *comBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(12));
	comBtn->setTarget(this, menu_selector(MenuPanel::onComplaintBtnClicked));


//	skinBtn->setVisible(false);
	CCMenuItem *libaoBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(10));
	libaoBtn->setTarget(this, menu_selector(MenuPanel::onLibaoClicked));
	libaoBtn->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCJumpBy::create(1.5f, CCPointZero, 25, 4),
		CCScaleTo::create(2.4f, 1),
		NULL)
		));
	
	
	
	
	auto name = PlayerData::theData()->getName();
	CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(6));
	nameLabel->setColor(ccc3(0, 0, 0));
	nameLabel->setString(name.c_str());

	bool forBusiness = AndroidIter::getIter()->isForBusiness();
	CCLabelTTF *phoneLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	phoneLabel->setColor(ccc3(0, 0, 0));
	phoneLabel->setVisible(true);
	if (forBusiness)
	{
		phoneLabel->setOpacity(255);
	}


    return true;
}

void MenuPanel::onComplaintBtnClicked(cocos2d::CCObject * pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(ComplaintDialog::create());
}

void MenuPanel::onNewGameBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MatchSysLayer * matchlayer = MatchSysLayer::create();
	addChild(matchlayer, 99);
	//MainScene::theScene()->showPanel(kPanelIdGamePanel);
}

void MenuPanel::onRuleBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(RuleDialog::create());
}

void MenuPanel::onSkinBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
}

void MenuPanel::onSettingBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(RankingDialog::create());
	//MainScene::theScene()->showDialog(SettingDialog::create());
}

void MenuPanel::onLibaoClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(PackageDialog::create());
}

void MenuPanel::onBackKeyTouched()
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	KeyPadWatcher::exitGame();
}
