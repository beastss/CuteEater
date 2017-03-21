#include "SnakeColor.h"
USING_NS_CC;
using namespace std;

std::vector<cocos2d::ccColor3B> SnakeColor::m_colors;

void SnakeColor::init()
{
	m_colors.clear();
	m_colors.push_back(cocos2d::ccc3(0, 0, 0));
	m_colors.push_back(cocos2d::ccc3(205, 82, 93));
	m_colors.push_back(cocos2d::ccc3(70, 130, 180));
	m_colors.push_back(cocos2d::ccc3(220, 20, 60));
	m_colors.push_back(cocos2d::ccc3(138, 100, 138));
	m_colors.push_back(cocos2d::ccc3(106, 90, 205));
	m_colors.push_back(cocos2d::ccc3(0, 155, 155));
	m_colors.push_back(cocos2d::ccc3(127, 205, 170));
	m_colors.push_back(cocos2d::ccc3(0, 155, 0));
	m_colors.push_back(cocos2d::ccc3(205, 205, 0));
	m_colors.push_back(cocos2d::ccc3(128, 128, 0));
	m_colors.push_back(cocos2d::ccc3(155, 148, 220));
	m_colors.push_back(cocos2d::ccc3(255, 165, 0));
	m_colors.push_back(cocos2d::ccc3(255, 127, 80));
	m_colors.push_back(cocos2d::ccc3(135, 206, 235));
	m_colors.push_back(cocos2d::ccc3(155, 115, 0));
	m_colors.push_back(cocos2d::ccc3(128, 0, 0));
}

cocos2d::ccColor3B SnakeColor::getRandomColor()
{
	int index = CommonUtil::getRandomValue(0, m_colors.size() - 1);
	return m_colors[index];
}
