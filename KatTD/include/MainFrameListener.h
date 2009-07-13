#pragma once
#include "ExampleFrameListener.h"

class MainFrameListener: public FrameListener
{
private:
	SceneManager* mSceneMgr;
	RenderWindow* mWindow;
	Camera* mCamera;
	
	OIS::Keyboard* mKeyboard;

	float mCameraOrbitAngle;
public:
	MainFrameListener(SceneManager *sceneMgr, RenderWindow* win, Camera* cam, OIS::Keyboard* keyboard);
	bool frameStarted(const FrameEvent& evt);
	bool initialise();

};