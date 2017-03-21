#ifndef __CCCIRCLE_BY_H__
#define  __CCCIRCLE_BY_H__

#include <iostream>
#include "cocos2d.h"
#include "Snake.h"
USING_NS_CC;

class CCCircleBy :public CCActionInterval
{
public:
	static CCCircleBy * creat(float t, CCPoint circleCenter, float radius, Snake * snake);
	bool init(float t, CCPoint circleCenter, float radius, Snake * snake);
	virtual void update(float time);
protected:
	CCPoint m_circlecenter;
	float m_radius;
	float m_radian;
	float m_movetimes;
	Snake * m_snake;
};
#endif // !__CCCIRCLE_BY_H__
