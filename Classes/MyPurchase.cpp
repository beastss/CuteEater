#include "MyPurchase.h"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "org_cocos2dx_lib_GameBilling.h"
#endif
#include "ActionRunner.h"
using namespace cocos2d;
using namespace std;
using namespace rapidxml;

function<void()> MyPurchase::s_callback = function<void()>();
ActionRunner* MyPurchase::s_runner = NULL;

MyPurchase::MyPurchase()
{
	s_runner = ActionRunner::create();
	s_runner->retain();
}

MyPurchase::~MyPurchase()
{
	s_runner->clear();
	s_runner->release();
}

MyPurchase* MyPurchase::sharedPurchase()
{
	static MyPurchase model;
	return &model;
}

void MyPurchase::buyItem(int id, std::function<void()> callback)
{
	if (!checkBuyType(id) || s_callback) return;
	s_callback = callback;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID) 
	onPayResult(kReturnCodeSucceed);
#else
	const char* funstr = "org/cocos2dx/lib/PayAndroidApi";
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
		funstr,
		"rtnActivity",
		"()Ljava/lang/Object;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}

	isHave = JniHelper::getMethodInfo(minfo,
		funstr,
		"Purchase",
		"(I)V");
	if (isHave) {
		minfo.env->CallVoidMethod(jobj, minfo.methodID, id);
	}
#endif
}

void MyPurchase::onPayResult(int ret)
{
	CCLOG("payResult:   %d", ret);
	switch (ret)
	{
	case kReturnCodeSucceed:
		//ÑÓÊ±0.5f SdkºóÌ¨
		if (s_callback)
		{
			s_runner->queueAction(DelayAction::withDelay(0.5f));
			s_runner->queueAction(CallFuncAction::withFunctor([=]()
			{
				s_callback();
				s_callback = function<void()>();
			}));
		}
		break;
	case kReturnCodeFail:
		s_callback = function<void()>();
		break;
	case kReturnCodeCanceled:
		s_callback = function<void()>();
		break;
	default:
		s_callback = function<void()>();
		break;
	}
	
}

bool MyPurchase::checkBuyType(int type)
{
	return type >= 0 && type < m_billingData.size();
}

void MyPurchase::showToast(int index)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	const char* funstr = "org/cocos2dx/lib/PayAndroidApi";
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, 
		funstr,
		"rtnActivity",  
		"()Ljava/lang/Object;");
	jobject jobj; 
	if (isHave) { 
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID); 
	}

	isHave = JniHelper::getMethodInfo(minfo, 
		funstr,
		"showToast",
		"(I)V");  
	if (isHave) {
		minfo.env->CallVoidMethod(jobj, minfo.methodID, index);
	}
#endif
}

void MyPurchase::initBillingData()
{
	xml_document<> doc;
	bool bRet = false;
	unsigned long size = 0;
	unsigned char *pBytes = NULL;
	do {
		pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("data/billing.xml", "r", &size);
		CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
		std::string load_str((const char*)pBytes, size);
		CC_SAFE_DELETE_ARRAY(pBytes);
		char *buf = new char[strlen(load_str.c_str()) + 1];
		strcpy(buf, load_str.c_str());
		doc.parse<0>(buf);
	} while (0);

	xml_node<> *root = doc.first_node();
	for (auto node = root->first_node(); node != NULL; node = node->next_sibling())
	{
		BillingData data;
		data.name = node->first_attribute("name")->value();
		data.desc = node->first_attribute("desc")->value();
		data.canRepeatedBuy = atoi(node->first_attribute("desc")->value()) == 1;
		data.cost = atoi(node->first_attribute("cost")->value());
		data.code = node->first_attribute("code")->value();
		m_billingData.push_back(data);
	}
}