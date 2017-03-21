#ifndef __MATCH_SYS_LAYER_H__
#define __MATCH_SYS_LAYER_H__

#include "cocos2d.h"
#include "UiLayout.h"
USING_NS_CC;

class MatchSysLayer :public CCLayer
{
public:
	CREATE_FUNC(MatchSysLayer);
	MatchSysLayer();
	~MatchSysLayer();
	void update(float dt);
private:
	void switchOn(int id);
	void initPlayer();
	void starGame(float dt);
private:

	std::vector<std::string> m_npcname;
	std::vector<int> m_characterid;
	std::vector<float> npcmatchtime;
	UiLayout * m_matchlayer;
	int icount;



};




#endif