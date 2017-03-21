#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cocos2d.h"
#include <deque>
#include "CommonMacro.h"
#include "SnakeSkinRes.h"
#include "CommonUtil.h"

class UiLayout;
class GamePanel;

struct SnakeData
{
	int score;
	int skinId;
	int length;
	std::string name;
	SnakeData(int _score, int _skinId, int _length, std::string _name)
		:score(_score), skinId(_skinId), length(_length), name(_name)
	{
	}
	SnakeData()
	{
		score = 0;
		skinId = CommonUtil::getRandomValue(kFirstSkin, kLastSkin);
		length = INIT_SNAKE_LENGTH * (CCRANDOM_0_1() * 2 + 1);
	}
};

class Snake: public cocos2d::CCNode
{
public:
	//CREATE_FUNC(Snake);
	virtual ~Snake(){}
	bool willCrash(cocos2d::CCPoint pt, int destAngle);
	bool isCrash(cocos2d::CCPoint pt);
	void update(float dt);
	bool canEatFood(cocos2d::CCPoint pt);
	void eatFood(int enery);
	CCNode *getHead(){ return m_body[0]; }
	virtual void addHead();
	static Snake * onCreat(GamePanel *gamePanel, const SnakeData &data = SnakeData());
	bool isDead(){ return isdead; }
	virtual void reborn();
protected:
	Snake(GamePanel *gamePanel, const SnakeData &data = SnakeData());
	void initBodyPos(cocos2d::CCPoint pos);
	
	void addBody();
	void addTail();
	void removeBody();
	void setGodLikeState(bool open);
protected:
	virtual void onExit();
	virtual void onMove(cocos2d::CCPoint pos){}
	virtual void onDead(){}
	virtual void onUpdate(float dt){}
	virtual void onEatFood(){}
	bool initSnake();
private:
	cocos2d::CCNode *getTail(){ return m_body.back(); }
	bool isdead = false;
	bool checkCrash();
	void crash();
protected:
	cocos2d::CCSprite * act;
	int m_destAngle;
	float m_speed;
	bool m_isSpeedUp;
	std::vector<cocos2d::CCNode *>m_body;
	std::deque<std::pair<cocos2d::CCPoint, float>>m_path;
	GamePanel *m_gamePanel;
	bool m_isGodlike;
	SnakeData m_data;
	cocos2d::CCLabelTTF *m_nameLabel;
	float m_scale;
	float m_speedTime;
private:
	int m_angle;
	int m_growEnergy;

};
#endif