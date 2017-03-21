#include "EnemySnake.h"
#include "CommonMacro.h"
#include "Snake.h"
#include "CommonUtil.h"
#include "GamePanel.h"
#include "RankingModel.h"
#include "PlayerData.h"
USING_NS_CC;
using namespace std;

EnemySnake::EnemySnake(GamePanel *gamePanel, const SnakeData &data)
: Snake(gamePanel,data)
, m_godLikeTime(0)
, m_speedUpTime(0)
, m_speedTime(0)
, m_onspeedTime(2)
, is_autospeed(false)
{

}
vector<float> randspeedup = {1.2f};
vector<float> randgodlike = { 2.9f };

void EnemySnake::onExit()
{
	PlayerData::theData()->addRebornId(m_data.skinId);
	Snake::onExit();
	RankingModel::theModel()->removeRank(m_data.name);
	SnakeController::controller()->removeView(this);
}

void EnemySnake::onEnter()
{
	Snake::onEnter();
	SnakeController::controller()->addView(this);
	SnakeController::controller()->npcgodLike();
}
EnemySnake *EnemySnake::create(GamePanel *gamePanel, const SnakeData &data)
{
	EnemySnake *snake = EnemySnake::onCreat(gamePanel, data);
	snake->init();
	//snake->autorelease();
	return snake;
}
void EnemySnake::addHead()
{
	auto path = SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame("sprite_frames/gni_idle_00000.png");
	//CCSpriteFrame *he = CCSpriteFrame::create("sprite_frames/gni_idle_00000.png",);
	auto head = CCSprite::create(SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId).c_str());//SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId).c_str()
	CCAnimation *animation = CCAnimation::create();
	//从本地文件系统中加载图片文件到CCSpriteFrame中区，然后添加到CCAnimation中  
	for (int i = 0; i < 2; i++)
	{
		char szImageFileName[128] = { 0 };
		sprintf(szImageFileName, SnakeSkinRes::SnakeResData()->getTailRes(m_data.skinId).c_str(), m_data.skinId,i);
		animation->addSpriteFrameWithFileName(szImageFileName);
	}
	animation->setDelayPerUnit(0.2f); // 这个动画包含14帧，将会持续2.8秒.  
	animation->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧  

	CCAnimate *action = CCAnimate::create(animation);
	head->runAction(CCRepeatForever::create(action));  // 运行精灵对象  
	head->setScale(m_scale);
	m_gamePanel->getSnakeBatch()->addChild(head);

	m_nameLabel = CCLabelTTF::create("", "fonts/ReeJi-BigRuiqiao-RegularGBV1.0.ttf", 17);
	m_nameLabel->setColor(ccc3(255, 251, 240));
	addChild(m_nameLabel, 1);
	m_body.push_back(head);
}
bool EnemySnake::init()
{
	CCPoint pos;
	pos.x = CommonUtil::getRandomValue(0, GAME_LAYER_WIDTH);
	pos.y = CommonUtil::getRandomValue(0, GAME_LAYER_HEIGHT);
	initBodyPos(pos);

	if (m_data.name.empty())
	{
		m_data.name = RankingModel::theModel()->applyName();
	}
	m_nameLabel->setString(m_data.name.c_str());
	return true;
}
EnemySnake * EnemySnake::onCreat(GamePanel *gamePanel, const SnakeData &data)
{
	EnemySnake* pSnake = new EnemySnake(gamePanel, data);

	if (pSnake && pSnake->initSnake())
	{
		pSnake->autorelease();
	}
	else
	{
		//CC_SAFE_DELETE(pSnake);
	}

	return pSnake;

}

void EnemySnake::onMove(cocos2d::CCPoint pos)
{
	const float detectSize = 50;

	if ((pos.x < detectSize && (90 < m_destAngle && m_destAngle < 270))
		|| (pos.x > GAME_LAYER_WIDTH - detectSize && (90 > m_destAngle || m_destAngle > 270)))
	{
		m_destAngle = 180 - m_destAngle;
	}
	else if (pos.y < detectSize && (m_destAngle > 180)
		|| (pos.y > GAME_LAYER_HEIGHT - detectSize && (m_destAngle < 180)))
	{
		m_destAngle = -m_destAngle;
	}

	m_destAngle = (m_destAngle + 360) % 360;
	detectCollision();
}


void EnemySnake::onDead()
{
	//auto snake = EnemySnake::create(m_gamePanel);
	//m_gamePanel->addSnake(snake);
	//m_gamePanel->removeSnake(this);
	//removeFromParent();
}

void EnemySnake::detectCollision()
{
	auto ghosts = m_gamePanel->getGhosts();
	for (auto gho : ghosts)
	{
		if (gho->willCrash(getHead()->getPosition(), m_destAngle))
		{
			m_destAngle += CommonUtil::getRandomValue(90, 270);
			return;
		}
	}
}

void EnemySnake::onSpeedUp(bool enable)
{
	/*m_isSpeedUp = false;
	if (!enable)
	{
		m_speed = NORMAL_SPEED;
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

	}*/
}

void EnemySnake::onNpcGrow()
{
	//addBody();
	m_onspeedTime = 2.0f;
	m_speed = NORMAL_SPEED * 2.0f;
	is_autospeed = true;
}

void EnemySnake::onNpcGodLike()
{
	//godtime!!!!!!!!
	const int kTime = 10.0f;
	m_godLikeTime += kTime;
}

void EnemySnake::onUpdate(float dt)
{
	if (CommonUtil::getResultByPercent(randgodlike) && CommonUtil::getResultByPercent(randgodlike))
	{
		onNpcGodLike();
	}
	if (CommonUtil::getResultByPercent(randspeedup) && CommonUtil::getResultByPercent(randspeedup))
	{
		onNpcGrow();
	}
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
		m_speedUpTime += dt;
		m_speedTime -= dt;
		if (m_speedTime <= 0)
		{
			m_speed = NORMAL_SPEED;
			m_speedTime = 0;
		}
		if (m_speedUpTime >= 3.0f)
		{
			removeBody();
			m_speedUpTime = 0;
		}
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
			this->addChild(particleSystem, -99, 22);
		}

		particleSystem->setPosition(ccp(getHead()->getPositionX(), getHead()->getPositionY()));
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

void EnemySnake::reborn()
{
	RankingModel::theModel()->removeRank(m_data.name);
}