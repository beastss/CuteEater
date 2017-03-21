#include "BasePanel.h"
#ifndef __SETTING_DIALOG_H__
#define __SETTING_DIALOG_H__
#include "cocos2d.h"
#include "ScaleDialog.h"

class UiLayout;
class SettingDialog
	: public ScaleDialog
{
public:
	CREATE_FUNC(SettingDialog);
private:
	SettingDialog(){}
	virtual bool init();
	void initPanel();
	void onCloseBtnClicked(cocos2d::CCObject* pSender);
	virtual void onTouch(cocos2d::CCPoint pt);
	void refreshUi();
private:
	UiLayout *m_layout;
};
#endif