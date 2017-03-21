#include "RebornDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "GamePanel.h"
#include "PlayerSnake.h"
#include "GameOverDialog.h"
#include "PlayerData.h"
#include "MyPurchase.h"
#include "SoundMgr.h"
#include "AndroidIter.h"
USING_NS_CC;
using namespace std;

RebornDialog *RebornDialog::create(GamePanel *gamePanel)
{

	RebornDialog *dialog = new RebornDialog(gamePanel);
	dialog->init();
	dialog->autorelease();
	return dialog;
}

bool RebornDialog::init()
{
	bool forBusiness = AndroidIter::getIter()->isForBusiness();

	m_layout = UiLayout::create(forBusiness ? "layout/reborn.xml" : "layout/reborn_white.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	buyBtn->setTarget(this, menu_selector(RebornDialog::onBuyBtnClicked));

	CCLabelTTF *costLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	CCLabelTTF *phoneLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(9));
	int cost = MyPurchase::sharedPurchase()->getBillData(kBillingReborn).cost / 100;
	char str[100] = { 0 };
	sprintf(str, costLabel->getString(), cost);
	costLabel->setString(str);
	//costLabel
	CCLabelTTF *label = NULL;
	label = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(10));
	label->setColor(ccc3(72, 49, 32));
	label->setFontSize(30);
	phoneLabel->setColor(ccc3(0, 0, 0));
	phoneLabel->setVisible(true);
	if (forBusiness)
	{
		costLabel->setOpacity(40);
		
		
		phoneLabel->setOpacity(255);
	}
	else
	{
		costLabel->setColor(ccc3(255, 255, 255));
		//costLabel->setColor(ccc3(0, 0, 0));
	}

	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	closeBtn->setTarget(this, menu_selector(RebornDialog::onCloseBtnClicked));
	return true;
}

void RebornDialog::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MyPurchase::sharedPurchase()->buyItem(kBillingReborn, [=]()
	{
		//复活后回复上次长度
		auto snake = PlayerSnake::create(m_gamePanel, PlayerData::theData()->getData());
		m_gamePanel->addSnake(snake);
		snake->reborn();
		removeFromParent();
	});
}

void RebornDialog::onCloseBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(GameOverDialog::create());
	removeFromParent();
}

void RebornDialog::onTouch(cocos2d::CCPoint pt)
{
	//bool forBusiness = AndroidIter::getIter()->isForBusiness();
	//if (!forBusiness) return;
	return;
	MyPurchase::sharedPurchase()->buyItem(kBillingReborn, [=]()
	{
		//复活后回复上次长度
		auto snake = PlayerSnake::create(m_gamePanel, PlayerData::theData()->getData());
		m_gamePanel->addSnake(snake);
		removeFromParent();
	});
}