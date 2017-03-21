#include "PlayerSnake.h"
#include "ActionRunner.h"
#include "CommonMacro.h"
#include "MainScene.h"
#include "GamePanel.h"
#include "GameOverDialog.h"
#include "PlayerData.h"
#include "RebornDialog.h"
#include "RankingModel.h"

USING_NS_CC;
using namespace std;

PlayerSnake::PlayerSnake(GamePanel *gamePanel, const SnakeData &data)
: Snake(gamePanel, data)
, m_godLikeTime(0)
, m_speedUpTime(0)
, m_speedTime(0)
, m_onspeedTime(5)
, is_autospeed(false)
{
	m_runner = ActionRunner::create();
	m_runner->retain();

}

PlayerSnake::~PlayerSnake()
{
	m_runner->clear();
	m_runner->release();
}

PlayerSnake *PlayerSnake::create(GamePanel *gamePanel, const SnakeData &data)
{
	//PlayerSnake *snake = new PlayerSnake(gamePanel, data);
	PlayerSnake *snake = PlayerSnake::onCreat(gamePanel, data);
	snake->init();
	//snake->autorelease();
	return snake;
}

PlayerSnake * PlayerSnake::onCreat(GamePanel *gamePanel, const SnakeData &data)
{
	PlayerSnake* pSnake = new PlayerSnake(gamePanel, data);

	if (pSnake && pSnake->initSnake())
	{
		pSnake->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pSnake);
	}

	return pSnake;

}

CCPoint PlayerSnake::getPPoingt()
{
	return this->getPosition();
}

void PlayerSnake::onEnter()
{
	Snake::onEnter();
	SnakeController::controller()->addView(this);
	SnakeController::controller()->godLike();
}

void PlayerSnake::onExit()
{
	Snake::onExit();
	SnakeController::controller()->removeView(this);
	RankingModel::theModel()->removeRank(m_data.name);
}

void PlayerSnake::reborn()
{
	RankingModel::theModel()->removeRank(m_data.name);
}

bool PlayerSnake::init()
{
	auto size = CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT);
	initBodyPos(ccpMult(size, 0.5f));

	if (m_data.name.empty())
	{
		m_data.name = PlayerData::theData()->getName();
	}
	m_nameLabel->setString(m_data.name.c_str());
	return true;
}

void PlayerSnake::onAngleChanged(int angle)
{
	m_destAngle = angle;
}

void PlayerSnake::onSpeedUp(bool enable)
{
	m_isSpeedUp = false;
	if (!enable)
	{
		m_speed = NORMAL_SPEED;
		if (getChildByTag(22) != NULL)
		{
			particleSystem->removeFromParent();
			particleSystem = NULL;
		}

	}
	else //if (m_body.size() > INIT_SNAKE_LENGTH)
	{
		if (m_speedTime > 0)
		{
			m_speed = NORMAL_SPEED * 2.0f;
			m_isSpeedUp = true;
		}
		else
		{
			m_speed = NORMAL_SPEED;

		}

	}
}

void PlayerSnake::onGrow()
{
	//addBody();
	m_onspeedTime = 5.0f;
	m_speed = NORMAL_SPEED * 2.0f;
	is_autospeed = true;
}

void PlayerSnake::onGodLike()
{
	//godtime!!!!!!!!
	const int kTime = 5.0f;
	m_godLikeTime += kTime;
}

void PlayerSnake::onUpdate(float dt)
{
	if (m_godLikeTime > 0)
	{
		m_godLikeTime -= dt;
		if (m_godLikeTime <= 0)
		{
			m_godLikeTime = 0;
			setGodLikeState(false);
		}
		else
		{
			setGodLikeState(true);
		}
	}
	//按钮加速
	if (m_isSpeedUp&&!is_autospeed)
	{



		if (getChildByTag(22) == NULL)
		{
			particleSystem = CCParticleMeteor::create();
			particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("game_scene/slot_star_2.png"));
			particleSystem->setPositionType(kCCPositionTypeRelative);
			this->addChild(particleSystem,-99, 22);
		}

		particleSystem->setPosition(ccp(getHead()->getPositionX(), getHead()->getPositionY()));
		m_speedUpTime += dt;
		m_speedTime -= dt;
		if (m_speedTime <= 0)
		{
			if (getChildByTag(22) != NULL)
			{
				particleSystem->removeFromParent();
				particleSystem = NULL;
			}
			m_speed = NORMAL_SPEED;
			m_speedTime = 0;
		}
		/*if (m_speedUpTime >= 3.0f)
		{
			removeBody();
			m_speedUpTime = 0;
		}*/
		//m_isSpeedUp = m_body.size() > INIT_SNAKE_LENGTH;//当加速过程中，蛇长度达到最小，不能加速
		if (!m_isSpeedUp)
		{

			m_speed = NORMAL_SPEED;
		}

	}
	//自动加速
	if (is_autospeed)
	{
		if (getChildByTag(22) == NULL)
		{
			particleSystem = CCParticleMeteor::create();
			particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("game_scene/slot_star_2.png"));
			particleSystem->setPositionType(kCCPositionTypeRelative);
			this->addChild(particleSystem, -1, 22);
		}

		particleSystem->setPosition(getHead()->getPosition());
		m_onspeedTime -= dt;
		if (m_onspeedTime <= 0)
		{
			if (getChildByTag(22) != NULL)
			{
				particleSystem->removeFromParent();
				particleSystem = NULL;
			}
			m_speed = NORMAL_SPEED;
			m_onspeedTime = 0;
			is_autospeed = false;
		}
		if (!is_autospeed)
		{
			m_speed = NORMAL_SPEED;
		}


	}
}

void PlayerSnake::onEatFood()
{
	PlayerData::theData()->setData(m_data);
	m_speedTime += 1.0f;
	//SnakeController::controller()->snakeDataChanged();
}

void PlayerSnake::onMove(cocos2d::CCPoint pos)
{
	m_gamePanel->setFocus(pos);
}

void PlayerSnake::onDead()
{
	//MainScene::theScene()->showDialog(GameOverDialog::create());
	//SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	

	auto dialog = RebornDialog::create(m_gamePanel);
	MainScene::theScene()->showDialog(dialog);
	int score = (PlayerData::theData()->getData().score);
	int historyScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("PlayerMaxScore", 0);
	if (historyScore < score)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("PlayerMaxScore", score);
	}
}
