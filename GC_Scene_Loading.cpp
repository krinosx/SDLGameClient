#include "GC_Scene_Loading.h"



GC_Scene_Loading::GC_Scene_Loading(std::string id) 
	: GC_Scene(id)
{
	this->isLoaded = false;
}


GC_Scene_Loading::~GC_Scene_Loading()
{
	this->unload();
	std::cout << "Destroying GC_Scene_Loading" << std::endl;
}

void GC_Scene_Loading::draw(SDL_Renderer * renderer)
{

	this->guiManager.draw(renderer);
}

void GC_Scene_Loading::load(SDL_Renderer * renderer)
{

	TTF_Font * font = this->sceneManager.lock()->getResourceLoader()->getFont("font_arial")->getFont();

	SDL_Color buttonColor = { 255,255,255,255 };
	SDL_Color buttonBgColor = { 200,255,200,255 };

	this->exitButton = new GUIButton(150, 250, 150, 64, "Loading... (click to get back)", font, true);
	this->exitButton->setLabelColor(buttonColor);
	this->exitButton->setBackgroundColor(buttonBgColor);
	this->exitButton->setAction([=]() {
		this->sceneManager.lock()->loadScene("scene_menu");
	});
	
	this->guiManager.addComponent(exitButton);

	this->isLoaded = true;
}

void GC_Scene_Loading::unload()
{
	this->guiManager.destroy();
	this->isLoaded = false;
}

bool GC_Scene_Loading::isReady()
{
	return this->isLoaded;
}

void GC_Scene_Loading::processEvents(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		/* Dispatch the events for GUIManager */
		this->guiManager.click(e.button.x, e.button.y);

		break;
	case SDL_MOUSEBUTTONUP:
		this->guiManager.release(e.button.x, e.button.y);
		break;
	default:
		break;
	}
}

void GC_Scene_Loading::setManager(std::weak_ptr<GC_SceneManager> manager)
{
	this->sceneManager = manager;
}
