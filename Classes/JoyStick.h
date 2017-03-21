#ifndef __JOY_SKICK_H__
#define __JOY_SKICK_H__
#include "cocos2d.h"
#include <functional>

class JoyStick
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
{
public:
	CREATE_FUNC(JoyStick);
	void setHandle(std::function<void(int)> handle){ m_handle = handle; }
private:
	virtual void onEnter();
	virtual void onExit();
	virtual bool init();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	void resetSlider();
private:
	cocos2d::CCNode *m_slider;
	cocos2d::CCNode *m_bg;
	std::function<void(int)> m_handle;
};

#endif