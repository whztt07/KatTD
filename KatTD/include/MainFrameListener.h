#pragma once
#include "ExampleFrameListener.h"

class MainFrameListener: public ExampleFrameListener
{
private:
	SceneManager* mSceneMgr;
public:
	MainFrameListener(SceneManager *sceneMgr, RenderWindow* win, Camera* cam);

	bool frameStarted(const FrameEvent& evt);

};