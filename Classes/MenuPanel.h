#ifndef __MENU_PANEL_H__
#define __MENU_PANEL_H__ 

#include "cocos2d.h"
#include "BasePanel.h"
class UiLayout;
class MenuPanel : public BasePanel
{
public:
	CREATE_FUNC(MenuPanel);
private:
    virtual bool init();  
	void onNewGameBtnClicked(cocos2d::CCObject* pSender);
	void onRuleBtnClicked(cocos2d::CCObject* pSender);
	void onSkinBtnClicked(cocos2d::CCObject* pSender);
	void onSettingBtnClicked(cocos2d::CCObject* pSender);
	void onLibaoClicked(cocos2d::CCObject* pSender);
	void onComplaintBtnClicked(cocos2d::CCObject * pSender);
	virtual void onBackKeyTouched();
private:
	UiLayout *m_layout;
};

#endif 
