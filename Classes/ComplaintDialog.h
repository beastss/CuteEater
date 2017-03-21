#ifndef __COMPLAINT_DIALOG_H__
#define __COMPLAINT_DIALOG_H__
#include "cocos2d.h"
#include "ScaleDialog.h"

class UiLayout;
class ComplaintDialog
	: public ScaleDialog
{
public:
	CREATE_FUNC(ComplaintDialog);
private:
	virtual bool init();

	void onBackBtnClicked(cocos2d::CCObject* pSender);

private:
	UiLayout *m_layout;
};
#endif