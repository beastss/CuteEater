#ifndef __PLAYER_SNAKE_H__
#define __PLAYER_SNAKE_H__ 
#include "Snake.h"
#include "SnakeController.h"


class ActionRunner;
class PlayerSnake 
	: public Snake
	, public IControlSnake
{
public:
	static PlayerSnake *create(GamePanel *gamePanel, const SnakeData &data = SnakeData());
	static PlayerSnake * onCreat(GamePanel *gamePanel, const SnakeData &data = SnakeData());
	cocos2d::CCPoint getPPoingt();
	virtual void reborn();
	~PlayerSnake();
private:
	PlayerSnake(GamePanel *gamePanel, const SnakeData &data);
	virtual void onEnter();
	virtual void onExit();
	virtual bool init();
private:
	virtual void onDead();
	virtual void onMove(cocos2d::CCPoint pos);
	virtual void onUpdate(float dt);
	virtual void onEatFood();
private:
	virtual void onAngleChanged(int angle);
	virtual void onSpeedUp(bool enable);
	virtual void onGrow();
	virtual void onGodLike();

protected:
	float m_speedTime;
	float m_onspeedTime;//����ҩˮ����ʱ��
	cocos2d::CCParticleSystem* particleSystem;
private:
	ActionRunner *m_runner;
	float m_godLikeTime; //����ʱ
	float m_speedUpTime; //�ۻ���ʱ
	bool is_autospeed;

};
#endif