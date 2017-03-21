#include "TestScene.h"
#include "GameConfig.h"
#include "PlayerSnake.h"
#include "MyPurchase.h"
using namespace std;
USING_NS_CC;

bool TestScene::init()
{
	if (!CCScene::init())return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	auto bk = CCLayerColor::create(ccc4(120, 120, 120, 255));
	addChild(bk);

	MyPurchase::sharedPurchase()->initBillingData();
	testBatchNode();
    return true;
}

void TestScene::testBatchNode()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("snake/aaa.plist");
	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("snake/aaa.png");
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	for (int i = 0; i < 400; ++i)
	{
		CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("skin_16_head.png");
		sprite1->setPosition(ccp(CCRANDOM_0_1() * winSize.width, CCRANDOM_0_1() * winSize.height));
		CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("skin_17_body1.png");
		sprite2->setPosition(ccp(CCRANDOM_0_1() * winSize.width, CCRANDOM_0_1() * winSize.height));
		batchNode->addChild(sprite1);
		batchNode->addChild(sprite2);
	}

	addChild(batchNode);
}
