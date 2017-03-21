#include "SettingDialog.h"
#include "UiLayout.h"
#include "CommonMacro.h"
#include "SoundMgr.h"
USING_NS_CC;
using namespace std;
bool SettingDialog::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	initPanel();
	return true;
}

void SettingDialog::initPanel()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_layout = UiLayout::create("layout/setting.xml");
	m_layout->setMenuTouchPriority(kTouchPriorityDialog - 1);
	addChild(m_layout);
	setContentSize(m_layout->getContentSize());
	addMaskLayer();

	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	closeBtn->setTarget(this, menu_selector(SettingDialog::onCloseBtnClicked));

	refreshUi();
}

void SettingDialog::onCloseBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	removeFromParent();
}

void SettingDialog::onTouch(cocos2d::CCPoint pt)
{
	auto pos = m_layout->convertToNodeSpace(pt);
	if (m_layout->getChildById(2)->boundingBox().containsPoint(pos))
	{
		bool isOn = SoundMgr::theMgr()->isBackgroundMusicOn();
		SoundMgr::theMgr()->setBackgroundMusic(!isOn);
		SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	}
	else if (m_layout->getChildById(3)->boundingBox().containsPoint(pos))
	{
		bool isOn = SoundMgr::theMgr()->isEffectMusicOn();
		SoundMgr::theMgr()->setEffectMusic(!isOn);
		SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	}
	refreshUi();
}

void SettingDialog::refreshUi()
{
	bool isOn = SoundMgr::theMgr()->isBackgroundMusicOn();
	m_layout->getChildById(4)->setVisible(isOn);
	m_layout->getChildById(2)->setVisible(isOn);
	m_layout->getChildById(7)->setVisible(!isOn);

	isOn = SoundMgr::theMgr()->isEffectMusicOn();
	m_layout->getChildById(5)->setVisible(isOn);
	m_layout->getChildById(3)->setVisible(isOn);
	m_layout->getChildById(8)->setVisible(!isOn);
}