#ifndef __REBORN_PACKAGE_H__
#define __REBORN_PACKAGE_H__
#include "cocos2d.h"
#include "ScaleDialog.h"

class UiLayout;
class GamePanel;
class RebornDialog
	: public ScaleDialog
{
public:
	static RebornDialog *create(GamePanel *gamePanel);
private:
	RebornDialog(GamePanel *gamePanel) :m_gamePanel(gamePanel){}
	virtual bool init();
	void onBuyBtnClicked(cocos2d::CCObject* pSender);
	void onCloseBtnClicked(cocos2d::CCObject* pSender);
	virtual void onTouch(cocos2d::CCPoint pt);
private:
	UiLayout *m_layout;
	GamePanel *m_gamePanel;
};
#endif