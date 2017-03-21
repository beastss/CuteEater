#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__
#include "cocos2d.h"
#include "Snake.h"
#include "AndroidIter.h"
class PlayerData
{
public:
	static PlayerData *theData();
	void reset();

	const SnakeData &getData(){ return m_data; }
	void setData(const SnakeData data){ m_data = data; }
	std::string getName();
	void setNpcData(std::vector<std::string> name, std::vector<int> id){ m_npcname = name; m_characterid = id; }
	std::string getNpcName(int i){ return m_npcname[i]; }
	int getNpcId(int i) { return m_characterid[i]; }
	void addRebornId(int id){ m_rebornid.push_back(id); }
	void earseRebornId(int id){ m_rebornid.erase(id + m_rebornid.begin()); }
	std::vector<int> getRebornId(){ return m_rebornid; }
private:
	SnakeData m_data;
	std::vector<std::string> m_npcname;
	std::vector<int> m_characterid;
	std::vector<int> m_rebornid;//¸´»îid
};


#endif