#ifndef __ENEMY_SNAKE_H__
#define __ENEMY_SNAKE_H__ 
#include "Snake.h"
#include "SnakeController.h"

class GamePanel;

class EnemySnake 
	: public Snake
	, public IControlSnake
{
public:
	static EnemySnake *create(GamePanel *gamePanel, const SnakeData &data );
	static EnemySnake *onCreat(GamePanel *gamePanel, const SnakeData &data);
	virtual void addHead();
	virtual void reborn();
private:
	EnemySnake(GamePanel *gamePanel, const SnakeData &data);
	virtual bool init();
	virtual void onExit();
	virtual void onEnter();
	virtual void onMove(cocos2d::CCPoint pos);
	virtual void onDead();
	void detectCollision();
	virtual void onUpdate(float dt);

private:
	virtual void onSpeedUp(bool enable);
	virtual void onNpcGodLike();
    virtual void onNpcGrow();

protected:
	float m_godLikeTime; //����ʱ
	float m_speedUpTime; //�ۻ���ʱ
	bool is_autospeed;
	float m_speedTime;
	float m_onspeedTime;//����ҩˮ����ʱ��
	cocos2d::CCParticleSystem* particleSystem;
};
#endif