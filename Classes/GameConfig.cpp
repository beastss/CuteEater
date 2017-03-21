#include "GameConfig.h"
USING_NS_CC;
using namespace std;

GameConfig *GameConfig::theModel()
{
	static GameConfig model;
	return &model;
}

const CCString* GameConfig::getValue(std::string tableName, std::string key)
{
	string tbPath = "data/" + tableName + ".xml";
	CCDictionary* pDict = CCDictionary::createWithContentsOfFile(tbPath.c_str());
	auto value = pDict->valueForKey(key);
	return value;
}

int GameConfig::getIntValue(std::string tableName, std::string key)
{
	auto value = getValue(tableName, key)->intValue();
	return value;
}

float GameConfig::getFloatValue(std::string tableName, std::string key)
{
	auto value = getValue(tableName, key)->floatValue();
	return value;
}

bool GameConfig::getBoolValue(std::string tableName, std::string key)
{
	auto value = getValue(tableName, key)->boolValue();
	return value;
}

std::string GameConfig::getStrValue(std::string tableName, std::string key)
{
	auto value = getValue(tableName, key)->getCString();
	return value;
}

std::vector<std::string> GameConfig::allKeys(std::string tableName)
{
	vector<string> keys;

	string tbPath = "data/" + tableName + ".xml";
	CCDictionary* pDict = CCDictionary::createWithContentsOfFile(tbPath.c_str());
	pDict->allKeys();
	CCDictElement * pElement;
	CCDICT_FOREACH(pDict, pElement)
	{
		const char * key = pElement->getStrKey();
		CCString * value = (CCString *)pElement->getObject();
		keys.push_back(key);
	}
	return keys;
}

