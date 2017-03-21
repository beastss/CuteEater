#include "BasePanel.h"
#include "UiLayout.h"
#include "CommonMacro.h"
#include "MainScene.h"
USING_NS_CC;
using namespace std;

BasePanel::BasePanel()
: m_touchPriority(kTouchPriorityPanel)
, m_panelId(kPanelIdDefault)
, m_usage(0)
{

}

void BasePanel::onEnter()
{
	CCNode::onEnter();
}

bool BasePanel::init()
{
	return true;
}

