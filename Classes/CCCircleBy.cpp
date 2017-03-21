#include "CCCircleBy.h"
CCCircleBy * CCCircleBy::creat(float t, CCPoint circleCenter, float radius,Snake * snake)
{
	CCCircleBy * pCircle = new CCCircleBy();
	pCircle->init(t, circleCenter, radius,  snake);
	pCircle->autorelease();
	return pCircle;
}

bool CCCircleBy::init(float t, CCPoint circleCenter, float radius, Snake * snake)
{
	if (CCActionInterval::initWithDuration(t))
	{
		m_circlecenter = circleCenter;
		m_radius = radius;
		m_radian = 2.0*M_PI / (t / (CCDirector::sharedDirector()->getAnimationInterval()));
		m_movetimes = 1;
		m_snake = snake;
		return true;
	}
	return false;
}

void CCCircleBy::update(float time)
{
	float m_radian = m_radius*m_movetimes;

	float x = m_radius*sin(m_radian);
	float y = m_radius*cos(m_radian);
	m_circlecenter = m_snake->getHead()->getPosition();
	CCPoint newPos = ccp(x + m_circlecenter.x, y + m_circlecenter.y);
	m_pTarget->setPosition(newPos);

	m_movetimes += 4;
}