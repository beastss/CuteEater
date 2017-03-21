#ifndef __ANDROID_ITER_H__
#define __ANDROID_ITER_H__
#include "cocos2d.h"

class AndroidIter
{
public:
	static AndroidIter *getIter();
	bool isForBusiness();
	std::string getUserId();
};
#endif

