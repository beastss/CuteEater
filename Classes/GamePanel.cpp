#include "GamePanel.h"
#include "PlayerSnake.h"
#include "CommonMacro.h"
#include "UiLayer.h"
#include "EnemySnake.h"
#include "FoodMgr.h"
#include "Food.h"
#include <algorithm>
#include "PlayerData.h"
#include "MainScene.h"
#include "SoundMgr.h"
#include "RankingModel.h"
#include "StageMgr.h"
#include "GameOverDialog.h"
#include "NextStageDialog.h"
#include "CommonUtil.h"
#include "SnakeController.h"
#include "Action.h"
using namespace std;
USING_NS_CC;
using namespace CommonUtil;

GamePanel::GamePanel()
:ispause(false)
{
	m_foodMgr = new FoodMgr(this);
}

GamePanel::~GamePanel()
{
	this->unschedule(schedule_selector(GamePanel::delayReborn));
	delete m_foodMgr;
}

bool GamePanel::init()
{
	//RankingModel::theModel()->reset();
	PlayerData::theData()->reset();
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	
	//背景层
	auto bk = CCLayerColor::create(ccc4(120, 0, 0, 200));
	addChild(bk);
	//蛇区域
	m_snakeField = CCNode::create();
	initGameBk();
	m_snakeField->setContentSize(CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT));
	m_snakeField->setAnchorPoint(ccp(0.5f, 0.5f));
	m_snakeField->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_snakeField);
	m_snakeBatchNode = CCNode::create();
	m_snakeField->addChild(m_snakeBatchNode);
	//ghost
	m_ghostField = CCNode::create();
	m_ghostField->setContentSize(CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT));
	m_ghostField->setAnchorPoint(ccp(0.5f, 0.5f));
	m_ghostField->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_ghostField);
	//ui层
	m_uiLayer = UiLayer::create();
	addChild(m_uiLayer);
	initSnakes();
	initGhost();
	setContentSize(winSize);
	scheduleUpdate();
	// 添加食物
	m_foodMgr->genNewFood(Stage->foods[Stage->currentstage - 1]);
	m_uiLayer->trsfoodmgr(m_foodMgr);

    return true;
}

void GamePanel::initGameBk()
{
	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("game_scene/map_01.png");
	/*
	char str [100]={0};
	sprintf(str,"game_scene/map_0%d.png",Stage->currentstage);
	
	*/
	m_snakeField->addChild(batchNode);
	const float WgridSize = 242;
	const float HgridSize = 143;
	int xGrids = GAME_LAYER_WIDTH / WgridSize;
	int yGrids = GAME_LAYER_HEIGHT / HgridSize;
	for (int i = 0; i < yGrids; ++i)
	{
		for (int j = 0; j < xGrids; ++j)
		{
			CCSprite *spr = CCSprite::createWithTexture(batchNode->getTexture());
			spr->setAnchorPoint(ccp(0, 0));
			CCPoint pos;
			pos.x = WgridSize * j;
			pos.y = HgridSize * i;
			spr->setPosition(pos);
			batchNode->addChild(spr);
		}
	}
	//this->scheduleOnce(schedule_selector(GamePanel::jifei),30.0f);
	//CCSprite * spr = CCSprite::create("game_scene/bg.png");
	//auto size = CCSize(GAME_LAYER_WIDTH,GAME_LAYER_HEIGHT);
	//spr->setPosition(ccpMult(size, 0.5));
	//m_snakeField->addChild(spr);
}

void GamePanel::jifei(float dt)
{
	MainScene::theScene()->showDialog(PackageDialog::create());

}

void GamePanel::npcRebornCheck()
{
	int id=-1;
	auto datas = PlayerData::theData()->getRebornId();
	for (size_t i = 0; i < datas.size(); ++i)
	{
		for (int ii = 0; ii < 3; ii++)
		{
			if (datas[i] == PlayerData::theData()->getNpcId(ii+1))
			{
				id = ii+1;
			}
		}
		if (id != -1)
		{
			//复活概率
			vector<float> reb = { 50.0 };
			if (getResultByPercent(reb))
			{
				float timetre = getRandomValue(1000, 4000) / 1000.0;
				m_reborni = i;
				m_rebornid = id;
				scheduleOnce(schedule_selector(GamePanel::delayReborn), timetre);

			}

		}


	}

}

void GamePanel::delayReborn(float dt)
{

	SnakeData data;
	data.length = INIT_SNAKE_LENGTH;
	data.skinId = PlayerData::theData()->getNpcId(m_rebornid);
	data.name = RankingModel::theModel()->getNpcName(m_rebornid - 1);
	auto npc = EnemySnake::create(this, data);
	npc->reborn();
	addSnake(npc);
	PlayerData::theData()->earseRebornId(m_reborni);
}

