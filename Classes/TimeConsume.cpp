#include "TimeConsume.h"
#include <algorithm>
USING_NS_CC;
using namespace std;

void TimeConSume::start()
{
	m_time.clear();

	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	m_startTime = now.tv_usec;
}

void TimeConSume::record(std::string name)
{
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	m_time[name] = now.tv_usec - m_startTime;
}

void TimeConSume::printLog()
{
	vector<pair<string, int>>temp;
	for (auto iter = m_time.begin(); iter != m_time.end(); ++iter)
	{
		temp.push_back(make_pair(iter->first, iter->second));
	}
	sort(temp.begin(), temp.end(), [=](pair<string, int> v1, pair<string, int> v2)
	{
		return v1.second < v2.second;
	});
	CCLOG("time consume record start --------------");
	for (size_t i = 0; i < temp.size(); ++i)
	{
		CCLOG("%s: %d", temp[i].first.c_str(), temp[i].second);
	}
	CCLOG("time consume record end --------------");
}