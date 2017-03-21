#include "GameOverDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "CommonUtil.h"
#include "PlayerData.h"
#include "SoundMgr.h"
USING_NS_CC;
using namespace std;

bool GameOverDialog::init()
{
	m_layout = UiLayout::create("layout/gameover_dialog.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);
	
	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(10));
	backBtn->setTarget(this, menu_selector(GameOverDialog::onBackBtnClicked));

	//CCMenuItem *replayBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	//replayBtn->setTarget(this, menu_selector(GameOverDialog::onReplayBtnClicked));

	CCLabelTTF *label = NULL;
	label = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(11));
	label->setColor(ccc3(72, 49, 32));
	label->setFontSize(34);

	/*CCLabelTTF *length = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(8));
	length->setString(CommonUtil::intToStr(PlayerData::theData()->getData().length));
	length->setColor(ccc3(0, 0, 0));
	CCLabelTTF *score = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(10));
	score->setString(CommonUtil::intToStr(PlayerData::theData()->getData().score));
	score->setColor(ccc3(0, 0, 0));*/
	
	return true;
}

void GameOverDialog::onReplayBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdGamePanel);
	removeFromParent();
}

void GameOverDialog::onBackBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	//MainScene::theScene()->showDialog(GameOverDialog::create());
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
	removeFromParent();
}