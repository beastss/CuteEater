#include "FoodMgr.h"
#include "GamePanel.h"
#include "Snake.h"
#include "Food.h"
#include "CommonUtil.h"
#include "CommonMacro.h"
USING_NS_CC;
using namespace std;

void FoodMgr::update(float dt)
{
	checkKill();
	//genNewFood();
}

void FoodMgr::checkKill()
{
	auto snakes = m_gamePanel->getSnakes();
	for (auto iter = m_foods.begin(); iter != m_foods.end();)
	{
		auto food = *iter;
		bool isDead = false;
		for (auto snake : snakes)
		{
			if (snake->canEatFood(food->getView()->getPosition()))
			{
				snake->eatFood(food->getEnergy());
				food->onEaten(snake->getHead()->getPosition());
				isDead = true;
				break;
			}
		}
		if (isDead)
		{
			iter = m_foods.erase(iter);
			Stage->foods[Stage->currentstage - 1]--;
		}
		else
		{
			++iter;
		}
	}
}

void FoodMgr::genNewFood(int count)
{

		for (int i = 0; i < count; ++i)
		{
			auto color = CommonUtil::getRandomColor();
			CCPoint pos;
			pos.x = CommonUtil::getRandomValue(0, GAME_LAYER_WIDTH);
			pos.y = CommonUtil::getRandomValue(0, GAME_LAYER_HEIGHT);
			m_gamePanel->addFood(color, pos);
		}
	
}

void FoodMgr::addFood(Food *food)
{
	m_foods.push_back(food);
}
int FoodMgr::leftFood()
{
	return m_foods.size();
}