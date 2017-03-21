#include "Ghost.h"
#include "CommonMacro.h"
#include "Snake.h"
#include "CommonUtil.h"
#include "GamePanel.h"
#include "RankingModel.h"
using namespace CommonUtil;
USING_NS_CC;
using namespace std;
vector<CCPoint> randpos ={ ccp(-100, -28), ccp(59,-400), ccp(-188,200), ccp(-249, 110), ccp(117, 210),ccp(-40,-88) ,ccp(200,100)};
vector<CCPoint> randpos2 = { ccp(1200, 190), ccp(600, 700), ccp(800, 200), ccp(1400, 1000) ,ccp(400,1000)};//越界用
Ghost::Ghost(GamePanel *gamePanel,PlayerSnake *playerSnake)
:m_gamePanel(gamePanel),
m_playerSnake(playerSnake),
m_scal(1.5),
lengt(0),
leftdt(0)
{

}

void Ghost::onExit()
{
	CCNode::onExit();
	for (auto body : m_body)
	{
		body->removeFromParent();
	}
	//RankingModel::theModel()->removeRank(m_data.name);
}

bool Ghost::initGhost()
{
	addHead();
	CCPoint pos;
	pos.x = CommonUtil::getRandomValue(0, GAME_LAYER_WIDTH);
	pos.y = CommonUtil::getRandomValue(0, GAME_LAYER_HEIGHT);
	initBodyPos(pos);
	return true;
}
void Ghost::initBodyPos(cocos2d::CCPoint pos)
{
	for (auto body : m_body)
	{
		body->setPosition(pos);
	}
}

Ghost *Ghost::create(GamePanel *gamePanel,PlayerSnake * playsnake)
{
	Ghost *ghost = Ghost::onCreat(gamePanel, playsnake);
	ghost->init();
	//snake->autorelease();
	return ghost;
}
void Ghost::addHead()
{
	//auto path = SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame("sprite_frames/gni_idle_00000.png");
	//CCSpriteFrame *he = CCSpriteFrame::create("sprite_frames/gni_idle_00000.png",);
	auto head = CCSprite::create("sprite_frames/ghost0.png");//SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId).c_str()
	CCAnimation *animation = CCAnimation::create();
	//从本地文件系统中加载图片文件到CCSpriteFrame中区，然后添加到CCAnimation中  
	for (int i = 0; i < 2; i++)
	{
		char szImageFileName[128] = { 0 };
		sprintf(szImageFileName, "sprite_frames/ghost%d.png", i);
		animation->addSpriteFrameWithFileName(szImageFileName);
	}
	animation->setDelayPerUnit(0.2f); // 这个动画包含14帧，将会持续2.8秒.  
	animation->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧  

	CCAnimate *action = CCAnimate::create(animation);
	head->runAction(CCRepeatForever::create(action));  // 运行精灵对象  
	head->setScale(m_scal);
	m_gamePanel->getSnakeBatch()->addChild(head,9);
	m_body.push_back(head);

}
bool Ghost::init()
{
	CCPoint pos;
	pos.x = CommonUtil::getRandomValue(0, GAME_LAYER_WIDTH);
	pos.y = CommonUtil::getRandomValue(0, GAME_LAYER_HEIGHT);
	initBodyPos(pos);
	targetSnake();
	return true;
}
Ghost * Ghost::onCreat(GamePanel *gamePanel, PlayerSnake *playerSnake)
{
	Ghost* pSnake = new Ghost(gamePanel,playerSnake);

	if (pSnake && pSnake->initGhost())
	{
		pSnake->autorelease();
	}
	else
	{
		//CC_SAFE_DELETE(pSnake);
	}

	return pSnake;

}

void Ghost::onMove(cocos2d::CCPoint pos)
{
	const float detectSize = 50;

	
	detectCollision();
}


void Ghost::onDead()
{
//	auto snake = Ghost::create(m_gamePanel);
	//m_gamePanel->addSnake(snake);
}

void Ghost::detectCollision()
{
	/*auto snakes = m_gamePanel->getSnakes();
	for (auto snake : snakes)
	{
	if (snake != this && snake->willCrash(getHead()->getPosition(), m_destAngle))
	{
	m_destAngle += CommonUtil::getRandomValue(90, 270);
	return;
	}
	}*/
}

