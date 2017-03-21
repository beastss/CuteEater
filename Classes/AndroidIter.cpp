#include "AndroidIter.h"
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include <jni.h> 
#include "platform/android/jni/JniHelper.h" 
#endif
USING_NS_CC;
using namespace std;

AndroidIter *AndroidIter::getIter()
{
	static AndroidIter iter;
	return &iter;
}

bool AndroidIter::isForBusiness()
{
	bool forBusiness = false;
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
		"isForBusiness",
		"()Z");
	if (isHave) {
		forBusiness = minfo.env->CallBooleanMethod(jobj, minfo.methodID);
	}
#endif
	return forBusiness;
}

std::string AndroidIter::getUserId()
{
	string userId = "34142";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	const char* funstr = "org/cocos2dx/lib/PayAndroidApi";

	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
		funstr,
		"rtnActivity",
		"()Ljava/lang/Object;");
	jobject jobj;
	if (isHave)
	{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}
	isHave = JniHelper::getMethodInfo(minfo,
		funstr,
		"getUserId",
		"()Ljava/lang/String;");
	if (isHave)
	{
		jstring jstr = (jstring)(minfo.env->CallObjectMethod(jobj, minfo.methodID));
		return JniHelper::jstring2string(jstr);
	}
#else
	return userId;
#endif
}