void GamePanel::update(float dt)
{
	if (!ispause)
	{
		npcRebornCheck();
		for (size_t i = 0; i < m_snakes.size(); ++i)
		{
			m_snakes[i]->update(dt);
		}
		for (size_t i = 0; i < m_ghosts.size(); i++)
		{
			m_ghosts[i]->update(dt);
		}
		m_foodMgr->update(dt);
		//CCLOG("left time: %d", timeLeft -= dt)
		m_uiLayer->updatetime(Stage->time[Stage->currentstage - 1] -= dt, Stage->currentstage);
		if (Stage->time[Stage->currentstage - 1] <= 0)
		{
			//游戏结束
			Stage->reset();
			//auto dialog = RebornDialog::create(m_gamePanel);
			//MainScene::theScene()->showDialog(dialog);

			pausePanel();
			SoundMgr::theMgr()->playEffect(kEffectMusicButton);
			MainScene::theScene()->showDialog(GameOverDialog::create());
		}
		int a = Stage->foods[Stage->currentstage - 1];
		CCLOG("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb%d", a);
		if (Stage->foods[Stage->currentstage - 1] <= 0)
		{
			//下一关
			Stage->currentstage += 1;
			pausePanel();
			SoundMgr::theMgr()->playEffect(kEffectMusicButton);


			MainScene::theScene()->showDialog(NextStageDialog::create());
		}
	}
	
}

void GamePanel::setFocus(cocos2d::CCPoint pos)
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint newPos;
	newPos.x = winSize.width * 0.5f - pos.x + GAME_LAYER_WIDTH * 0.5f;
	newPos.y = winSize.height * 0.5f - pos.y + GAME_LAYER_HEIGHT * 0.5f;
	
	m_snakeField->setPosition(newPos);
}

void GamePanel::initSnakes()
{

	SnakeData data;
	data.length = INIT_SNAKE_LENGTH;
	data.skinId = data.skinId = PlayerData::theData()->getNpcId(0);
	//data.length = 100; 
	m_playsnake = PlayerSnake::create(this, data);
	
	addSnake(m_playsnake);
	//return;
	for (int i = 0; i < SNAKE_NUM; ++i)
	{
		SnakeData data;
		data.length = INIT_SNAKE_LENGTH;
		data.skinId = PlayerData::theData()->getNpcId(i+1);
		data.name = RankingModel::theModel()->getNpcName(i);
		addSnake(EnemySnake::create(this, data));
	}
	//addFood(cocos2d::ccColor3B color, cocos2d::CCPoint pos);

}

void GamePanel::initGhost()
{
	for (int i = 1; i < Stage->ghost[Stage->currentstage]; ++i)
	{

		addGhost(Ghost::onCreat(this,m_playsnake));
	}

}

void GamePanel::addSnake(Snake *snake)
{
	m_snakeField->addChild(snake,0);
	m_snakes.push_back(snake);
	updateTarget();
}

void GamePanel::addGhost(Ghost *ghost)
{
	m_ghostField->addChild(ghost);
	m_ghosts.push_back(ghost);
}

void GamePanel::removeSnake(Snake *snake)
{

	snake->removeFromParent();
	auto iter = find(m_snakes.begin(), m_snakes.end(), snake);
	if (iter != m_snakes.end())
	{
		//注意：这里删除snake 会不会导致上层的遍历出错？
		m_snakes.erase(iter);
	}
	updateTarget();

}

void GamePanel::updateTarget()
{
	for (auto gho : m_ghosts)
	{
		gho->targetSnake();
	}
}

void GamePanel::addFood(cocos2d::ccColor3B color, cocos2d::CCPoint pos)
{
	if (pos.x <= 10) pos.x = 10;
	if (pos.x >= GAME_LAYER_WIDTH - 10) pos.x = GAME_LAYER_WIDTH - 10;
	if (pos.y <= 10) pos.y = 10;
	if (pos.y >= GAME_LAYER_HEIGHT - 10) pos.y = GAME_LAYER_HEIGHT - 10;
	char str[100] = { 0 };
	sprintf(str, "game_scene/food_0%d.png", getRandomValue(0, 3));
	auto food = new Food(str);
	food->getView()->setPosition(pos);
	m_snakeBatchNode->addChild(food->getView(), -10000);
	m_foodMgr->addFood(food);
}

void GamePanel::addFood(std::string path, cocos2d::CCPoint pos)
{
	/*if (pos.x <= 10) pos.x = 10;
	if (pos.x >= GAME_LAYER_WIDTH - 10) pos.x = GAME_LAYER_WIDTH - 10;
	if (pos.y <= 10) pos.y = 10;
	if (pos.y >= GAME_LAYER_HEIGHT - 10) pos.y = GAME_LAYER_HEIGHT - 10;

	auto food = new Food(path);
	food->getView()->setPosition(pos);
	m_snakeBatchNode->addChild(food->getView(), -9999);
	m_foodMgr->addFood(food);*/
}

void GamePanel::onBackKeyTouched()
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
}