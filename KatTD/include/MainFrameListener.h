#pragma once
#include "ExampleFrameListener.h"

class MainFrameListener: public FrameListener, public WindowEventListener
{
private:
	SceneManager* mSceneMgr;
	RenderWindow* mWindow;
	Camera* mCamera;
	
	OIS::Keyboard* mKeyboard;

	float mCameraOrbitAngle;
	bool mClosing;

	Entity* mRobot;
	SceneNode* mRobotNode;
	Bone* mHeadBone;
	float mHeadAngle;

public:
	MainFrameListener(SceneManager *sceneMgr, RenderWindow* win, Camera* cam, OIS::Keyboard* keyboard);
	bool frameStarted(const FrameEvent& evt);
	bool initialise();
	void windowClosed(RenderWindow* rw);

};