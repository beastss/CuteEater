#ifndef __PACKAGE_DIALOG_H__
#define __PACKAGE_DIALOG_H__
#include "cocos2d.h"
#include "ScaleDialog.h"

class UiLayout;
class PackageDialog
	: public ScaleDialog
{
public:
	CREATE_FUNC(PackageDialog);
private:
	//virtual void onEnter();
	//virtual void onExit();
	virtual bool init();
	void onBuyBtnClicked(cocos2d::CCObject* pSender);
	void onCloseBtnClicked(cocos2d::CCObject* pSender);
	virtual void onTouch(cocos2d::CCPoint pt);

private:
	UiLayout *m_layout;
};
#endif