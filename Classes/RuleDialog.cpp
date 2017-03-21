#include "RuleDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "CommonUtil.h"
#include "PlayerData.h"
#include "SoundMgr.h"
USING_NS_CC;
using namespace std;

bool RuleDialog::init()
{
	m_layout = UiLayout::create("layout/rule_dialog.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);

	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	backBtn->setTarget(this, menu_selector(RuleDialog::onBackBtnClicked));




	return true;
}



void RuleDialog::onBackBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	//MainScene::theScene()->showDialog(GameOverDialog::create());
	//MainScene::theScene()->showPanel(kPanelIdMenuPanel);
	removeFromParent();
}