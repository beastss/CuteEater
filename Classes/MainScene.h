#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class ScaleDialog;
class BasePanel;
class KeyPadWatcher;
enum PanelId
{
	kPanelIdDefault,
	kPanelIdMenuPanel,
	kPanelIdGamePanel,
	kPanelIdHelpPanel,
};
class MainScene : public cocos2d::CCScene
{
public:
	static MainScene *theScene();
	~MainScene();
	void showPanel(int panelId);
	void showDialog(ScaleDialog *dialog);
public:
	void onKeyBackClicked();
	void exitGame();
private:
	MainScene();
    virtual bool init();  
private:
	cocos2d::CCNode *m_panelLayer;
	cocos2d::CCNode *m_dialogLayer;
	static MainScene *m_scene;
	BasePanel *m_curPanel;
	KeyPadWatcher *m_keyPadWatcher;
};

#endif 
