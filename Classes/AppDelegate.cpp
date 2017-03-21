#include "AppDelegate.h"
#include "MainScene.h"
#include "TestScene.h"
#include "DataLoader.h"
#include "SimpleAudioEngine.h"
#include "SoundMgr.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	pEGLView->setFrameSize(800, 480);
#endif
	CCSize designSize = CCSizeMake(800, 480);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedHeight);
    pDirector->setAnimationInterval(1.0 / 60);

	DataLoader loader;
	loader.loadData();
	CCScene *pScene = NULL;
//#define GMAE_TEST
#ifdef GMAE_TEST
	pScene = TestScene::create();
#else
    pScene = MainScene::theScene();
#endif 
    pDirector->runWithScene(pScene);

	//pDirector->setDisplayStats(true);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	if(SoundMgr::theMgr()->isBackgroundMusicOn())
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}
