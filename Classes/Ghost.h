#ifndef __GHOST_H__
#define __GHOST_H__ 
#include "Snake.h"
#include "PlayerSnake.h"

class GamePanel;

class Ghost :public cocos2d::CCNode
{
public:
	static Ghost *create(GamePanel *gamePanel, PlayerSnake * playerSnake);
	static Ghost *onCreat(GamePanel *gamePanel, PlayerSnake *playerSnake);
	virtual void addHead();
	void update(float dt);

	CCNode *getHead(){ return m_body[0]; }
	void initBodyPos(cocos2d::CCPoint pos);
	void targetSnake();
	bool willCrash(cocos2d::CCPoint pt, int destAngle);
protected:
	bool initGhost();
	GamePanel * m_gamePanel;
	PlayerSnake * m_playerSnake;
	std::vector<cocos2d::CCNode *>m_body;
	float m_scal;
	void aiMove(float dt);
	void randmove(float dt);


private:
	float leftdt;//计时器 计算执行多久追踪玩家
	float lengt;
	cocos2d::CCPoint target;
	Snake * tarsnake=NULL;
	Ghost(GamePanel *gamePanel, PlayerSnake *playerSnake);
	virtual bool init();
	virtual void onExit();

	virtual void onMove(cocos2d::CCPoint pos);
	virtual void onDead();
	void detectCollision();
};
#endif