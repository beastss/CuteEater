#include "BasePanel.h"
#ifndef __HELP_PANEL_H__
#define __HELP_PANEL_H__
#include "cocos2d.h"
#include "BasePanel.h"

class HelpPanel
	: public BasePanel
	, public cocos2d::CCTouchDelegate
{
public:
	CREATE_FUNC(HelpPanel);
private:
	HelpPanel() :m_curIndex(1){}
	virtual void onEnter();
	virtual void onExit();
	virtual bool init();
	void initPanel();
	void onBackBtnClicked(cocos2d::CCObject* pSender);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onBackKeyTouched();
private:
	int m_curIndex;
	cocos2d::CCSprite *m_helpTips;
};
#endif