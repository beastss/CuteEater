#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

class TestScene : public cocos2d::CCScene
{
public:
	CREATE_FUNC(TestScene);
private:
    virtual bool init();  
private:
	void testBatchNode();
};

#endif 
