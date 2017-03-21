#ifndef __RULE_DIALOG_H__
#define __RULE_DIALOG_H__
#include "cocos2d.h"
#include "ScaleDialog.h"

class UiLayout;
class RuleDialog
	: public ScaleDialog
{
public:
	CREATE_FUNC(RuleDialog);
private:
	virtual bool init();

	void onBackBtnClicked(cocos2d::CCObject* pSender);

private:
	UiLayout *m_layout;
};
#endif