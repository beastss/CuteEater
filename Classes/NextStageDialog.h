#ifndef __NEXT_STAGE_DIALOG_H__
#define __NEXT_STAGE_DIALOG_H__
#include "cocos2d.h"
#include "ScaleDialog.h"

class UiLayout;
class NextStageDialog
	: public ScaleDialog
{
public:
	CREATE_FUNC(NextStageDialog);
private:
	//virtual void onEnter();
	//virtual void onExit();
	virtual bool init();
	void onReplayBtnClicked(cocos2d::CCObject* pSender);
	void onBackBtnClicked(cocos2d::CCObject* pSender);

private:
	UiLayout *m_layout;
};
#endif