bool Ghost::willCrash(cocos2d::CCPoint pt, int destAngle)
{
	for (size_t i = 0; i < m_body.size(); ++i)
	{
		int angle = 0;
		float dy = m_body[i]->getPosition().y - pt.y;
		float dx = m_body[i]->getPosition().x - pt.x;
		if (fabs(dx) > 200 || fabs(dy) > 200) return false;
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

void Ghost::update(float dt)
{
	if (tarsnake!=NULL)
	{
		aiMove(dt);
	}
	else{
		randmove(dt);
	}








}
void Ghost::targetSnake()
{
	tarsnake = NULL;
	for (auto snake : m_gamePanel->getSnakes())
	{
		if (getRandomValue(0, 1))
		{

			tarsnake = snake;
			return;
		}
	}
	if (m_gamePanel->getSnakes().size() < 1)
	{

	}
	else
	{
		if (tarsnake == NULL)
		{
			tarsnake = m_gamePanel->getSnakes()[0];
		}
		
	}
	
}
int speed = 250;
void Ghost::aiMove(float dt)
{

	float s = getRandomValue(0, 10);
	CCPoint p = tarsnake->getHead()->getPosition();


	CCPoint j = getHead()->getPosition();
	CCCallFuncN *caction;
	auto pos = getHead()->getPosition();
	if (pos.x < 80 || pos.x > GAME_LAYER_WIDTH - 80 || pos.y < 80 || pos.y > GAME_LAYER_HEIGHT - 80 || leftdt > 0)
	{
		targetSnake();
		if (leftdt == 0)
			leftdt = 1.7;
		//getHead()->stopAllActions();
		p = (ccp(1000,1000));
		j = getHead()->getPosition();
		float a = speed*dt / p.getDistance(j);
		p = ccpSub(p, j);
		p = ccpMult(p, a);
		//p = ccpMult(p, dt);
		//CCAction * action = CCSequence::create(CCMoveBy::create(dt, p), NULL);
		getHead()->setPosition(ccpAdd(j, p));
		onMove(CCPointZero);
		leftdt -= dt;


	}
	else{
		leftdt = 0;

		if (p.getDistance(j) < 199)
		{
			//getHead()->stopAllActions();
			j = getHead()->getPosition();
			float a = speed*dt / p.getDistance(j);
			p = ccpSub(p, j);
			p = ccpMult(p, a);
			//p = ccpMult(p, dt);
			//CCAction * action = CCSequence::create(CCMoveBy::create(dt, p), NULL);
			getHead()->setPosition(ccpAdd(j, p));
			onMove(CCPointZero);
		}
		else{
			randmove(dt);
			onMove(CCPointZero);
		}
	}
}

void Ghost::randmove(float dt)
{

	CCPoint j = getHead()->getPosition();
	if (j.x < 50 || j.x > GAME_LAYER_WIDTH-50 || j.y < 50 || j.y > GAME_LAYER_HEIGHT-50)
	{
		if (lengt == 0)
		{
			CCPoint g = randpos2[getRandomValue(0, randpos2.size() - 1)];
			target = ccpSub(g,j);
			lengt = target.getDistance(j);

		}
		if (lengt < 0)
		{
			lengt = 0;
			
		}
		if (lengt>0){
			lengt -= speed*dt*1.1;


		}



		
	}
	else
	{
		if (lengt == 0)
		{
			CCPoint g = randpos[getRandomValue(0, randpos.size() - 1)];
			target = ccpAdd(j, g);
			lengt = target.getDistance(j);

		}
		if (lengt < 0)
		{
			lengt = 0;
		}
		if (lengt>0){
			lengt -= speed*dt*1.1;


		}
	}
	

	float a = speed*dt / target.getDistance(j);
	CCPoint temp;
	temp = ccpSub(target, j);
	temp = ccpMult(temp, a);
	CCLog("tar%f,%f", target.x, target.y);
	CCLog("pos%f,%f", j.x, j.y);
	//p = ccpMult(p, dt);
	getHead()->setPosition(ccpAdd(j, temp));
	//CCAction * action = CCSequence::create(CCMoveBy::create(dt, temp), NULL);
	//getHead()->runAction(action);
}