#include "SnakeSkinRes.h"
USING_NS_CC;
using namespace std;

SnakeSkinRes *SnakeSkinRes::SnakeResData()
{
	static SnakeSkinRes res;
	return &res;
}

void SnakeSkinRes::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite_frames/snake_skin.plist");

	m_headRes.push_back("sprite_frames/pic_0_0.png");
	m_bodyRes.push_back(make_pair("skin_1_body%d.png", 1));
	m_tailRes.push_back("sprite_frames/pic_%d_%d.png");

	m_headRes.push_back("sprite_frames/pic_1_0.png");
	m_bodyRes.push_back(make_pair("skin_2_body%d.png", 2));
	m_tailRes.push_back("sprite_frames/pic_%d_%d.png");

	m_headRes.push_back("sprite_frames/pic_2_0.png");
	m_bodyRes.push_back(make_pair("skin_3_body%d.png", 1));
	m_tailRes.push_back("sprite_frames/pic_%d_%d.png");

	m_headRes.push_back("sprite_frames/pic_3_0.png");
	m_bodyRes.push_back(make_pair("skin_4_body%d.png", 2));
	m_tailRes.push_back("sprite_frames/pic_%d_%d.png");

	/*m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_5_body%d.png", 1));
	m_tailRes.push_back("skin_5_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_6_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_7_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_8_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");
	
	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_9_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_10_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_11_body%d.png", 1));
	m_tailRes.push_back("skin_5_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_12_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_13_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_14_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_15_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_16_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_17_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("sprite_frames/enemy.png");
	m_bodyRes.push_back(make_pair("skin_18_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");*/
}

std::string SnakeSkinRes::getHeadRes(int skin)
{
	assert(isValidSkinId(skin));

	return m_headRes[skin];
}

std::string SnakeSkinRes::getBodyRes(int skin, int pos)
{
	assert(isValidSkinId(skin));

	int index = (pos - 1) % m_bodyRes[skin].second + 1;
	char str[100] = { 0 };
	sprintf(str, m_bodyRes[skin].first.c_str(), index);
	return str;
}

std::string SnakeSkinRes::getTailRes(int skin)
{
	assert(isValidSkinId(skin));

	return m_tailRes[skin];
}

bool SnakeSkinRes::isValidSkinId(int skin)
{
	return skin >= kFirstSkin && skin <= kLastSkin;
}