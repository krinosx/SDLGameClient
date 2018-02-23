#include "GC_Scene_Main.h"




GC_Scene_Main::GC_Scene_Main(std::string id)
	:GC_Scene(id)
{
	this->bgTexture = NULL;
}

GC_Scene_Main::~GC_Scene_Main()
{
}

void GC_Scene_Main::setSceneManager(std::shared_ptr<GC_SceneManager> sceneManager)
{
	this->sceneManager = sceneManager;
}

void GC_Scene_Main::draw(SDL_Renderer * renderer)
{
	if (this->bgTexture != NULL)
	{
		SDL_RenderCopy(renderer, this->bgTexture, NULL, NULL);
	}
}

void GC_Scene_Main::load(SDL_Renderer * renderer)
{

	/*
	* Load Textures
	*/

	if (this->sceneManager.lock()->getResourceLoader()->getTexture("main_scene_bg") == nullptr)
	{
		this->sceneManager.lock()->getResourceLoader()->loadTexture("main_scene_bg", IMG_MAIN_SCENE_BG, renderer);
	};

	this->bgTexture = this->sceneManager.lock()->getResourceLoader()->getTexture("main_scene_bg")->getTexture().get();

}

void GC_Scene_Main::unload()
{
	/*
	if (this->bgTexture != NULL)
	{
		SDL_DestroyTexture(this->bgTexture);
	}
	*/
//	this->sceneManager.lock()->getResourceLoader()->unload
}

bool GC_Scene_Main::isReady()
{
	return this->bgTexture != NULL;
}

void GC_Scene_Main::processEvents(SDL_Event e)
{
	switch (e.type)
	{
	

	case SDL_QUIT:
		break;
	case SDL_KEYDOWN:
		//this->guiManager.keyPress(e.key.keysym);
		break;
	case SDL_KEYUP:
		//this->guiManager.keyRelease(e.key.keysym);
		switch (e.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			// return to menu
			this->sceneManager.lock()->loadScene("scene_menu");
		default:
			break;
		}


		break;
	case SDL_MOUSEBUTTONDOWN:
		/* Dispatch the events for GUIManager */
		//this->guiManager.click(e.button.x, e.button.y);
		break;
	case SDL_MOUSEBUTTONUP:
		//this->guiManager.release(e.button.x, e.button.y);
		break;
	case SDL_TEXTEDITING:
		break;
	case SDL_TEXTINPUT:
		//this->guiManager.textInput(e.text);
		break;
	default:
		break;
	}


}
