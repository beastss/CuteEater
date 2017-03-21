#include "ComplaintDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "CommonUtil.h"
#include "PlayerData.h"
#include "SoundMgr.h"
USING_NS_CC;
using namespace std;

bool ComplaintDialog::init()
{
	m_layout = UiLayout::create("layout/complaint_dialog.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);
	for (int i = 0; i < 4; i++)
	{
		CCLabelTTF * str = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(11+i));
		str->setColor(ccc3(153, 96, 22));
	}
	

	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	backBtn->setTarget(this, menu_selector(ComplaintDialog::onBackBtnClicked));




	return true;
}



void ComplaintDialog::onBackBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	//MainScene::theScene()->showDialog(GameOverDialog::create());
	//MainScene::theScene()->showPanel(kPanelIdMenuPanel);
	removeFromParent();
}