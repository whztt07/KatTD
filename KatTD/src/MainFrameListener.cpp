#include "MainFrameListener.h"

MainFrameListener::MainFrameListener(SceneManager *sceneMgr, RenderWindow* win, Camera* cam, OIS::Keyboard* keyboard)
: mSceneMgr(sceneMgr), mWindow(win), mCamera(cam), mKeyboard(keyboard)
{
	mSceneMgr->setAmbientLight(ColourValue());

	mRobot = mSceneMgr->createEntity("Robot", "Robot.mesh");
	mRobotNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RobotNode");
	mRobotNode->attachObject(mRobot);


	SkeletonInstance* skel = mRobot->getSkeleton();
	Animation* idle_anim = skel->getAnimation("Idle");
	mHeadBone = skel->getBone("Joint12");
	mHeadBone->setManuallyControlled(true);
	mHeadAngle = 0;
	idle_anim->destroyNodeTrack(mHeadBone->getHandle());


	mClosing = false;
	mCameraOrbitAngle = 0;
	mCamera->lookAt(0, 0, 0);
}

bool MainFrameListener::frameStarted(const FrameEvent& evt)
{
	//Do camera positioning
	//bool ret = ExampleFrameListener::frameStarted(evt);
	mKeyboard->capture();

	if(mKeyboard->isKeyDown(OIS::KC_LEFT))
		mCameraOrbitAngle += 3.14 * evt.timeSinceLastFrame;
	if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
		mCameraOrbitAngle -= 3.14 * evt.timeSinceLastFrame;


	mCamera->setPosition(200 * cosf(mCameraOrbitAngle), 100, 200 * sinf(mCameraOrbitAngle));
	mCamera->lookAt(0, 0, 0);


	//Do animation
	
	AnimationState* idle_state = mRobot->getAnimationState("Idle");
	mRobot->setDisplaySkeleton(true);
	idle_state->setLoop(true);
	idle_state->setEnabled(true);
	idle_state->addTime(evt.timeSinceLastFrame);

	mHeadAngle += 3.14 * evt.timeSinceLastFrame;

	Quaternion head_orientation;
	head_orientation.FromAngleAxis(Radian(mHeadAngle), Vector3(0, 1, 0));
	mHeadBone->setOrientation(head_orientation);

	
	

	return !mClosing;
}

void MainFrameListener::windowClosed(RenderWindow* rw)
{
	mClosing = true;
}