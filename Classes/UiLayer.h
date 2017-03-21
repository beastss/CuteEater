#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "cocos2d.h"
#include "SnakeController.h"
#include "FoodMgr.h"

class UiLayout;
class UiLayer
	: public cocos2d::CCNode
	, public IControlSnake
	, public cocos2d::CCTouchDelegate
{
public:
	CREATE_FUNC(UiLayer);
	void updatetime(int leftSecs,int cur);
	void trsfoodmgr(FoodMgr * food){ foodmgr = food; };
private:
    virtual bool init();  
	void initLeftUi();
	void initRightUi();
	void onGodLikeBtnClicked(cocos2d::CCObject* pSender);
	void onGrowBtnClicked(cocos2d::CCObject* pSender);
	void onBackBtnClicked(cocos2d::CCObject* pSender);
	void onJoyStickChanged(int angle);
	void initTopUi();

	virtual void onEnter();
	virtual void onExit();

private:
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onSnakeDataChanged();
private:
	UiLayout *m_leftLayout;
	UiLayout *m_rightLayout;
	UiLayout *m_topLayout;
	FoodMgr* foodmgr;

};

#endif 
