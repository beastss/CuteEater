#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "BasePanel.h"
#include "PackageDialog.h"
#include "StageMgr.h"
#include "Ghost.h"
class UiLayer;
class Snake;
class Food;
class FoodMgr;

class GamePanel : public BasePanel
{
public:
	CREATE_FUNC(GamePanel);
	void setFocus(cocos2d::CCPoint pos);
	std::vector<Snake *> getSnakes(){ return m_snakes; }
	std::vector<Ghost *> getGhosts(){ return m_ghosts; }
	void removeSnake(Snake *snake);
	void addFood(cocos2d::ccColor3B color, cocos2d::CCPoint pos);
	void addFood(std::string path, cocos2d::CCPoint pos);
	void addSnake(Snake *snake);
	void addGhost(Ghost *ghost);
	cocos2d::CCNode *getSnakeBatch(){ return m_snakeBatchNode; }
	cocos2d::CCNode *getSnakeField(){ return m_snakeField; }
	void initGhost();

	~GamePanel();
private:
	GamePanel();
    virtual bool init();  
	void initGameBk();
	void initSnakes();
	void update(float dt);
	void updateTarget();
	void jifei(float dt);
	virtual void onBackKeyTouched();
	void pausePanel(){ ispause = true; }
	void npcRebornCheck();
private:
	float timeLeft;
	UiLayer *m_uiLayer;
	cocos2d::CCNode *m_snakeField,*m_ghostField;
	cocos2d::CCNode *m_snakeBatchNode;
	FoodMgr *m_foodMgr;
	std::vector<Snake *> m_snakes;
	std::vector<Ghost *> m_ghosts;
	PlayerSnake * m_playsnake;
	bool ispause;

private:
	//—”ïrèÕªÓ”√
	void delayReborn(float dt);
	int m_reborni;
	int m_rebornid;
};

#endif 
