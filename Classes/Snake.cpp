#include "Snake.h"
#include "UiLayout.h"
#include <cmath>
#include "SnakeColor.h"
#include "CommonUtil.h"
#include "GamePanel.h"
#include "Food.h"
#include "RankingModel.h"
#include "PlayerData.h"
#include "CCCircleBy.h"
USING_NS_CC;
using namespace std;
using namespace CommonUtil;
Snake::Snake(GamePanel *gamePanel, const SnakeData &data)
: m_gamePanel(gamePanel)
, m_speed(NORMAL_SPEED)
, m_angle(0)
, m_destAngle(0)
, m_growEnergy(0)
, m_isGodlike(false)
, m_data(data)
, m_isSpeedUp(false)
, m_scale(1.5f)
, m_speedTime(0)
, act(NULL)
{
	m_destAngle = CommonUtil::getRandomValue(0, 359);
	m_angle = m_destAngle;
	//initSnake();
}

void Snake::onExit()
{
	CCNode::onExit();
	for (auto body : m_body)
	{
		//body->removeFromParent();
		body->setVisible(false);
	}
}
Snake * Snake::onCreat(GamePanel *gamePanel, const SnakeData &data)
{
	Snake* pSnake = new Snake(gamePanel,  data );

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

bool Snake::initSnake()
{
	addHead();
	//addTail();
	/*for (int i = 1; i < m_data.length - 1; ++i)
	{
		addBody();
	}*/
	return true;
	
}

void Snake::reborn()
{
	//RankingModel::theModel()->removeRank(m_data.name);
}

void Snake::addHead()
{
	auto path = SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame("sprite_frames/gni_idle_00000.png");
	//CCSpriteFrame *he = CCSpriteFrame::create("sprite_frames/gni_idle_00000.png",);
	auto head = CCSprite::create(SnakeSkinRes::SnakeResData()->getHeadRes(PlayerData::theData()->getNpcId(0)).c_str());//SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId).c_str()
	int i = PlayerData::theData()->getNpcId(0);
	CCAnimation *animation = CCAnimation::create();
	//从本地文件系统中加载图片文件到CCSpriteFrame中区，然后添加到CCAnimation中  
	for (int i = 0; i < 2; i++)
	{
		char szImageFileName[128] = { 0 };
		sprintf(szImageFileName, "sprite_frames/pic_%d_%d.png", PlayerData::theData()->getNpcId(0),i);
		animation->addSpriteFrameWithFileName(szImageFileName);
	}
	animation->setDelayPerUnit(0.2f); // 这个动画包含14帧，将会持续2.8秒.  
	animation->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧  

	CCAnimate *action = CCAnimate::create(animation);
	head->runAction(CCRepeatForever::create(action));  // 运行精灵对象  
	head->setScale(m_scale);
	m_gamePanel->getSnakeField()->addChild(head,999);

	m_nameLabel = CCLabelTTF::create("", "fonts/ReeJi-BigRuiqiao-RegularGBV1.0.ttf", 17);
	m_nameLabel->setColor(ccc3(255, 251, 240));
	addChild(m_nameLabel, 1);
	m_body.push_back(head);
}

void Snake::addBody()
{
	/*int pos = m_body.size() + 1;
	auto path = SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, pos);
	CCSprite *body = CCSprite::createWithSpriteFrameName(SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, pos).c_str());
	body->setScale(m_scale);
	m_gamePanel->getSnakeBatch()->addChild(body, -pos);
	body->setPosition(m_body.back()->getPosition());
	m_body.insert(m_body.begin() + m_body.size() - 1, body);*/
}

void Snake::addTail()
{
	/*auto path = SnakeSkinRes::SnakeResData()->getTailRes(m_data.skinId);
	auto tail = CCSprite::createWithSpriteFrameName(SnakeSkinRes::SnakeResData()->getTailRes(m_data.skinId).c_str());
	tail->setScale(m_scale);
	m_gamePanel->getSnakeBatch()->addChild(tail, -9999);
	m_body.push_back(tail);*/
}

void Snake::removeBody()
{
	if (m_body.size() <= 2) return; //只剩下头和尾
	//m_body[m_body->size() - 1]
	m_body[m_body.size() - 2]->removeFromParent();
	m_body.erase(m_body.begin() + m_body.size() - 2);
}

void Snake::initBodyPos(cocos2d::CCPoint pos)
{
	for (auto body : m_body)
	{
		body->setPosition(pos);
	}
}

void Snake::update(float dt)
{
	//更新蛇长度
	/*m_data.length = m_body.size();
	for (auto body : m_body)
	{
		m_scale = min((m_body.size() / 50.0f), 1.0f) * 0.3f + 0.5f;
		body->setScale(m_scale);
	}*/

	//移动方向
	int angleOffset = m_destAngle - m_angle;
	if (abs(angleOffset) < 5)
	{
		m_angle = m_destAngle;
	}
	else if ((0 < angleOffset && angleOffset < 180) || angleOffset < -180)
	{
		m_angle += 500 * dt;//逆时针
	}
	else
	{
		m_angle -= 500 * dt;//顺时针
	}
	//旋转头，身体
	if (m_destAngle <= 30 || m_destAngle >= -340)//右
	{
		dynamic_cast<CCSprite*>(getHead())->setFlipY(false);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(false);
		getHead()->setRotation(0);
	}
	if (m_destAngle >=150  && m_destAngle <= 210)//左
	{
		//dynamic_cast<CCSprite*>(getHead())->setFlipY(true);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(true);
		getHead()->setRotation(0);
	}
	if (m_destAngle > 120 && m_destAngle < 150)//左上
	{
		dynamic_cast<CCSprite*>(getHead())->setFlipY(true);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(false);
		getHead()->setRotation(-135);
	}

	m_angle = (m_angle + 360) % 360;
	if (m_destAngle > 30 && m_destAngle < 60)//右上
	{
		dynamic_cast<CCSprite*>(getHead())->setFlipY(false);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(false);
		getHead()->setRotation(-45);

	}
	//CCLOG("m_angle: %d", m_angle);
	//getHead()->setRotation(90 - m_angle);//头部选中
	if (m_destAngle > 60 && m_destAngle < 120)//上
	{
		dynamic_cast<CCSprite*>(getHead())->setFlipY(false);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(false);
		getHead()->setRotation(-90);

	}
	if (m_destAngle > 210 && m_destAngle < 240)//左下
	{
		dynamic_cast<CCSprite*>(getHead())->setFlipY(true);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(false);

		getHead()->setRotation(135 );

	}
	if (m_destAngle > 240 && m_destAngle < 300)//下
	{
		dynamic_cast<CCSprite*>(getHead())->setFlipY(false);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(false);

		getHead()->setRotation(90);

	}
	if (m_destAngle > 300 && m_destAngle < 340)//右下
	{
		dynamic_cast<CCSprite*>(getHead())->setFlipY(false);
		dynamic_cast<CCSprite*>(getHead())->setFlipX(false);

		getHead()->setRotation(45);

	}

	for (size_t i = 1; i < m_body.size(); ++i)
	{
		auto pos1 = m_body[i - 1]->getPosition();
		auto pos2 = m_body[i]->getPosition();
		int rotation = CommonUtil::getRotation(pos1, pos2);
		m_body[i]->setRotation(270 - rotation);
	}
	
	//更新头部坐标
	CCPoint offset;
	offset.x = cos(m_angle * M_PI / 180) *dt * m_speed;
	offset.y = sin(m_angle * M_PI / 180) *dt * m_speed;
	auto pos = ccpAdd(getHead()->getPosition(), offset);
	getHead()->setPosition(pos);
	m_nameLabel->setPosition(ccpAdd(pos, ccp(0, 40)));
	m_path.push_front(make_pair(pos, 0));
	onMove(pos);

	for (size_t i = 1; i < m_path.size(); ++i)
	{
		m_path[i].second += dt * m_speed;
	}
	//遍历所有蛇节点，在指定长度上更新位置
	const float kDistance = 30 * m_scale;
	int curIndex = 1;
	for (size_t bodyIndex = 1; bodyIndex < m_body.size(); ++bodyIndex)
	{
		for (int i = curIndex; i < m_path.size(); ++i)
		{
			auto length = m_path[i].second;
			curIndex = i;
			if (length >= kDistance * bodyIndex)
			{
				auto prevPos = m_path[i - 1].first;
				auto myPos = m_path[i].first;
				int dx = myPos.x - prevPos.x;
				int dy = myPos.y - prevPos.y;
				auto distance = ccpDistance(prevPos, myPos);
				auto newPos = ccpAdd(prevPos, ccpMult(ccp(dx, dy), (kDistance * bodyIndex - m_path[i - 1].second) / distance));
				m_body[bodyIndex]->setPosition(newPos);
				break;
			}
		}
	}

	int newSize = m_path.size();
	for (int i = 1; i < m_path.size(); ++i)
	{
		if (m_path[i].second > kDistance *(m_body.size() - 1))
		{
			newSize = i + 1;
			break;
		}
	}
	
	m_path.resize(newSize);
	CCLOG("m_path.size(): %d", m_path.size());

	onUpdate(dt);
	if (checkCrash())
	{
		crash();
	}

}

void Snake::setGodLikeState(bool open)
{
	m_isGodlike = open;
	if (act == NULL)
	{
		act = CCSprite::create("game_scene/star2.png");
	}

	for (auto body : m_body)
	{
		auto self = dynamic_cast<CCSprite *>(body);
		if (self)
		{
			if (open)
			{

				

				if (this->getChildByTag(88) == NULL)
				{
					act->setVisible(true);
					//act->setPosition(ccp(50, 50));
					this->addChild(act, 999,88);
					act->runAction(CCCircleBy::creat(900000.0, ccp(self->getContentSize().width/2, self->getContentSize().height/2), 55,this));
				}
				act->setColor(ccc3(getRandomValue(0, 255) / 1.0, getRandomValue(0, 255) / 1.0, getRandomValue(0, 255) / 1.0));

			}
			else
			{
				act->setVisible(false);
				act->stopAllActions();
				act->cleanup();
				act->removeFromParent();
				act = NULL;
			}
			//self->setOpacity(open ? 128 : 255);
		}

		/*auto children = body->getChildren();
		CCObject* pObj;
		CCARRAY_FOREACH(children, pObj)
		{
			CCSprite* pNode = dynamic_cast<CCSprite*>(pObj);
			if (pNode)
			{
				pNode->setOpacity(open ? 128 : 255);
			}
		}*/
	}
}

bool Snake::checkCrash()
{
	auto pos = getHead()->getPosition();
	if (pos.x < 0 || pos.x > GAME_LAYER_WIDTH || pos.y < 0 || pos.y > GAME_LAYER_HEIGHT)
	{
		return true;
	}
	if (m_isGodlike)//如果无敌，不检测与其他蛇碰撞
	{
		return false;
	}

	auto snakes = m_gamePanel->getSnakes();
	auto ghosts = m_gamePanel->getGhosts();

		for (auto ghost : ghosts)
		{
			if (isCrash(ghost->getHead()->getPosition()))
			{
				return true;
			}
			
		}


	return false;
}

static CCPoint getRandomPt()
{
	CCPoint pt;
	pt.x = CommonUtil::getRandomValue(0, 10);
	pt.y = CommonUtil::getRandomValue(0, 10);
	return pt;
}

void Snake::crash()
{
	isdead = true;
	onDead();
	/*for (size_t i = 0; i < m_body.size(); ++i)
	{
		auto body = m_body[i];
		auto pos = body->getPosition();
		auto path = SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, i + 1);
		m_gamePanel->addFood(path, ccpAdd(pos, getRandomPt()));
	}*/

	m_gamePanel->removeSnake(this);
	CCLOG("Snake::crash!!!!");
}

bool Snake::willCrash(cocos2d::CCPoint pt, int destAngle)
{
	for (size_t i = 0; i < m_body.size(); ++i)
	{
		int angle = 0;
		float dy = m_body[i]->getPosition().y - pt.y;
		float dx = m_body[i]->getPosition().x - pt.x;
		if (abs(dx) > 200 || abs(dy) > 200) return false;
		if (dx == 0)
		{
			if (dy > 0) angle = 90;
			else angle = -90;
		}
		else
		{
			angle = atan(dy / dx) * 180 / M_PI;
			if (dx < 0) angle += 180;
		}

		angle = (angle + 360) % 360;
		if (abs(angle - destAngle) < 10)
		{
			return true;
		}
	}
	return false;
}
int a=0;
bool Snake::isCrash(cocos2d::CCPoint pt)
{
	for (auto body : m_body)
	{
		a++;
		CCLOG("ffffffffff%d %f %f",a,pt.x,pt.y);
		auto pos = body->getPosition();
		float dis = ccpDistance(pos, pt);
		if (dis < 60)
		{

			return true;
		}
	}
	return false;
}

bool Snake::canEatFood(CCPoint pt)
{
	auto pos = getHead()->getPosition();
	return abs(pos.x - pt.x) < 20 && abs(pos.y - pt.y) < 20;
}

void Snake::eatFood(int energy)
{
	RankingModel::theModel()->updateScore(m_data.name, m_data.score);
	m_data.score += energy * 100;
	int const kEnergyToGrow = 10;
	/*m_growEnergy += energy;
	if (m_growEnergy >= kEnergyToGrow)
	{
		int num = m_growEnergy / kEnergyToGrow;
		m_growEnergy = m_growEnergy % kEnergyToGrow;
		for (int i = 0; i < num; ++i)
		{
			addBody();
		}
	}*/
	m_speedTime += 1.0f;
	onEatFood();
}