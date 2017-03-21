#ifndef __PROPS_MGR_H__
#define __PROPS_MGR_H__
#include "cocos2d.h"
#include <unordered_map>
enum PropsType
{
	kPropsTypeGrow,
	kPropsTypeGodlike,
};
class PropsMgr
{
public:
	static PropsMgr *theMgr();
	void init();
	void saveNum(int propsType, int num);
	int getNum(int propsType);
private:
	std::unordered_map<int, int>m_props;
};


#endif