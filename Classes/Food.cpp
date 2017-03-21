#include "Food.h"
#include "CommonUtil.h"
#include "CommonMacro.h"
#include "CCFunctionAction.h"
USING_NS_CC;
using namespace std;
using namespace CommonUtil;

Food::Food(cocos2d::ccColor3B color)
: m_color(color)
{
	m_view = CCSprite::createWithSpriteFrameName("snake_food.png");
	m_enery = 1;
	m_view->setColor(m_color);
	m_view->setScale(0.5f);
}

Food::Food(std::string path)
{
	m_view = CCSprite::create(path.c_str());
	m_enery = 2;
	m_view->setScale(0.99f);
	CCSprite *effec2 = CCSprite::create("game_scene/star.png");
	effec2->setScale(0);
	effec2->setPosition(ccp(m_view->getPositionX()+9.5 , m_view->getPositionY()+19.7 ));
	effec2->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCScaleTo::create(1.2, 0),
		CCScaleTo::create(0.75f, 0.61),
		CCScaleTo::create(0.35f, 0),
		CCScaleTo::create(1.1f, 0),
		CCDelayTime::create(getRandomValue(0, 4000) / 1000.0),
		NULL)
		));
	m_view->addChild(effec2, 11);

	CCSprite *effec3 = CCSprite::create("game_scene/star.png");
	effec3->setScale(0);
	effec3->setPosition(ccp(m_view->getPositionX() + 20, m_view->getPositionY() + 5));
	effec3->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCScaleTo::create(3.5, 0),
		CCScaleTo::create(0.85f, 0.72),
		CCScaleTo::create(0.85f, 0),
		CCScaleTo::create(0.7f, 0),
		CCDelayTime::create(getRandomValue(0, 4000) / 1000.0),
		NULL)
		));
	m_view->addChild(effec3, 11);
}

Food::~Food()
{

}

void Food::onEaten(CCPoint pt)
{
	//auto move = CCMoveTo::create(0.3f, pt);
	/*auto func = CCFunctionAction::create([=]()
	{
		m_view->removeFromParent();
		delete this;
	});*/
	m_view->removeFromParent();
	delete this;
	//auto seq = CCSequence::create(move, func, NULL);
	//m_view->runAction(seq);
}