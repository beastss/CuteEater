#include "UiLayer.h"
#include "CommonUtil.h"
#include "JoyStick.h"
#include "SnakeController.h"
#include "CommonMacro.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "RankingPanel.h"
#include "PropsMgr.h"
#include "MainScene.h"
#include "PackageDialog.h"
#include "PlayerData.h"
#include "SoundMgr.h"
#include "StageMgr.h"
#include "FoodMgr.h"
using namespace std;
USING_NS_CC;

void UiLayer::onEnter()
{
	CCNode::onEnter();
	SnakeController::controller()->addView(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityPanel, true);
}

void UiLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	removeAllChildren();
	CCNode::onExit();

	SnakeController::controller()->removeView(this);
}

bool UiLayer::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	initLeftUi();
	initRightUi();
	initTopUi();
	//ÐéÄâÒ¡¸Ë
	auto joyStick = JoyStick::create();
	joyStick->setHandle(bind(&UiLayer::onJoyStickChanged, this, placeholders::_1));
	addChild(joyStick);

    return true;
}

void UiLayer::initLeftUi()
{
	m_leftLayout = UiLayout::create("layout/game_panel_ui_left.xml");
	m_leftLayout->setMenuTouchPriority(kTouchPriorityPanel);
	addChild(m_leftLayout);

	for (int i = 0; i < 2; ++i)
	{
		CCLabelTTF *label = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(5 + i));
		label->setColor(ccc3(249, 255, 251));
	}
	onSnakeDataChanged();
}

void UiLayer::initRightUi()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_rightLayout = UiLayout::create("layout/game_panel_ui_right.xml");
	m_rightLayout->setMenuTouchPriority(kTouchPriorityPanel);
	m_rightLayout->setAnchorPoint(ccp(1, 0));
	m_rightLayout->setPosition(ccp(winSize.width, 0));
	addChild(m_rightLayout);

	auto rankingPanel = RankingPanel::create();
	rankingPanel->setAnchorPoint(ccp(1, 1));
	rankingPanel->setPosition(ccpSub(winSize, ccp(5, 5)));
	rankingPanel->setScale(0.7f);
	addChild(rankingPanel);

	CCMenuItem *growBtn = dynamic_cast<CCMenuItem *>(m_rightLayout->getChildById(2));
	growBtn->setTarget(this, menu_selector(UiLayer::onGrowBtnClicked));
	CCLabelAtlas *growNum = dynamic_cast<CCLabelAtlas *>(m_rightLayout->getChildById(8));
	growNum->setString(CommonUtil::intToStr(PropsMgr::theMgr()->getNum(kPropsTypeGrow)));
	CCMenuItem *godLikeBtn = dynamic_cast<CCMenuItem *>(m_rightLayout->getChildById(3));
	CCLabelAtlas *godLikeNum = dynamic_cast<CCLabelAtlas *>(m_rightLayout->getChildById(9));
	godLikeNum->setString(CommonUtil::intToStr(PropsMgr::theMgr()->getNum(kPropsTypeGodlike)));;
	godLikeBtn->setTarget(this, menu_selector(UiLayer::onGodLikeBtnClicked));
	CCSprite *buttonbg = dynamic_cast<CCSprite *>(m_rightLayout->getChildById(15));
	buttonbg->setFlipX(true);
	CCSprite *buttonbg2 = dynamic_cast<CCSprite *>(m_rightLayout->getChildById(16));
	buttonbg2->setFlipX(true);



	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>(m_rightLayout->getChildById(10));
	backBtn->setTarget(this, menu_selector(UiLayer::onBackBtnClicked));
	backBtn->setVisible(false);
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	backBtn->setVisible(false);
#endif
}

void UiLayer::initTopUi()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_topLayout = UiLayout::create("layout/game_panel_ui_top.xml");
	m_topLayout->setMenuTouchPriority(kTouchPriorityPanel);
	m_topLayout->setAnchorPoint(ccp(0.5, 0));
	m_topLayout->setPosition(ccp(winSize.width*0.5, 0));
	addChild(m_topLayout);

}

void UiLayer::onGodLikeBtnClicked(CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	int num = PropsMgr::theMgr()->getNum(kPropsTypeGodlike);
	if (num <= 0)
	{
		MainScene::theScene()->showDialog(PackageDialog::create());
		return;
	}
	PropsMgr::theMgr()->saveNum(kPropsTypeGodlike, num - 1);
	CCLabelAtlas *growNum = dynamic_cast<CCLabelAtlas *>(m_rightLayout->getChildById(9));
	growNum->setString(CommonUtil::intToStr(num - 1));

	SnakeController::controller()->godLike();
}

void UiLayer::onGrowBtnClicked(CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	int num = PropsMgr::theMgr()->getNum(kPropsTypeGrow);
	if (num <= 0)
	{
		MainScene::theScene()->showDialog(PackageDialog::create());
		return;
	}
	PropsMgr::theMgr()->saveNum(kPropsTypeGrow, num - 1);
	CCLabelAtlas *growNum = dynamic_cast<CCLabelAtlas *>(m_rightLayout->getChildById(8));
	growNum->setString(CommonUtil::intToStr(num - 1));

	SnakeController::controller()->growBody();
}

void UiLayer::onBackBtnClicked(CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
}

void UiLayer::onJoyStickChanged(int angle)
{
	//CCLOG("x = %f, y = %f", angel.x, angel.y);
	SnakeController::controller()->changeAngle(angle);
}

void UiLayer::onSnakeDataChanged()
{
	

}

bool UiLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	auto pos = m_rightLayout->convertToNodeSpace(pTouch->getLocation());
	auto speedUpImg = m_rightLayout->getChildById(1);
	if (speedUpImg->boundingBox().containsPoint(pos))
	{
		SoundMgr::theMgr()->playEffect(kEffectMusicButton);
		speedUpImg->setScale(1.3f);
		SnakeController::controller()->speedUp(true);
		return true;
	}
	return false;
}

void UiLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_rightLayout->getChildById(1)->setScale(1);
	SnakeController::controller()->speedUp(false);
}

void UiLayer::updatetime(int leftSecs,int cur)
{
	CCLabelTTF *leftTime = dynamic_cast<CCLabelTTF *>(m_topLayout->getChildById(12));
	CCSprite *currentsta = dynamic_cast<CCSprite *>(m_leftLayout->getChildById(12));

	char str[100] = { 0 };
	sprintf(str, "game_scene/stadesc%d.png",cur);
	currentsta->initWithFile(str);
	if (leftSecs > 0)
	{
	int mins = leftSecs / 60;
	int secs = leftSecs % 60;
	leftTime->setVisible(true);
	char str[100] = { 0 };
	sprintf(str, "%02d : %02d", mins, secs);
	leftTime->setString(str);
	}
	else
	{
	leftTime->setVisible(false);
	}
	CCLabelTTF *lengthLabel = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(5));
	lengthLabel->setString(CommonUtil::intToStr(foodmgr->leftFood()));
	CCLabelTTF *scoreLabel = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(6));
	scoreLabel->setString(CommonUtil::intToStr(Stage->ghost[Stage->currentstage]));

	
}