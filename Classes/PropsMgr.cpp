#include "PropsMgr.h"
#include <algorithm>
USING_NS_CC;
using namespace std;

PropsMgr *PropsMgr::theMgr()
{
	static PropsMgr mgr;
	return &mgr;
}

void PropsMgr::init()
{
	m_props[kPropsTypeGrow] = CCUserDefault::sharedUserDefault()->getIntegerForKey("props_grow", 10);
	m_props[kPropsTypeGodlike] = CCUserDefault::sharedUserDefault()->getIntegerForKey("props_godlike", 10);
}

void PropsMgr::saveNum(int propsType, int num)
{
	num = max(0, num);
	m_props[propsType] = num;
	switch (propsType)
	{
	case kPropsTypeGrow:
		CCUserDefault::sharedUserDefault()->setIntegerForKey("props_grow", m_props[kPropsTypeGrow]);
		break;
	case kPropsTypeGodlike:
		CCUserDefault::sharedUserDefault()->setIntegerForKey("props_godlike", m_props[kPropsTypeGodlike]);
		break;
	default:
		assert(false && "no this props");
		break;
	}
}

int PropsMgr::getNum(int propsType)
{
	return m_props[propsType];
}