#include "MainScene.h"
#include "ScaleDialog.h"
#include "BasePanel.h"
#include "GamePanel.h"
#include "MenuPanel.h"
#include "HelpPanel.h"
using namespace std;
USING_NS_CC;

MainScene *MainScene::m_scene = NULL;

MainScene *MainScene::theScene()
{
	if (!m_scene)
	{
		m_scene = new MainScene();
		m_scene->init();
		m_scene->autorelease();
	}
	return m_scene;
}

MainScene::MainScene()
: m_curPanel(NULL)
{

}

MainScene::~MainScene()
{
	m_scene = NULL;
}

bool MainScene::init()
{
	if (!CCScene::init())return false;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//监听手机键
	m_keyPadWatcher = KeyPadWatcher::create();
	addChild(m_keyPadWatcher);
	//面板层
	m_panelLayer = CCNode::create();
	addChild(m_panelLayer);
	//对话框层
	m_dialogLayer = CCNode::create();
	addChild(m_dialogLayer);

	showPanel(kPanelIdMenuPanel);
    return true;
}

void MainScene::showPanel(int panelId)
{
	BasePanel *panel = NULL;
	switch (panelId)
	{
	case kPanelIdMenuPanel:
		panel = MenuPanel::create();
		break;
	case kPanelIdGamePanel:
		panel = GamePanel::create();
		break;
	case kPanelIdHelpPanel:
		panel = HelpPanel::create();
	default:
		break;
	}

	if (panel)
	{
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		m_panelLayer->removeAllChildren();
		panel->setAnchorPoint(ccp(0.5f, 0.5f));
		panel->setPosition(ccpMult(winSize, 0.5f));
		m_panelLayer->addChild(panel);
		m_curPanel = panel;
	}

}

void MainScene::showDialog(ScaleDialog *dialog)
{
	m_dialogLayer->removeAllChildren();
	m_dialogLayer->addChild(dialog);
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	dialog->setAnchorPoint(ccp(0.5f, 0.5f));
	dialog->setPosition(ccpMult(winSize, 0.5f));
}

void MainScene::onKeyBackClicked()
{
	m_curPanel->onBackKeyTouched();
}

void MainScene::exitGame()
{
	m_keyPadWatcher->exitGame();
}