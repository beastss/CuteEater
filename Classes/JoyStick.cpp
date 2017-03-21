#include "JoyStick.h"
#include <cmath>
USING_NS_CC;
using namespace std;

void JoyStick::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void JoyStick::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool JoyStick::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_bg = CCSprite::create("joy_stick/bg.png");
	m_bg->setPosition(ccp(winSize.width * 0.1f, winSize.height * 0.2f));
	addChild(m_bg);

	m_slider = CCSprite::create("joy_stick/slider.png");
	addChild(m_slider);

	resetSlider();
	return true;
}

void JoyStick::resetSlider()
{
	m_slider->setPosition(m_bg->getPosition());
}

bool JoyStick::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	auto pos = convertToNodeSpace(pTouch->getLocation());
	if(m_slider->boundingBox().containsPoint(pos))
	{
		return true;
	}
	return false;
}

void JoyStick::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	auto curPos = convertToNodeSpace(pTouch->getLocation());
	auto prePos = convertToNodeSpace(pTouch->getPreviousLocation());

	auto centerPos = m_bg->getPosition();
	auto radius = m_bg->getContentSize().height * 0.5f;
	auto targetPos = ccpAdd(m_slider->getPosition(), ccpSub(curPos, prePos));
	
	float distance = ccpDistance(targetPos, centerPos);
	float dx = targetPos.x - centerPos.x;
	float dy = targetPos.y - centerPos.y;
	if (distance > radius)
	{
		//利用等比三角形算出圆边上的坐标
		targetPos.x = centerPos.x + dx * radius / distance;
		targetPos.y = centerPos.y + dy * radius / distance;
	}
	m_slider->setPosition(targetPos);
	if (m_handle)
	{
		//计算角度
		CCPoint delta = ccp(dx, dy).normalize();
		int angle = atan(dy / dx) * 180 / M_PI;
		if (dx < 0)
		{
			angle += 180;
		}
		angle = (angle + 360) % 360;
		m_handle(angle);
	}
}

void JoyStick::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	resetSlider();
}
