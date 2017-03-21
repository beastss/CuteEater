#include "DataLoader.h"
#include "SnakeColor.h"
#include "SoundMgr.h"
#include "PropsMgr.h"
#include "MyPurchase.h"
#include "SnakeSkinRes.h"
#include "RankingModel.h"
using namespace std;

void DataLoader::loadData()
{
	SnakeColor::init();
	SoundMgr::theMgr()->init();
	PropsMgr::theMgr()->init();
	MyPurchase::sharedPurchase()->initBillingData();
	SnakeSkinRes::SnakeResData()->init();
	RankingModel::theModel()->init();
}
