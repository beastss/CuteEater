#ifndef __TIME_CONSUME_H__
#define __TIME_CONSUME_H__
#include "cocos2d.h"
#include <unordered_map>
class TimeConSume
{
public:
	void start();
	void record(std::string name);
	void printLog();
	TimeConSume() : m_startTime(0){}
private:
	std::unordered_map<std::string, int>m_time;
	int m_startTime;
};
#endif