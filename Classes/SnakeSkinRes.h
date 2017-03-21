#ifndef __SNAKE_SKIN_RES_H__
#define __SNAKE_SKIN_RES_H__
#include "cocos2d.h"

enum
{
	kFirstSkin = 0,
	kLastSkin = 3,
};

class SnakeSkinRes
{
public:
	static SnakeSkinRes *SnakeResData();
	void init();

	std::string getHeadRes(int skin);
	std::string getBodyRes(int skin, int pos);
	std::string getTailRes(int skin);
private:
	bool isValidSkinId(int skin);
private:

	std::vector<std::string> m_headRes;
	std::vector<std::pair<std::string, int>> m_bodyRes;
	std::vector<std::string> m_tailRes;
};
#endif