#include "MainFrameListener.h"

MainFrameListener::MainFrameListener(SceneManager *sceneMgr, RenderWindow* win, Camera* cam)
: ExampleFrameListener(win, cam), mSceneMgr(sceneMgr)
{
}

bool MainFrameListener::frameStarted(const FrameEvent& evt)
{
	bool ret = ExampleFrameListener::frameStarted(evt);

	return ret;
}