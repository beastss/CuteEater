#ifndef __SNAKE_COLOR_H__
#define __SNAKE_COLOR_H__
#include "cocos2d.h"
#include "CommonUtil.h"
class SnakeColor
{
public:
	static std::vector<cocos2d::ccColor3B> m_colors;
	static void init();
	static cocos2d::ccColor3B getRandomColor();

};

#define RANDOM_COLOR SnakeColor::getRandomColor()
#endif