#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__
#include "cocos2d.h"

class GameConfig
{
public:
	static GameConfig *theModel();
	
	int getIntValue(std::string tableName, std::string key);
	float getFloatValue(std::string tableName, std::string key);
	std::string getStrValue(std::string tableName, std::string key);
	bool getBoolValue(std::string tableName, std::string key);

	std::vector<std::string>allKeys(std::string tableName);
private:
	const cocos2d::CCString* getValue(std::string tableName, std::string key);
};

#define GameConfigSelf GameConfig::theModel()
#endif