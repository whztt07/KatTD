#include "Ogre.h"
#include "OgreConfigFile.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#include "windows.h"
#include "../res/resource.h"
#include "MainFrameListener.h"

using namespace Ogre;


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
	Root* root;
	OIS::InputManager* inputManager;
	OIS::Keyboard* keyboard;
	MainFrameListener* main_listener;
	try
	{
		//Create root
		root = new Root();

		//Load resources
		String secName, typeName, archName;
		ConfigFile cf;
		cf.load("resources.cfg");
		ConfigFile::SectionIterator seci = cf.getSectionIterator();
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			ConfigFile::SettingsMultiMap *settings = seci.getNext();
			ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
			}
		}

		//Create render system
		if (!root->restoreConfig() && !root->showConfigDialog())
			throw Exception(52, "User canceled the config dialog!", "Application::setupRenderSystem()");
		root->initialise(true, "Kat Vs The Lovecraftian Horrors!");

		//Initialise resources
		TextureManager::getSingleton().setDefaultNumMipmaps(5);
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


		//Create the scene
		SceneManager* mgr = root->createSceneManager(ST_GENERIC, "Default SceneManager");
		Camera* cam = mgr->createCamera("Camera");
		Viewport* vp = root->getAutoCreatedWindow()->addViewport(cam);
		vp->setBackgroundColour(ColourValue(1, 0, 0, 0));
		cam->setAspectRatio(vp->getActualWidth() / vp->getActualHeight());


		//Setup OIS
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		OIS::ParamList pl;

		root->getAutoCreatedWindow()->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		inputManager = OIS::InputManager::createInputSystem(pl);
		try
		{
			keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, false));
			//mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));
			//mJoy = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false));
		}
		catch (const OIS::Exception &e)
		{
			throw Exception(42, e.eText, "Application::setupInputSystem");
		}

		main_listener = new MainFrameListener(mgr, root->getAutoCreatedWindow(), cam, keyboard);
		root->addFrameListener(main_listener);
		root->startRendering();
	} catch( Ogre::Exception& e )
	{
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return -1;
	}
	return 0;
}