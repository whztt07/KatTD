#include "MainFrameListener.h"

MainFrameListener::MainFrameListener(SceneManager *sceneMgr, RenderWindow* win, Camera* cam, OIS::Keyboard* keyboard)
: mSceneMgr(sceneMgr), mWindow(win), mCamera(cam), mKeyboard(keyboard)
{
	mSceneMgr->setAmbientLight(ColourValue());

	Entity* ent1 = mSceneMgr->createEntity("Robot", "ogrehead.mesh");
	SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("RobotNode");
	node1->attachObject(ent1);


	mCameraOrbitAngle = 0;
	mCamera->lookAt(0, 0, 0);
}

bool MainFrameListener::frameStarted(const FrameEvent& evt)
{
	
	//bool ret = ExampleFrameListener::frameStarted(evt);
	mKeyboard->capture();

	if(mKeyboard->isKeyDown(OIS::KC_LEFT))
		mCameraOrbitAngle += 3.14 * evt.timeSinceLastFrame;
	if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
		mCameraOrbitAngle -= 3.14 * evt.timeSinceLastFrame;


	mCamera->setPosition(200 * cosf(mCameraOrbitAngle), 100, 200 * sinf(mCameraOrbitAngle));
	mCamera->lookAt(0, 0, 0);
	return true;
}