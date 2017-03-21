#ifndef __STAGE_MGR_H__
#define __STAGE_MGR_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#define   Stage StageMgr::getIter()


class StageMgr
{
public:
    static StageMgr * getIter();
	StageMgr() ;
	 ~StageMgr(){};
	 void reset();
public:
public:
	int stagecount[8] ;
	float time[8];
	int foods[8];
	int currentstage = 1;
	int ghost[8];
	std::string mapnames[8];


};
#endif